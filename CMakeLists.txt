cmake_minimum_required(VERSION 3.0.0)
project(bbb-bme280 C)

add_compile_options(-Wall -Wextra -pedantic -Werror -Werror=vla)

add_executable(bbb-bme280 "")

add_subdirectory(src)
