#include "plot.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static const char *html_0
    = "<!DOCTYPE html>\n"
      "<html>\n"
      "<script src=\"https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.5.0/Chart.min.js\"></script>\n"
      "<body>\n"
      "<canvas id=\"temp\" style=\"width:100%;max-width:1920px\"></canvas>\n"
      "<canvas id=\"press\" style=\"width:100%;max-width:1920px\"></canvas>\n"
      "<canvas id=\"humid\" style=\"width:100%;max-width:1920px\"></canvas>\n"
      "<script>\n"
      "var xValues = [";
static const char *html_1
    = "];\n"
      "new Chart(\"temp\", {\n"
      "  type: \"line\",\n"
      "  data: {\n"
      "    labels: xValues,\n"
      "    datasets: [{ \n"
      "      data: [";
static const char *html_2
    = "],\n"
      "      borderColor: \"red\",\n"
      "      fill: false\n"
      "    }]\n"
      "  },\n"
      "  options: {\n"
      "    legend: {display: false}\n"
      "  }\n"
      "});\n"
      "new Chart(\"press\", {\n"
      "  type: \"line\",\n"
      "  data: {\n"
      "    labels: xValues,\n"
      "    datasets: [{ \n"
      "      data: [";
static const char *html_3
    = "],\n"
      "      borderColor: \"green\",\n"
      "      fill: false\n"
      "    }]\n"
      "  },\n"
      "  options: {\n"
      "    legend: {display: false}\n"
      "  }\n"
      "});\n"
      "new Chart(\"humid\", {\n"
      "  type: \"line\",\n"
      "  data: {\n"
      "    labels: xValues,\n"
      "    datasets: [{ \n"
      "      data: [";
static const char *html_4
    = "],\n"
      "      borderColor: \"blue\",\n"
      "      fill: false\n"
      "    }]\n"
      "  },\n"
      "  options: {\n"
      "    legend: {display: false}\n"
      "  }\n"
      "});\n"
      "</script>\n"
      "</body>\n"
      "</html>\n";

char *
plot_generate_html(const data_t* const data, size_t n_data_points)
{
    const size_t time_data_str_len = n_data_points * 30;
    char* time_data_str = malloc(time_data_str_len);
    memset(time_data_str, 0, time_data_str_len);

    const size_t temp_data_str_len = n_data_points * 10;
    char *temp_data_str = malloc(temp_data_str_len);
    memset(temp_data_str, 0, temp_data_str_len);

    const size_t press_data_str_len = n_data_points * 10;
    char *press_data_str = malloc(press_data_str_len);
    memset(press_data_str, 0, press_data_str_len);

    const size_t humid_data_str_len = n_data_points * 10;
    char *humid_data_str = malloc(humid_data_str_len);
    memset(humid_data_str, 0, humid_data_str_len);

    size_t time_data_str_idx = 0;
    size_t temp_data_str_idx = 0;
    size_t press_data_str_idx = 0;
    size_t humid_data_str_idx = 0;
    for (size_t i = 0; i < n_data_points; ++i)
    {
        const time_t t = (time_t)((intmax_t)(data[i].timestamp_ns / 1000000000));
        const char* date_str = asctime(localtime(&t));
        const size_t date_str_len = strlen(date_str);
        time_data_str[time_data_str_idx++] = '\"';
        memcpy(&time_data_str[time_data_str_idx], date_str, date_str_len);
        time_data_str_idx += date_str_len - 1;
        time_data_str[time_data_str_idx++] = '\"';

        temp_data_str_idx += snprintf(&temp_data_str[temp_data_str_idx],
                                       temp_data_str_len - temp_data_str_idx,
                                       "%.2f",
                                       data[i].t_degC);

        press_data_str_idx += snprintf(&press_data_str[press_data_str_idx],
                                       press_data_str_len - press_data_str_idx,
                                       "%.2f",
                                       data[i].p_kPa);

        humid_data_str_idx += snprintf(&humid_data_str[humid_data_str_idx],
                                       humid_data_str_len - humid_data_str_idx,
                                       "%.2f",
                                       data[i].humidity_pcnt);

        if (i != (n_data_points - 1))
        {
            time_data_str[time_data_str_idx++] = ',';
            temp_data_str[temp_data_str_idx++] = ',';
            press_data_str[press_data_str_idx++] = ',';
            humid_data_str[humid_data_str_idx++] = ',';
        }
    }

    const size_t total_html_str_len
     = strlen(html_0) + strlen(html_1) + strlen(html_2) + strlen(html_3) + strlen(html_4)
     + strlen(time_data_str)+ strlen(temp_data_str)+ strlen(press_data_str)+ strlen(humid_data_str) + 1;

    char *html_str = malloc(total_html_str_len);
    memset(html_str, 0, total_html_str_len);
    size_t html_str_idx = 0;

    memcpy(&html_str[html_str_idx], html_0, strlen(html_0));
    html_str_idx += strlen(html_0);

    memcpy(&html_str[html_str_idx], time_data_str, strlen(time_data_str));
    html_str_idx += strlen(time_data_str);

    memcpy(&html_str[html_str_idx], html_1, strlen(html_1));
    html_str_idx += strlen(html_1);

    memcpy(&html_str[html_str_idx], temp_data_str, strlen(temp_data_str));
    html_str_idx += strlen(temp_data_str);

    memcpy(&html_str[html_str_idx], html_2, strlen(html_2));
    html_str_idx += strlen(html_2);

    memcpy(&html_str[html_str_idx], press_data_str, strlen(press_data_str));
    html_str_idx += strlen(press_data_str);

    memcpy(&html_str[html_str_idx], html_3, strlen(html_3));
    html_str_idx += strlen(html_3);

    memcpy(&html_str[html_str_idx], humid_data_str, strlen(humid_data_str));
    html_str_idx += strlen(humid_data_str);

    memcpy(&html_str[html_str_idx], html_4, strlen(html_4));
    html_str_idx += strlen(html_4);

    free(humid_data_str);
    free(press_data_str);
    free(temp_data_str);
    free(time_data_str);

    return html_str;
}
