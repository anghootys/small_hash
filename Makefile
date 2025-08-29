CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = tests/test
SRC = tests/test_sh_create_hash_table.c
INCLUDE = include

.PHONY: all clean test

all: clean $(TARGET) test

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -I$(INCLUDE) $^ -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
