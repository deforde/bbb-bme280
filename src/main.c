#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <microhttpd.h>
#include <unistd.h>

#include "bme.h"
#include "data.h"
#include "i2c.h"
#include "plot.h"

#define I2C_DEV_NAME "/dev/i2c-2"
#define DATA_STORE_FILE_PATH "data.bin"
#define MEASUREMENT_PERIOD_S 1

#define PORT 8888

data_vec_t data_vec = {.capacity = 0, .n_data_points = 0, .data = NULL};

enum MHD_Result send_plot_response(void *cls __attribute__((unused)),
                                   struct MHD_Connection *connection,
                                   const char *url __attribute__((unused)),
                                   const char *method __attribute__((unused)),
                                   const char *version __attribute__((unused)),
                                   const char *upload_data
                                   __attribute__((unused)),
                                   unsigned int *upload_data_size
                                   __attribute__((unused)),
                                   void **con_cls __attribute__((unused))) {
  struct MHD_Response *response;
  int ret;

  char *page_str = plot_generate_html(data_vec.data, data_vec.n_data_points);

  // FILE* file = fopen("tmp.html", "w");
  // fwrite(page_str, strlen(page_str), 1, file);
  // fclose(file);

  response = MHD_create_response_from_buffer(strlen(page_str), (void *)page_str,
                                             MHD_RESPMEM_PERSISTENT);
  ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  MHD_destroy_response(response);

  free(page_str);

  return ret;
}

int main() {
  {
    data_t *data = NULL;
    size_t n_data_points = 0;
    if (read_data_from_file(DATA_STORE_FILE_PATH, &data, &n_data_points)) {
      data_vec_init(&data_vec, data, n_data_points);
    } else {
      data_vec_create(&data_vec);
    }
  }

  int i2c_dev = 0;
  if (!i2c_init(I2C_DEV_NAME, &i2c_dev)) {
    return EXIT_FAILURE;
  }

  struct MHD_Daemon *daemon =
      MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL,
                       &send_plot_response, NULL, MHD_OPTION_END);
  if (daemon == NULL)
    return EXIT_FAILURE;

  for (;;) {
    if (!bme_configure(i2c_dev)) {
      return EXIT_FAILURE;
    }

    float t_degC = 0.0f;
    int32_t t_fine = 0;
    if (!bme_get_temp(i2c_dev, &t_degC, &t_fine)) {
      return EXIT_FAILURE;
    }
    // printf("t_degC = %.2f degrees Celsius\n", t_degC);

    float p_kPa = 0.0f;
    if (!bme_get_pressure(i2c_dev, t_fine, &p_kPa)) {
      return EXIT_FAILURE;
    }
    // printf("p_kPa = %.2f kPa\n", p_kPa);

    float humidity_pcnt = 0.0f;
    if (!bme_get_humidity(i2c_dev, t_fine, &humidity_pcnt)) {
      return EXIT_FAILURE;
    }
    // printf("humidity_pcnt = %.2f %%\n", humidity_pcnt);

    uint64_t timestamp_ns = 0;
    time_t current_time = time(NULL);
    if (current_time != (time_t)(-1)) {
      timestamp_ns = (intmax_t)current_time * 1000000000;
      data_t data = {.timestamp_ns = timestamp_ns,
                     .t_degC = t_degC,
                     .p_kPa = p_kPa,
                     .humidity_pcnt = humidity_pcnt};
      write_data_to_file(DATA_STORE_FILE_PATH, data);
      data_vec_push(&data_vec, data);
    }

    sleep(MEASUREMENT_PERIOD_S);
  }

  MHD_stop_daemon(daemon);
  return EXIT_SUCCESS;
}
