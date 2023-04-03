SRC=./src
BIN=./bin
TESTS_SRC=./tests
TESTS_BIN=$(TESTS_SRC)/bin
COV=$(TESTS_BIN)/cov
UNITY_SRC=./tests/unity
UNITY=$(TESTS_BIN)/unity.o
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
# gcov
CFLAGS += -fprofile-arcs
CFLAGS += -ftest-coverage
# unity
TESTS_FLAGS=-Wno-implicit-function-declaration

TARGETS += bubblesort_int bubblesort_generic
TARGETS += quicksort_int quicksort_generic

# Create output directories
_BUILD_BIN::=$(shell mkdir -p $(BIN))
_BUILD_TESTS_BIN::=$(shell mkdir -p $(TESTS_BIN))
_BUILD_COV::=$(shell mkdir -p $(COV))

all: bubblesort quicksort

# BubbleSort

bubblesort: bubblesort_int bubblesort_generic

bubblesort_int: $(BIN)/bubblesort_int.o $(TESTS_BIN)/test_bubblesort_int

$(BIN)/bubblesort_int.o: $(SRC)/bubblesort_int.c
	$(CC) -c $(CFLAGS) $< -o $@

bubblesort_generic: $(BIN)/bubblesort_generic.o $(TESTS_BIN)/test_bubblesort_generic

$(BIN)/bubblesort_generic.o: $(SRC)/bubblesort_generic.c
	$(CC) -c $(CFLAGS) $< -o $@

# QuickSort

quicksort: quicksort_int quicksort_generic

quicksort_int: $(BIN)/quicksort_int.o $(TESTS_BIN)/test_quicksort_int

$(BIN)/quicksort_int.o: $(SRC)/quicksort_int.c
	$(CC) -c $(CFLAGS) $< -o $@

quicksort_generic: $(BIN)/quicksort_generic.o $(TESTS_BIN)/test_quicksort_generic

$(BIN)/quicksort_generic.o: $(SRC)/quicksort_generic.c
	$(CC) -c $(CFLAGS) $< -o $@

## Tests

# BubbleSort

$(TESTS_BIN)/test_bubblesort_int: $(TESTS_SRC)/test_int.c $(BIN)/bubblesort_int.o $(UNITY)
	$(CC) $(CFLAGS) $(TESTS_FLAGS) $^ -o $@

$(TESTS_BIN)/test_bubblesort_generic: $(TESTS_SRC)/test_generic.c $(BIN)/bubblesort_generic.o $(UNITY)
	$(CC) $(CFLAGS) $(TESTS_FLAGS) $^ -o $@

# QuickSort

$(TESTS_BIN)/test_quicksort_int: $(TESTS_SRC)/test_int.c $(BIN)/quicksort_int.o $(UNITY)
	$(CC) $(CFLAGS) $(TESTS_FLAGS) $^ -o $@

$(TESTS_BIN)/test_quicksort_generic: $(TESTS_SRC)/test_generic.c $(BIN)/quicksort_generic.o $(UNITY)
	$(CC) $(CFLAGS) $(TESTS_FLAGS) $^ -o $@

$(UNITY): $(UNITY_SRC)/unity.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: all tests clean

tests: all
	$(TESTS_BIN)/test_bubblesort_int
	$(TESTS_BIN)/test_bubblesort_generic
	$(TESTS_BIN)/test_quicksort_int
	$(TESTS_BIN)/test_quicksort_generic

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
