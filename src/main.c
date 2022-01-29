#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#define I2C_DEV_NAME "/dev/i2c-2"
#define BME_ADDR 0x76

bool i2c_init_dev(const char* i2c_dev_name, int* i2c_dev)
{
    *i2c_dev = open(i2c_dev_name, O_RDWR);
    if(*i2c_dev == -1) {
        fprintf(stderr, "Failed to open the i2c bus \"%s\": Error %i: %s\n", i2c_dev_name, errno, strerror(errno));
        return false;
    }
    return true;
}

bool i2c_read_dev_reg(int i2c_dev, uint8_t dev_addr, uint8_t reg_addr, uint8_t* reg_val)
{
    struct i2c_msg messages[] = {
        { dev_addr, 0, 1, &reg_addr },
        { dev_addr, I2C_M_RD, 1, reg_val }
    };
    const size_t n_messages = sizeof(messages) / sizeof(*messages);
    struct i2c_rdwr_ioctl_data ioctl_data = {
        .msgs = messages,
        .nmsgs = n_messages
    };
    if(ioctl(i2c_dev, I2C_RDWR, &ioctl_data) == -1) {
        fprintf(stderr, "Failed to read register %#x from I2C device %#x: Error %i: %s\n", reg_addr, dev_addr, errno, strerror(errno));
        return false;
    }
    return true;
}

bool bme_get_temp(int i2c_dev, float* t_degC, int32_t* t_fine)
{
    int32_t adc_T = 0;
    uint8_t adc_T_addrs[] = {
        0xFA,
        0xFB,
        0xFC
    };
    for(size_t i = 0; i < sizeof(adc_T_addrs) / sizeof(*adc_T_addrs); ++i) {
        uint8_t reg_val = 0;
        if(!i2c_read_dev_reg(i2c_dev, BME_ADDR, adc_T_addrs[i], &reg_val)) {
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
    uint8_t dig_T1_addrs[] = {
        0x89,
        0x88
    };
    for(size_t i = 0; i < sizeof(dig_T1_addrs) / sizeof(*dig_T1_addrs); ++i) {
        uint8_t reg_val = 0;
        if(!i2c_read_dev_reg(i2c_dev, BME_ADDR, dig_T1_addrs[i], &reg_val)) {
            return false;
        }
        dig_T1 <<= 8;
        dig_T1 |= reg_val;
    }

    int32_t dig_T2 = 0;
    uint8_t dig_T2_addrs[] = {
        0x8B,
        0x8A
    };
    for(size_t i = 0; i < sizeof(dig_T2_addrs) / sizeof(*dig_T2_addrs); ++i) {
        uint8_t reg_val = 0;
        if(!i2c_read_dev_reg(i2c_dev, BME_ADDR, dig_T2_addrs[i], &reg_val)) {
            return false;
        }
        dig_T2 <<= 8;
        dig_T2 |= reg_val;
    }
    dig_T2 = (int32_t)(*(int16_t*)&dig_T2);

    int32_t dig_T3 = 0;
    uint8_t dig_T3_addrs[] = {
        0x8D,
        0x8C
    };
    for(size_t i = 0; i < sizeof(dig_T3_addrs) / sizeof(*dig_T3_addrs); ++i) {
        uint8_t reg_val = 0;
        if(!i2c_read_dev_reg(i2c_dev, BME_ADDR, dig_T3_addrs[i], &reg_val)) {
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

int main()
{
    int i2c_dev = 0;
    if(!i2c_init_dev(I2C_DEV_NAME, &i2c_dev)) {
        return EXIT_FAILURE;
    }

    float t_degC = 0.0f;
    int32_t t_fine = 0;
    if(!bme_get_temp(i2c_dev, &t_degC, &t_fine)) {
        return EXIT_FAILURE;
    }
    printf("t_degC = %.2f degrees Celsius\n", t_degC / 100.0f);

    // i2cset -y 2 0x76 0xF4 0x45 // Puts device in "Forced" mode, for single measurement reading

    // {
    //     int32_t adc_P = 0x64f;

    //     int64_t dig_P1 = 0x9051;
    //     int64_t dig_P2 = INT16_C(0xd6b0);
    //     int64_t dig_P3 = INT16_C(0x0bd0);
    //     int64_t dig_P4 = INT16_C(0x212a);
    //     int64_t dig_P5 = INT16_C(0xffcf);
    //     int64_t dig_P6 = INT16_C(0xfff9);
    //     int64_t dig_P7 = INT16_C(0x26ac);
    //     int64_t dig_P8 = INT16_C(0xd80a);
    //     int64_t dig_P9 = INT16_C(0x10bd);

    //     int64_t var1, var2, p;
    //     var1 = (t_fine) - 128000;
    //     var2 = var1 * var1 * dig_P6;
    //     var2 = var2 + ((var1*dig_P5)<<17);
    //     var2 = var2 + ((dig_P4)<<35);
    //     var1 = ((var1 * var1 * dig_P3)>>8) + ((var1 * dig_P2)<<12);
    //     var1 = ((((INT64_C(1))<<47)+var1))*(dig_P1)>>33;
    //     p = 1048576-adc_P;
    //     p = (((p<<31)-var2)*3125)/var1;
    //     var1 = ((dig_P9) * (p>>13) * (p>>13)) >> 25;
    //     var2 = ((dig_P8) * p) >> 19;
    //     p = ((p + var1 + var2) >> 8) + ((dig_P7)<<4);

    //     printf("P = %.2f kPa\n", p / 256000.0f);
    // }

    return EXIT_SUCCESS;
}
