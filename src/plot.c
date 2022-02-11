#include "plot.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static const char* html_0 = "\n<!DOCTYPE html>\n<html lang=\"en\">\n  <head>\n    <meta charset=\"utf-8\">\n      <title>Bokeh Plot</title>\n      <script type=\"text/javascript\" src=\"https://cdn.bokeh.org/bokeh/release/bokeh-2.4.2.min.js\"></script>\n        <script type=\"text/javascript\">\n            Bokeh.set_log_level(\"info\");\n        </script>\n  </head>\n  <body>\n    <div class=\"bk-root\" id=\"802ed0ae-ead0-4f90-800f-a86e937b30e4\" data-root-id=\"1002\"></div>\n        <script type=\"application/json\" id=\"1334\">\n          {\"8310fd92-6954-4983-98de-917ac13c82d1\":{\"defs\":[],\"roots\":{\"references\":[{\"attributes\":{},\"id\":\"1005\",\"type\":\"DataRange1d\"},{\"attributes\":{\"days\":[\"%Y/%m/%dT%H:%M:%S\"],\"hours\":[\"%Y/%m/%dT%H:%M:%S\"],\"minutes\":[\"%Y/%m/%dT%H:%M:%S\"],\"months\":[\"%Y/%m/%dT%H:%M:%S\"],\"seconds\":[\"%Y/%m/%dT%H:%M:%S\"],\"years\":[\"%Y/%m/%dT%H:%M:%S\"]},\"id\":\"1029\",\"type\":\"DatetimeTickFormatter\"},{\"attributes\":{},\"id\":\"1007\",\"type\":\"DataRange1d\"},{\"attributes\":{\"below\":[{\"id\":\"1013\"}],\"center\":[{\"id\":\"1016\"},{\"id\":\"1020\"},{\"id\":\"1059\"}],\"left\":[{\"id\":\"1017\"}],\"renderers\":[{\"id\":\"1036\"}],\"sizing_mode\":\"stretch_both\",\"title\":{\"id\":\"1003\"},\"toolbar\":{\"id\":\"1025\"},\"toolbar_location\":\"above\",\"x_range\":{\"id\":\"1005\"},\"x_scale\":{\"id\":\"1009\"},\"y_range\":{\"id\":\"1007\"},\"y_scale\":{\"id\":\"1011\"}},\"id\":\"1002\",\"subtype\":\"Figure\",\"type\":\"Plot\"},{\"attributes\":{},\"id\":\"1040\",\"type\":\"BasicTickFormatter\"},{\"attributes\":{},\"id\":\"1041\",\"type\":\"AllLabels\"},{\"attributes\":{\"num_minor_ticks\":5,\"tickers\":[{\"id\":\"1047\"},{\"id\":\"1048\"},{\"id\":\"1049\"},{\"id\":\"1050\"},{\"id\":\"1051\"},{\"id\":\"1052\"},{\"id\":\"1053\"},{\"id\":\"1054\"},{\"id\":\"1055\"},{\"id\":\"1056\"},{\"id\":\"1057\"},{\"id\":\"1058\"}]},\"id\":\"1014\",\"type\":\"DatetimeTicker\"},{\"attributes\":{\"coordinates\":null,\"group\":null,\"text\":\"";
static const char* html_1 = "\"},\"id\":\"1003\",\"type\":\"Title\"},{\"attributes\":{},\"id\":\"1009\",\"type\":\"LinearScale\"},{\"attributes\":{\"line_color\":\"#1f77b4\",\"line_width\":2,\"x\":{\"field\":\"x\"},\"y\":{\"field\":\"y\"}},\"id\":\"1033\",\"type\":\"Line\"},{\"attributes\":{\"data\":{\"x\":[";
static const char* html_2 = "],\"y\":[";
static const char* html_3 = "]},\"selected\":{\"id\":\"1045\"},\"selection_policy\":{\"id\":\"1044\"}},\"id\":\"1032\",\"type\":\"ColumnDataSource\"},{\"attributes\":{\"bottom_units\":\"screen\",\"coordinates\":null,\"fill_alpha\":0.5,\"fill_color\":\"lightgrey\",\"group\":null,\"left_units\":\"screen\",\"level\":\"overlay\",\"line_alpha\":1.0,\"line_color\":\"black\",\"line_dash\":[4,4],\"line_width\":2,\"right_units\":\"screen\",\"syncable\":false,\"top_units\":\"screen\"},\"id\":\"1024\",\"type\":\"BoxAnnotation\"},{\"attributes\":{\"axis_label\":\"";
static const char* html_4 = "\",\"coordinates\":null,\"formatter\":{\"id\":\"1040\"},\"group\":null,\"major_label_policy\":{\"id\":\"1041\"},\"ticker\":{\"id\":\"1018\"}},\"id\":\"1017\",\"type\":\"LinearAxis\"},{\"attributes\":{\"axis\":{\"id\":\"1017\"},\"coordinates\":null,\"dimension\":1,\"group\":null,\"ticker\":null},\"id\":\"1020\",\"type\":\"Grid\"},{\"attributes\":{},\"id\":\"1043\",\"type\":\"AllLabels\"},{\"attributes\":{\"coordinates\":null,\"group\":null,\"items\":[{\"id\":\"1060\"}]},\"id\":\"1059\",\"type\":\"Legend\"},{\"attributes\":{},\"id\":\"1018\",\"type\":\"BasicTicker\"},{\"attributes\":{\"line_alpha\":0.2,\"line_color\":\"#1f77b4\",\"line_width\":2,\"x\":{\"field\":\"x\"},\"y\":{\"field\":\"y\"}},\"id\":\"1035\",\"type\":\"Line\"},{\"attributes\":{\"line_alpha\":0.1,\"line_color\":\"#1f77b4\",\"line_width\":2,\"x\":{\"field\":\"x\"},\"y\":{\"field\":\"y\"}},\"id\":\"1034\",\"type\":\"Line\"},{\"attributes\":{\"overlay\":{\"id\":\"1024\"}},\"id\":\"1022\",\"type\":\"BoxZoomTool\"},{\"attributes\":{},\"id\":\"1021\",\"type\":\"PanTool\"},{\"attributes\":{},\"id\":\"1023\",\"type\":\"ResetTool\"},{\"attributes\":{\"mantissas\":[1,2,5],\"max_interval\":500.0,\"num_minor_ticks\":0},\"id\":\"1047\",\"type\":\"AdaptiveTicker\"},{\"attributes\":{\"base\":60,\"mantissas\":[1,2,5,10,15,20,30],\"max_interval\":1800000.0,\"min_interval\":1000.0,\"num_minor_ticks\":0},\"id\":\"1048\",\"type\":\"AdaptiveTicker\"},{\"attributes\":{\"days\":[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31]},\"id\":\"1050\",\"type\":\"DaysTicker\"},{\"attributes\":{\"axis_label\":\"Time\",\"coordinates\":null,\"formatter\":{\"id\":\"1029\"},\"group\":null,\"major_label_policy\":{\"id\":\"1043\"},\"ticker\":{\"id\":\"1014\"}},\"id\":\"1013\",\"type\":\"DatetimeAxis\"},{\"attributes\":{\"coordinates\":null,\"data_source\":{\"id\":\"1032\"},\"glyph\":{\"id\":\"1033\"},\"group\":null,\"hover_glyph\":null,\"muted_glyph\":{\"id\":\"1035\"},\"name\":\"";
static const char* html_5 = "\",\"nonselection_glyph\":{\"id\":\"1034\"},\"view\":{\"id\":\"1037\"}},\"id\":\"1036\",\"type\":\"GlyphRenderer\"},{\"attributes\":{},\"id\":\"1044\",\"type\":\"UnionRenderers\"},{\"attributes\":{\"base\":24,\"mantissas\":[1,2,4,6,8,12],\"max_interval\":43200000.0,\"min_interval\":3600000.0,\"num_minor_ticks\":0},\"id\":\"1049\",\"type\":\"AdaptiveTicker\"},{\"attributes\":{},\"id\":\"1045\",\"type\":\"Selection\"},{\"attributes\":{\"months\":[0,1,2,3,4,5,6,7,8,9,10,11]},\"id\":\"1054\",\"type\":\"MonthsTicker\"},{\"attributes\":{\"months\":[0,2,4,6,8,10]},\"id\":\"1055\",\"type\":\"MonthsTicker\"},{\"attributes\":{\"days\":[1,4,7,10,13,16,19,22,25,28]},\"id\":\"1051\",\"type\":\"DaysTicker\"},{\"attributes\":{\"days\":[1,15]},\"id\":\"1053\",\"type\":\"DaysTicker\"},{\"attributes\":{\"months\":[0,6]},\"id\":\"1057\",\"type\":\"MonthsTicker\"},{\"attributes\":{\"label\":{\"value\":\"";
static const char* html_6 = "\"},\"renderers\":[{\"id\":\"1036\"}]},\"id\":\"1060\",\"type\":\"LegendItem\"},{\"attributes\":{\"days\":[1,8,15,22]},\"id\":\"1052\",\"type\":\"DaysTicker\"},{\"attributes\":{},\"id\":\"1058\",\"type\":\"YearsTicker\"},{\"attributes\":{\"months\":[0,4,8]},\"id\":\"1056\",\"type\":\"MonthsTicker\"},{\"attributes\":{\"source\":{\"id\":\"1032\"}},\"id\":\"1037\",\"type\":\"CDSView\"},{\"attributes\":{},\"id\":\"1011\",\"type\":\"LinearScale\"},{\"attributes\":{\"axis\":{\"id\":\"1013\"},\"coordinates\":null,\"group\":null,\"ticker\":null},\"id\":\"1016\",\"type\":\"Grid\"},{\"attributes\":{\"logo\":null,\"tools\":[{\"id\":\"1021\"},{\"id\":\"1022\"},{\"id\":\"1023\"}]},\"id\":\"1025\",\"type\":\"Toolbar\"}],\"root_ids\":[\"1002\"]},\"title\":\"Bokeh Application\",\"version\":\"2.4.2\"}}\n        </script>\n        <script type=\"text/javascript\">\n          (function() {\n            const fn = function() {\n              Bokeh.safely(function() {\n                (function(root) {\n                  function embed_document(root) {\n\n                  const docs_json = document.getElementById('1334').textContent;\n                  const render_items = [{\"docid\":\"8310fd92-6954-4983-98de-917ac13c82d1\",\"root_ids\":[\"1002\"],\"roots\":{\"1002\":\"802ed0ae-ead0-4f90-800f-a86e937b30e4\"}}];\n                  root.Bokeh.embed.embed_items(docs_json, render_items);\n\n                  }\n                  if (root.Bokeh !== undefined) {\n                    embed_document(root);\n                  } else {\n                    let attempts = 0;\n                    const timer = setInterval(function(root) {\n                      if (root.Bokeh !== undefined) {\n                        clearInterval(timer);\n                        embed_document(root);\n                      } else {\n                        attempts++;\n                        if (attempts > 100) {\n                          clearInterval(timer);\n                          console.log(\"Bokeh: ERROR: Unable to run BokehJS code because BokehJS library is missing\");\n                        }\n                      }\n                    }, 10, root)\n                  }\n                })(window);\n              });\n            };\n            if (document.readyState != \"loading\") fn();\n            else document.addEventListener(\"DOMContentLoaded\", fn);\n          })();\n        </script>\n  </body>\n</html>\n";

