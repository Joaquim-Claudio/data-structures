#include "unity/unity.h"

#include "../src/sort_int.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_simple_int_array(void) {
    int numbers[] = {7, 1, 2, 8, 3, 10, 9, 6, 5, 4};
    sort(numbers, 10);
    TEST_ASSERT_EQUAL_INT_ARRAY(((int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10}), numbers, 10);
}

void test_single_element_array(void) {
    int numbers[] = {1};
    sort(numbers, 1);
    TEST_ASSERT_EQUAL_INT_ARRAY(((int[]){1}), numbers, 1);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_simple_int_array);
    RUN_TEST(test_single_element_array);
    return UNITY_END();
}