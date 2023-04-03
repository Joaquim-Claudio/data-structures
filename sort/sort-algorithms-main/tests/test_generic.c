#include <stdlib.h>
#include "unity/unity.h"

#include "../src/sort.h"

#define NUMBERS_SIZE 10
int** numbers;

void setUp(void) {
    numbers = (int**)malloc(sizeof(int*) * NUMBERS_SIZE);
    for (int i = 0; i < NUMBERS_SIZE; i++) {
        numbers[i] = (int*)malloc(sizeof(int));
    }
    *(numbers[0]) = 7;
    *(numbers[1]) = 1;
    *(numbers[2]) = 2;
    *(numbers[3]) = 8;
    *(numbers[4]) = 3;
    *(numbers[5]) = 10;
    *(numbers[6]) = 9;
    *(numbers[7]) = 6;
    *(numbers[8]) = 5;
    *(numbers[9]) = 4;
}

void tearDown(void) {
    for (int i = 0; i < NUMBERS_SIZE; i++) {
        free(numbers[i]);
    }
    free(numbers);
}

int compare(int* a, int* b) {
    return *a - *b;
}

void test_generic_int_array(void) {
    sort((comparable*)numbers, NUMBERS_SIZE, (int (*)(comparable, comparable))compare);
    for (int i = 0; i < NUMBERS_SIZE; i++) {
        TEST_ASSERT_EQUAL_INT(i + 1, *(numbers[i]));
    }
}

void test_generic_single_element_array(void) {
    int** small_numbers = (int**)malloc(sizeof(int*) * 1);
    small_numbers[0] = (int*)malloc(sizeof(int));
    *(small_numbers[0]) = 1;
    sort((comparable*)small_numbers, 1, (int (*)(comparable, comparable))compare);
    TEST_ASSERT_EQUAL_INT(1, *(small_numbers[0]));
    free(small_numbers[0]);
    free(small_numbers);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_generic_int_array);
    RUN_TEST(test_generic_single_element_array);
    return UNITY_END();
}