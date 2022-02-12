#ifndef PLOT_H
#define PLOT_H

#include <stddef.h>
#include <stdint.h>

#include "data.h"

char *plot_generate_html(const data_t *data, size_t n_data_points);

#endif // PLOT_H
