#ifndef PLOT_H
#define PLOT_H

#include <stddef.h>
#include <stdint.h>

char* plot_generate_html(const char* title, const char* y_axis_label, const char* plot_label, const char* legend_label, size_t n_data_points, uint64_t* time_data_ms, float* temp_data);

#endif //PLOT_H
