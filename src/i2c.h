#ifndef I2C_H
#define I2C_H

#include <stdbool.h>
#include <stdint.h>

bool i2c_init(const char* i2c_dev_name, int* i2c_dev);

bool i2c_read_reg(int i2c_dev, uint8_t dev_addr, uint8_t reg_addr, uint8_t* reg_val);

bool i2c_write_reg(int i2c_dev, uint8_t dev_addr, uint8_t reg_addr, uint8_t reg_val);

#endif //I2C_H
