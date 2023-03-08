BUILD:=release
BUILD:=debug
BUILD:=debug_cov

CC=gcc
SRC=./src
BIN=./bin
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

TARGETS += singly_linked_list

# Create output directories
_BUILD_BIN::=$(shell mkdir -p $(BIN))
_BUILD_TESTS_BIN::=$(shell mkdir -p $(TESTS_BIN))
_BUILD_COV::=$(shell mkdir -p $(COV))

all: singly_linked_list

# Singly Linked List

singly_linked_list: $(BIN)/singly_linked_list.o $(TESTS_BIN)/test_singly_linked_list

$(BIN)/singly_linked_list.o: $(SRC)/singly_linked_list.c
	$(CC) -c $(CFLAGS) $< -o $@

## Tests

# Singly Linked List

$(TESTS_BIN)/test_singly_linked_list: $(TESTS_SRC)/test_list.c $(BIN)/singly_linked_list.o $(UNITY)
	$(CC) $(CFLAGS) $(TESTS_FLAGS) $^ -o $@

# Compile Unity

$(UNITY): $(UNITY_SRC)/unity.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: all tests clean

tests: all
	$(TESTS_BIN)/test_singly_linked_list

tests_memory: all
	valgrind --leak-check=full -s $(TESTS_BIN)/test_singly_linked_list

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
