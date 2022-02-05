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

    if(!bme_configure(i2c_dev)) {
        return EXIT_FAILURE;
    }

    float t_degC = 0.0f;
    int32_t t_fine = 0;
    if(!bme_get_temp(i2c_dev, &t_degC, &t_fine)) {
        return EXIT_FAILURE;
    }
    printf("t_degC = %.2f degrees Celsius\n", t_degC / 100.0f);

    float p_kPa = 0.0f;
    if(!bme_get_pressure(i2c_dev, t_fine, &p_kPa)) {
        return EXIT_FAILURE;
    }
    printf("p_kPa = %.2f kPa\n", p_kPa);

    float humidity_pcnt = 0.0f;
    if(!bme_get_humidity(i2c_dev, t_fine, &humidity_pcnt)) {
        return EXIT_FAILURE;
    }
    printf("humidity_pcnt = %.2f %%\n", humidity_pcnt);

    return EXIT_SUCCESS;
}
