#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>

#include "data.h"
#include "bme.h"
#include "i2c.h"

#define I2C_DEV_NAME "/dev/i2c-2"
#define DATA_STORE_FILE_PATH "data.bin"
#define MEASUREMENT_PERIOD_S 1

int
main()
{
    data_vec_t data_vec = {
        .capacity = 0,
        .n_data_points = 0,
        .data = NULL
    };
    {
        data_t* data = NULL;
        size_t n_data_points = 0;
        if (read_data_from_file(DATA_STORE_FILE_PATH, &data, &n_data_points))
        {
            data_vec_init(&data_vec, data, n_data_points);
        }
        else
        {
            data_vec_create(&data_vec);
        }
    }

    int i2c_dev = 0;
    if (!i2c_init(I2C_DEV_NAME, &i2c_dev))
    {
        return EXIT_FAILURE;
    }

    for (;;)
    {
        if (!bme_configure(i2c_dev))
        {
            return EXIT_FAILURE;
        }

        float   t_degC = 0.0f;
        int32_t t_fine = 0;
        if (!bme_get_temp(i2c_dev, &t_degC, &t_fine))
        {
            return EXIT_FAILURE;
        }
        printf("t_degC = %.2f degrees Celsius\n", t_degC);

        float p_kPa = 0.0f;
        if (!bme_get_pressure(i2c_dev, t_fine, &p_kPa))
        {
            return EXIT_FAILURE;
        }
        printf("p_kPa = %.2f kPa\n", p_kPa);

        float humidity_pcnt = 0.0f;
        if (!bme_get_humidity(i2c_dev, t_fine, &humidity_pcnt))
        {
            return EXIT_FAILURE;
        }
        printf("humidity_pcnt = %.2f %%\n", humidity_pcnt);

        uint64_t timestamp_ns = 0;
        time_t current_time = time(NULL);
        if (current_time != (time_t)(-1))
        {
            timestamp_ns = (intmax_t)current_time;
            data_t data = {
                .timestamp_ns = timestamp_ns,
                .t_degC = t_degC,
                .p_kPa = p_kPa,
                .humidity_pcnt = humidity_pcnt
            };
            write_data_to_file(DATA_STORE_FILE_PATH, data);
            data_vec_push(&data_vec, data);
        }

        sleep(MEASUREMENT_PERIOD_S);
    }

    return EXIT_SUCCESS;
}
