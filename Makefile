HDR = $(shell find ./src -type f -name *.h)
SRC = $(shell find ./src -type f -name *.c)
OBJ = $(SRC:.c=.o)

TESTS = $(shell find ./tests -type f -name *.me)

CC = gcc
GDB = gdb

CC_INCS  = -I./src -I./src/ext
CC_DBG   = -g3 -fsanitize=address -static-libasan
CC_WARNS = -Wall

CC_FLAGS = ${CC_INCS} ${CC_DBG} ${CC_WARNS}

.PHONY: rmlogs clean rebuild

test: mep
	./mep ${TESTS}
# @echo $(TESTS)
# ./test_compiler.sh ./mep $(TESTS)

run: mep
	@./mep

rerun: clean mep
	@./mep

build: mep

rebuild: clean mep

rmlogs:
	@rm -f ./logs/*

clean: rmlogs
	@rm -rf $(shell find . -type f -name *.tok)
	@rm -rf ./mep

mep: ${OBJ}
	${CC} -o $@ $^ ${CC_FLAGS}

%.o: %.c
	${CC} -o $@ -c $^ ${CC_FLAGS}
