#ifndef DATA_H
#define DATA_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
  uint64_t timestamp_ns;
  float t_degC;
  float p_kPa;
  float humidity_pcnt;
} data_t;

typedef struct {
  data_t *data;
  size_t n_data_points;
  size_t capacity;
} data_vec_t;

bool write_data_to_file(const char *file_path, data_t data);
bool read_data_from_file(const char *file_path, data_t **data,
                         size_t *n_data_points);

bool data_vec_create(data_vec_t *data_vec);
void data_vec_init(data_vec_t *data_vec, data_t *data, size_t n_data_points);
bool data_vec_push(data_vec_t *data_vec, data_t data);
void data_vec_destroy(data_vec_t *data_vec);

#endif // DATA_H
