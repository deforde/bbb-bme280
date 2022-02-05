#ifndef BME_H
#define BME_H

#include <stdbool.h>
#include <stdint.h>

bool bme_get_temp(int i2c_dev, float* t_degC, int32_t* t_fine);

#endif //BME_H