char* plot_generate_html(const char* title, const char* y_axis_label, const char* plot_label, const char* legend_label, size_t n_data_points, uint64_t* time_data_ms, float* temp_data)
{
    char* time_data_str = NULL;
    char* y_data_str = NULL;

    {
        const size_t time_data_str_len = n_data_points * 16;
        time_data_str = malloc(time_data_str_len);
        memset(time_data_str, 0, time_data_str_len);

        size_t time_data_str_idx = 0;
        for(size_t i = 0; i < n_data_points; ++i) {
            time_data_str_idx += snprintf(&time_data_str[time_data_str_idx], time_data_str_len - time_data_str_idx, "%llu,", time_data_ms[i]);
            if(i == (n_data_points - 1)) {
                time_data_str[time_data_str_idx - 1] = 0;
            }
        }
    }

    {
        const size_t y_data_str_len = n_data_points * 6;
        y_data_str = malloc(y_data_str_len);
        memset(y_data_str, 0, y_data_str_len);

        size_t y_data_str_idx = 0;
        for(size_t i = 0; i < n_data_points; ++i) {
            y_data_str_idx += snprintf(&y_data_str[y_data_str_idx], y_data_str_len - y_data_str_idx, "%.2f,", temp_data[i]);
            if(i == (n_data_points - 1)) {
                y_data_str[y_data_str_idx - 1] = 0;
            }
        }
    }

    const size_t total_html_str_len =
        strlen(html_0) +
        strlen(title) +
        strlen(html_1) +
        strlen(time_data_str) +
        strlen(html_2) +
        strlen(y_data_str) +
        strlen(html_3) +
        strlen(y_axis_label) +
        strlen(html_4) +
        strlen(plot_label) +
        strlen(html_5) +
        strlen(legend_label) +
        strlen(html_6) + 1;

    char* html_str = malloc(total_html_str_len);
    memset(html_str, 0, total_html_str_len);
    size_t html_str_idx = 0;

    memcpy(&html_str[html_str_idx], html_0,        strlen(html_0));
    html_str_idx += strlen(html_0);
    memcpy(&html_str[html_str_idx], title,         strlen(title));
    html_str_idx += strlen(title);
    memcpy(&html_str[html_str_idx], html_1,        strlen(html_1));
    html_str_idx += strlen(html_1);
    memcpy(&html_str[html_str_idx], time_data_str, strlen(time_data_str));
    html_str_idx += strlen(time_data_str);
    memcpy(&html_str[html_str_idx], html_2,        strlen(html_2));
    html_str_idx += strlen(html_2);
    memcpy(&html_str[html_str_idx], y_data_str,    strlen(y_data_str));
    html_str_idx += strlen(y_data_str);
    memcpy(&html_str[html_str_idx], html_3,        strlen(html_3));
    html_str_idx += strlen(html_3);
    memcpy(&html_str[html_str_idx], y_axis_label,  strlen(y_axis_label));
    html_str_idx += strlen(y_axis_label);
    memcpy(&html_str[html_str_idx], html_4,        strlen(html_4));
    html_str_idx += strlen(html_4);
    memcpy(&html_str[html_str_idx], plot_label,    strlen(plot_label));
    html_str_idx += strlen(plot_label);
    memcpy(&html_str[html_str_idx], html_5,        strlen(html_5));
    html_str_idx += strlen(html_5);
    memcpy(&html_str[html_str_idx], legend_label,  strlen(legend_label));
    html_str_idx += strlen(legend_label);
    memcpy(&html_str[html_str_idx], html_6,        strlen(html_6));
    html_str_idx += strlen(html_6);

    free(y_data_str);
    free(time_data_str);

    return html_str;
}
