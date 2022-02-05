#include "i2c.h"

#include <stdio.h>
#include <string.h>

#include <errno.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>

bool
i2c_init(const char *i2c_dev_name, int *i2c_dev)
{
    *i2c_dev = open(i2c_dev_name, O_RDWR);
    if (*i2c_dev == -1)
    {
        fprintf(stderr,
                "Failed to open the i2c bus \"%s\": Error %i: %s\n",
                i2c_dev_name,
                errno,
                strerror(errno));
        return false;
    }
    return true;
}

bool
i2c_read_reg(int i2c_dev, uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_val)
{
    struct i2c_msg messages[]
        = { { dev_addr, 0, 1, &reg_addr }, { dev_addr, I2C_M_RD, 1, reg_val } };
    const size_t n_messages = sizeof(messages) / sizeof(*messages);
    const struct i2c_rdwr_ioctl_data ioctl_data
        = { .msgs = messages, .nmsgs = n_messages };
    if (ioctl(i2c_dev, I2C_RDWR, &ioctl_data) == -1)
    {
        fprintf(
            stderr,
            "Failed to read register %#x from I2C device %#x: Error %i: %s\n",
            reg_addr,
            dev_addr,
            errno,
            strerror(errno));
        return false;
    }
    return true;
}

bool
i2c_write_reg(int i2c_dev, uint8_t dev_addr, uint8_t reg_addr, uint8_t reg_val)
{
    uint8_t        command[]  = { reg_addr, reg_val };
    struct i2c_msg messages[] = { { dev_addr, 0, sizeof(command), command } };
    const size_t   n_messages = sizeof(messages) / sizeof(*messages);
    const struct i2c_rdwr_ioctl_data ioctl_data
        = { .msgs = messages, .nmsgs = n_messages };
    if (ioctl(i2c_dev, I2C_RDWR, &ioctl_data) == -1)
    {
        fprintf(
            stderr,
            "Failed to write register %#x from I2C device %#x: Error %i: %s\n",
            reg_addr,
            dev_addr,
            errno,
            strerror(errno));
        return false;
    }
    return true;
}
