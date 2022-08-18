TARGET_EXEC := bbb-bme280

BUILD_DIR := build
SRC_DIRS := src

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d) -Ilibmicrohttpd/include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CFLAGS := -Wall -Wextra -Wpedantic -Werror -Wno-format -Wno-strict-aliasing -Wno-incompatible-pointer-types $(INC_FLAGS) -MMD -MP
LDFLAGS := -Llibmicrohttpd/lib -lmicrohttpd

EXECUTABLE := $(BUILD_DIR)/$(TARGET_EXEC)

all: CFLAGS += -O3
all: executable

debug: CFLAGS += -g3 -D_FORTIFY_SOURCE=2
debug: executable

san: debug
san: CFLAGS += -fsanitize=address,undefined
san: LDFLAGS += -fsanitize=address,undefined

executable: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean compdb valgrind libmicrohttpd

clean:
	@rm -rf $(BUILD_DIR)

compdb: clean
	@bear -- $(MAKE) san && \
	 mv compile_commands.json build

valgrind: debug
	@valgrind ./$(EXECUTABLE)

libmicrohttpd:
	rm -rf libmicrohttpd-latest && \
	mkdir libmicrohttpd-latest && \
	cd libmicrohttpd-latest && \
	curl -LO https://mirrors.ocf.berkeley.edu/gnu/libmicrohttpd/libmicrohttpd-latest.tar.gz && \
	tar --strip-components=1 -xz -f libmicrohttpd-latest.tar.gz && \
	rm libmicrohttpd-latest.tar.gz && \
	cd .. && \
	mkdir libmicrohttpd && \
	cd libmicrohttpd-latest && \
	./configure --prefix=$$PWD/../libmicrohttpd && \
	make && \
	make install && \
	cd .. && \
	rm -rf libmicrohttpd-latest

-include $(DEPS)
