#ifndef BME_H
#define BME_H

#include <stdbool.h>
#include <stdint.h>

bool bme_configure(int i2c_dev);

bool bme_get_temp(int i2c_dev, float *t_degC, int32_t *t_fine);

bool bme_get_pressure(int i2c_dev, int32_t t_fine, float *p_kPa);

bool bme_get_humidity(int i2c_dev, int32_t t_fine, float *humidity_pcnt);

#endif // BME_H
