#include "data.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_DATA_VEC_CAPACITY      100
#define DEFAULT_DATA_VEC_GROWTH_FACTOR 2

bool
write_data_to_file(const char *file_path, data_t data)
{
    FILE *file = fopen(file_path, "a");

    if (file == NULL)
    {
        fprintf(stderr, "Failed to open file: \"%s\"\n", file_path);
        return false;
    }

    bool         ret_val    = true;
    const size_t write_size = fwrite(&data, sizeof(data_t), 1, file);
    if (write_size < 1)
    {
        fprintf(stderr, "Failed to write data to file: \"%s\"\n", file_path);
        ret_val = false;
    }

    fclose(file);
    return ret_val;
}

bool
read_data_from_file(const char *file_path, data_t **data, size_t *n_data_points)
{
    FILE *file = fopen(file_path, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Failed to open file: \"%s\"\n", file_path);
        return false;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    assert(file_size % sizeof(data_t) == 0);
    if (file_size % sizeof(data_t) != 0)
    {
        printf(
            "Binary content of: \"%s\", is not an integer multiple of "
            "sizeof(data_t)\n",
            file_path);
        file_size = (file_size / sizeof(data_t)) * sizeof(data_t);
    }

    bool  ret_val = true;
    char *buf     = malloc(file_size);
    if (buf == NULL)
    {
        fprintf(stderr, "Failed to allocate %u bytes of memory\n", file_size);
        ret_val = false;
    }
    else
    {
        const size_t n_data_points_expected = file_size / sizeof(data_t);
        const size_t n_data_points_read
            = fread(buf, sizeof(data_t), n_data_points_expected, file);
        if (n_data_points_read != n_data_points_expected)
        {
            fprintf(stderr,
                    "Failed to read %u data points from the file: \"%s\" "
                    "(actual num points read: %u)\n",
                    n_data_points_expected,
                    file_path,
                    n_data_points_read);
            free(buf);
            ret_val = false;
        }
        else
        {
            *data          = (data_t *)buf;
            *n_data_points = n_data_points_read;
        }
    }

    fclose(file);
    return ret_val;
}

bool
data_vec_create(data_vec_t *data_vec)
{
    data_vec->capacity      = 0;
    data_vec->n_data_points = 0;
    data_vec->data          = NULL;

    data_vec->data
        = (data_t *)malloc(DEFAULT_DATA_VEC_CAPACITY * sizeof(data_t));
    if (data_vec->data == NULL)
    {
        fprintf(
            stderr,
            "Failed to allocate initial data_vec_t memory (size: %u bytes)\n",
            DEFAULT_DATA_VEC_CAPACITY * sizeof(data_t));
        return false;
    }

    data_vec->capacity = DEFAULT_DATA_VEC_CAPACITY;
    return true;
}

void
data_vec_init(data_vec_t *data_vec, data_t *data, size_t n_data_points)
{
    data_vec->capacity      = n_data_points;
    data_vec->n_data_points = n_data_points;
    data_vec->data          = data;
}

bool
data_vec_push(data_vec_t *data_vec, data_t data)
{
    if (data_vec->n_data_points == data_vec->capacity)
    {
        const size_t new_capacity
            = DEFAULT_DATA_VEC_GROWTH_FACTOR * data_vec->capacity;
        data_t *new_data_buf = (data_t *)malloc(new_capacity * sizeof(data_t));

        if (new_data_buf == NULL)
        {
            fprintf(
                stderr,
                "Data vec at capcity but failed to allocate additional memory, "
                "could not push new data to vec (alloc size: %u bytes)\n",
                new_capacity);
            return false;
        }

        memcpy(
            new_data_buf, data_vec->data, data_vec->capacity * sizeof(data_t));
        free(data_vec->data);
        data_vec->data     = new_data_buf;
        data_vec->capacity = new_capacity;
    }

    data_vec->data[data_vec->n_data_points++] = data;

    return true;
}

void
data_vec_destroy(data_vec_t *data_vec)
{
    data_vec->capacity      = 0;
    data_vec->n_data_points = 0;
    free(data_vec->data);
}
