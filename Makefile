TARGET = bmp_header
SRC_DIR = src
OBJ_DIR = obj
CFLAGS = -Wall -Wextra -pedantic -Werror -O2
CC = gcc
SRC_FILES = $(shell find $(SRC_DIR) -name '*.c')
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
format:
	find . -regex '.*\.\(c\|h\|cpp\|hpp\)' -exec clang-format -style=file -i {} \;
.PHONY: clean format
