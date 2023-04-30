BUILD:=release
BUILD:=debug
BUILD:=debug_cov

CC=gcc
SRC=./src
BIN=./bin
UTILS=./utils
TESTS_SRC=./tests
TESTS_BIN=$(TESTS_SRC)/bin
COV=$(TESTS_BIN)/cov
UNITY_SRC=./tests/unity
UNITY=$(TESTS_BIN)/unity.o

# release flags
CFLAGS.release=-O2

# debug flags
CFLAGS.debug+=-g
CFLAGS.debug+=-Wall
CFLAGS.debug+=-Wextra

# gcov flags
CFLAGS.debug_cov+=$(CFLAGS.debug)
CFLAGS.debug_cov+=-fprofile-arcs
CFLAGS.debug_cov+=-ftest-coverage

CFLAGS:=${CFLAGS.${BUILD}}

# unity
TESTS_FLAGS=-Wno-implicit-function-declaration

TARGETS += hash_table

# Create output directories
_BUILD_BIN::=$(shell mkdir -p $(BIN))
_BUILD_TESTS_BIN::=$(shell mkdir -p $(TESTS_BIN))
_BUILD_COV::=$(shell mkdir -p $(COV))

all: hash_table

# Hash Table

hash_table: $(BIN)/hash_table.o $(TESTS_BIN)/test_hash_table

$(BIN)/hash_table.o: $(SRC)/hash_table.c
	$(CC) -c $(CFLAGS) $< -o $@


$(BIN)/singly_linked_list.o: $(UTILS)/singly_linked_list.c
	$(CC) -c $(CFLAGS) $< -o $@
## Tests

# Hash Table

$(TESTS_BIN)/test_hash_table: $(TESTS_SRC)/test_hash_table.c $(BIN)/hash_table.o $(BIN)/singly_linked_list.o $(UNITY)
	$(CC) $(CFLAGS) $(TESTS_FLAGS) $^ -o $@

# Compile Unity

$(UNITY): $(UNITY_SRC)/unity.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: all tests clean

tests: all
	$(TESTS_BIN)/test_hash_table

tests_memory: all
	valgrind --leak-check=full -s $(TESTS_BIN)/test_hash_table

cov: tests
	mv $(BIN)/*.gcov $(COV) 2>/dev/null || true
	mv $(BIN)/*.gcda $(COV) 2>/dev/null || true
	mv $(BIN)/*.gcno $(COV) 2>/dev/null || true
	$(foreach TARGET,$(TARGETS),gcov $(COV)/$(TARGET).c)
	mv *gcov $(COV)
	gcovr $(COV) -r $(SRC)

clean:
	rm -rf $(BIN)
	rm -rf $(TESTS_BIN)
	rm -rf $(COV)
