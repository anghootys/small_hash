CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = tests/test_sh_create_hash_table.c \
			tests/test_pv_sh_polynominal_rolling_hash.c
EXE = $(SRC:.c=)
INCLUDE = include

.PHONY: all clean test

all: clean $(EXE) test

%: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE) $^ -o ./bin/$@

test:
	./bin/tests/test_sh_create_hash_table
	./bin/tests/test_pv_sh_polynominal_rolling_hash

clean:
	rm -rf ./bin/tests
	mkdir ./bin/tests
