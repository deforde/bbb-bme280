file(GLOB SOURCES *.c)

target_sources(bbb-bme280
PRIVATE
    ${SOURCES}
)
