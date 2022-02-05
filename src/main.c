#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "bme.h"
#include "i2c.h"

#define I2C_DEV_NAME "/dev/i2c-2"

int main()
{
    int i2c_dev = 0;
    if(!i2c_init(I2C_DEV_NAME, &i2c_dev)) {
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
