#include "bme.h"

#include <stddef.h>

#include "i2c.h"

#define BME_ADDR 0x76

bool bme_get_temp(int i2c_dev, float* t_degC, int32_t* t_fine)
{
    int32_t adc_T = 0;
    const uint8_t adc_T_addrs[] = {
        0xFA,
        0xFB,
        0xFC
    };
    for(size_t i = 0; i < sizeof(adc_T_addrs) / sizeof(*adc_T_addrs); ++i) {
        uint8_t reg_val = 0;
        if(!i2c_read_reg(i2c_dev, BME_ADDR, adc_T_addrs[i], &reg_val)) {
            return false;
        }
        if(i == (sizeof(adc_T_addrs) / sizeof(*adc_T_addrs) - 1)) {
            reg_val &= 0xF0;
            reg_val >>= 4;
            adc_T <<= 4;
        }
        else {
            adc_T <<= 8;
        }
        adc_T |= reg_val;
    }

    int32_t dig_T1 = 0;
    const uint8_t dig_T1_addrs[] = {
        0x89,
        0x88
    };
    for(size_t i = 0; i < sizeof(dig_T1_addrs) / sizeof(*dig_T1_addrs); ++i) {
        uint8_t reg_val = 0;
        if(!i2c_read_reg(i2c_dev, BME_ADDR, dig_T1_addrs[i], &reg_val)) {
            return false;
        }
        dig_T1 <<= 8;
        dig_T1 |= reg_val;
    }

    int32_t dig_T2 = 0;
    const uint8_t dig_T2_addrs[] = {
        0x8B,
        0x8A
    };
    for(size_t i = 0; i < sizeof(dig_T2_addrs) / sizeof(*dig_T2_addrs); ++i) {
        uint8_t reg_val = 0;
        if(!i2c_read_reg(i2c_dev, BME_ADDR, dig_T2_addrs[i], &reg_val)) {
            return false;
        }
        dig_T2 <<= 8;
        dig_T2 |= reg_val;
    }
    dig_T2 = (int32_t)(*(int16_t*)&dig_T2);

    int32_t dig_T3 = 0;
    const uint8_t dig_T3_addrs[] = {
        0x8D,
        0x8C
    };
    for(size_t i = 0; i < sizeof(dig_T3_addrs) / sizeof(*dig_T3_addrs); ++i) {
        uint8_t reg_val = 0;
        if(!i2c_read_reg(i2c_dev, BME_ADDR, dig_T3_addrs[i], &reg_val)) {
            return false;
        }
        dig_T3 <<= 8;
        dig_T3 |= reg_val;
    }
    dig_T3 = (int32_t)(*(int16_t*)&dig_T3);

    const int32_t var1 = (((adc_T>>3) - (dig_T1<<1)) * dig_T2) >> 11;
    const int32_t var2 = (((((adc_T>>4) - dig_T1) * ((adc_T>>4) - dig_T1)) >> 12) * dig_T3) >> 14;
    *t_fine = var1 + var2;
    *t_degC = (*t_fine * 5 + 128) >> 8;

    return true;
}
