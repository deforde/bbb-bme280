#include "bme.h"

#include <assert.h>
#include <stddef.h>

#include "i2c.h"

#define BME_ADDR 0x76

static bool read_val_20u(int i2c_dev, const uint8_t* const addrs, size_t n_addrs, int32_t* val)
{
    assert(n_addrs == 3);

    for(size_t i = 0; i < n_addrs; ++i) {
        uint8_t reg_val = 0;
        if(!i2c_read_reg(i2c_dev, BME_ADDR, addrs[i], &reg_val)) {
            return false;
        }
        if(i == (n_addrs - 1)) {
            reg_val &= 0xF0;
            reg_val >>= 4;
            *val <<= 4;
        }
        else {
            *val <<= 8;
        }
        *val |= reg_val;
    }

    return true;
}

static bool read_val_16u(int i2c_dev, const uint8_t* const addrs, size_t n_addrs, int32_t* val)
{
    assert(n_addrs == 2);

    for(size_t i = 0; i < n_addrs; ++i) {
        uint8_t reg_val = 0;
        if(!i2c_read_reg(i2c_dev, BME_ADDR, addrs[i], &reg_val)) {
            return false;
        }
        *val <<= 8;
        *val |= reg_val;
    }

    return true;
}

static bool read_val_16s(int i2c_dev, const uint8_t* const addrs, size_t n_addrs, int32_t* val)
{
    if(!read_val_16u(i2c_dev, addrs, n_addrs, val)) {
        return false;
    }
    *val = (int32_t)(*(int16_t*)val);
    return val;
}

bool bme_configure(int i2c_dev)
{
    return i2c_write_reg(i2c_dev, BME_ADDR, 0xF4, 0x45); // Puts device in "Forced" mode, for single measurement reading
}

bool bme_get_temp(int i2c_dev, float* t_degC, int32_t* t_fine)
{
    int32_t adc_T = 0;
    const uint8_t adc_T_addrs[] = {
        0xFA,
        0xFB,
        0xFC
    };
    if(!read_val_20u(i2c_dev, adc_T_addrs, sizeof(adc_T_addrs) / sizeof(*adc_T_addrs), &adc_T)) {
        return false;
    }

    int32_t dig_T1 = 0;
    const uint8_t dig_T1_addrs[] = {
        0x89,
        0x88
    };
    if(!read_val_16u(i2c_dev, dig_T1_addrs, sizeof(dig_T1_addrs) / sizeof(*dig_T1_addrs), &dig_T1)) {
        return false;
    }

    int32_t dig_T2 = 0;
    const uint8_t dig_T2_addrs[] = {
        0x8B,
        0x8A
    };
    if(!read_val_16s(i2c_dev, dig_T2_addrs, sizeof(dig_T2_addrs) / sizeof(*dig_T2_addrs), &dig_T2)) {
        return false;
    }

    int32_t dig_T3 = 0;
    const uint8_t dig_T3_addrs[] = {
        0x8D,
        0x8C
    };
    if(!read_val_16s(i2c_dev, dig_T3_addrs, sizeof(dig_T3_addrs) / sizeof(*dig_T3_addrs), &dig_T3)) {
        return false;
    }

    const int32_t var1 = (((adc_T>>3) - (dig_T1<<1)) * dig_T2) >> 11;
    const int32_t var2 = (((((adc_T>>4) - dig_T1) * ((adc_T>>4) - dig_T1)) >> 12) * dig_T3) >> 14;
    *t_fine = var1 + var2;
    *t_degC = (*t_fine * 5 + 128) >> 8;

    return true;
}

bool bme_get_pressure(int i2c_dev, int32_t t_fine, float* p_kPa)
{
    int32_t adc_P = 0;
    const uint8_t adc_P_addrs[] = {
        0xF7,
        0xF8,
        0xF9
    };
    if(!read_val_20u(i2c_dev, adc_P_addrs, sizeof(adc_P_addrs) / sizeof(*adc_P_addrs), &adc_P)) {
        return false;
    }

    int64_t dig_P1 = 0;
    const uint8_t dig_P1_addrs[] = {
        0x8F,
        0x8E
    };
    if(!read_val_16u(i2c_dev, dig_P1_addrs, sizeof(dig_P1_addrs) / sizeof(*dig_P1_addrs), (int32_t*)&dig_P1)) {
        return false;
    }

    int32_t dig_P[8] = {0};
    const uint8_t dig_P_addrs[8][2] = {
        {0x91, 0x90},
        {0x93, 0x92},
        {0x95, 0x94},
        {0x97, 0x96},
        {0x99, 0x98},
        {0x9B, 0x9A},
        {0x9D, 0x9C},
        {0x9F, 0x9E}
    };
    for(size_t i = 0; i < sizeof(dig_P_addrs) / sizeof(*dig_P_addrs); ++i) {
        if(!read_val_16s(i2c_dev, dig_P_addrs[i], sizeof(dig_P_addrs[i]) / sizeof(*dig_P_addrs[i]), &dig_P[i])) {
            return false;
        }
    }

    const int64_t dig_P2 = dig_P[0];
    const int64_t dig_P3 = dig_P[1];
    const int64_t dig_P4 = dig_P[2];
    const int64_t dig_P5 = dig_P[3];
    const int64_t dig_P6 = dig_P[4];
    const int64_t dig_P7 = dig_P[5];
    const int64_t dig_P8 = dig_P[6];
    const int64_t dig_P9 = dig_P[7];

    int64_t var1, var2, p;
    var1 = (t_fine) - 128000;
    var2 = var1 * var1 * dig_P6;
    var2 = var2 + ((var1 * dig_P5) << 17);
    var2 = var2 + ((dig_P4) << 35);
    var1 = ((var1 * var1 * dig_P3) >> 8) + ((var1 * dig_P2) << 12);
    var1 = ((((INT64_C(1)) << 47) + var1)) * (dig_P1) >> 33;
    p = 1048576 - adc_P;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = ((dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = ((dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + ((dig_P7) << 4);

    *p_kPa = p / 256000.0f;

    return true;
}
