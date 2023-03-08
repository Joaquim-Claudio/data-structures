#include "unity/unity.h"

#include "../src/list.h"

#include <stdlib.h>
#include <string.h>
// #include <mcheck.h>
#include <stdbool.h>

List list;

int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
char* strings[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};

void setUp(void) {
    list = list_create();
}

void tearDown(void) {
    list_destroy(list, NULL);
}

/*******************************************************************************
 Helper functions.
 ******************************************************************************/

bool is_equal(void* a, void* b) {
    return a == b;
}

void insert_numbers(int start, int end) {
    for (int i = start - 1; i < end; i++) {
        list_insert_last(list, &numbers[i]);
    }
}

void insert_number(int number) {
    insert_numbers(number, number);
}

int* number_address_of(int number) {
    return &(numbers[number - 1]);
}

void insert_strings(int start, int end) {
    for (int i = start - 1; i < end; i++) {
        list_insert_last(list, &strings[i]);
    }
}

void insert_string(int str_idx) {
    insert_strings(str_idx, str_idx);
}

char** string_address_of(int str_idx) {
    return &(strings[str_idx - 1]);
}

bool equal_to_string(void** str1, void** str2) {
    return strcmp(*str1, *str2) == 0;
}

void print_str(char** s) {
    printf("[%s]->", *s);
}

void free_str(char** str) {
    free(*str);
}

void free_int(int* i) {
    free(i);
}

/*******************************************************************************
 Tests
 ******************************************************************************/

void test_list_is_empty() {
    TEST_ASSERT(list_is_empty(list));
}

void test_list_size() {
    TEST_ASSERT_EQUAL(0, list_size(list));
    insert_numbers(1, 1);
    TEST_ASSERT_EQUAL(1, list_size(list));
    insert_strings(3, 3);
    TEST_ASSERT_EQUAL(2, list_size(list));
}

void test_list_get_first() {
    TEST_ASSERT_NULL(list_get_first(list));
    insert_numbers(1, 3);
    TEST_ASSERT_EQUAL(number_address_of(1), list_get_first(list));
}

void test_list_get_last() {
    TEST_ASSERT_NULL(list_get_last(list));
    insert_numbers(1, 3);
    TEST_ASSERT_EQUAL(number_address_of(3), list_get_last(list));
}

void test_list_get() {
    TEST_ASSERT_NULL(list_get(list, 0));
    insert_numbers(1, 5);
    TEST_ASSERT_EQUAL(number_address_of(2), list_get(list, 1));
}

void test_list_find() {
    TEST_ASSERT_EQUAL(-1, list_find(list, is_equal, number_address_of(1)));
    insert_numbers(1, 5);
    TEST_ASSERT_EQUAL(2, list_find(list, is_equal, number_address_of(3)));
    TEST_ASSERT_EQUAL(-1, list_find(list, is_equal, number_address_of(10)));
}

void test_list_insert_first() {
    TEST_ASSERT_NULL(list_get_first(list));
    list_insert_first(list, &strings[0]);
    TEST_ASSERT_EQUAL(&strings[0], list_get_first(list));
    list_insert_first(list, &numbers[0]);
    TEST_ASSERT_EQUAL(&numbers[0], list_get_first(list));
}

void test_list_insert_last() {
    TEST_ASSERT_NULL(list_get_last(list));
    list_insert_last(list, &strings[0]);
    TEST_ASSERT_EQUAL(&strings[0], list_get_last(list));
    TEST_ASSERT_EQUAL(1, list_size(list));
    list_insert_last(list, &numbers[0]);
    TEST_ASSERT_EQUAL(&numbers[0], list_get_last(list));
    TEST_ASSERT_EQUAL(2, list_size(list));
}

void test_list_insert() {
    list_insert(list, &numbers[0], 10);
    TEST_ASSERT_EQUAL(0, list_size(list));
    TEST_ASSERT_NULL(list_get_first(list));
    TEST_ASSERT_NULL(list_get_last(list));
    TEST_ASSERT_EQUAL(0, list_size(list));
    list_insert(list, &numbers[0], 0);
    TEST_ASSERT_EQUAL(1, list_size(list));
    TEST_ASSERT_EQUAL(&numbers[0], list_get_first(list));
    insert_strings(1, 3);
    list_insert(list, &numbers[1], 4);
    TEST_ASSERT_EQUAL(5, list_size(list));
    TEST_ASSERT_EQUAL(&numbers[1], list_get_last(list));
    list_insert(list, &numbers[2], 3);
    TEST_ASSERT_EQUAL(6, list_size(list));
    TEST_ASSERT_EQUAL(&numbers[2], list_get(list, 3));
}

void test_list_remove_first() {
    TEST_ASSERT_NULL(list_remove_first(list));
    insert_string(1);
    TEST_ASSERT_EQUAL(string_address_of(1), list_remove_first(list));
    TEST_ASSERT_EQUAL(0, list_size(list));
    insert_numbers(1, 5);
    TEST_ASSERT_EQUAL(5, list_size(list));
    TEST_ASSERT_EQUAL(number_address_of(1), list_get_first(list));
    TEST_ASSERT_EQUAL(number_address_of(1), list_remove_first(list));
    TEST_ASSERT_EQUAL(4, list_size(list));
    TEST_ASSERT_EQUAL(number_address_of(2), list_get_first(list));
}

void test_list_remove_last() {
    TEST_ASSERT_NULL(list_remove_last(list));
    insert_string(1);
    TEST_ASSERT_EQUAL(string_address_of(1), list_remove_last(list));
    TEST_ASSERT_EQUAL(0, list_size(list));
    insert_numbers(1, 5);
    TEST_ASSERT_EQUAL(5, list_size(list));
    TEST_ASSERT_EQUAL(number_address_of(5), list_get_last(list));
    TEST_ASSERT_EQUAL(number_address_of(5), list_remove_last(list));
    TEST_ASSERT_EQUAL(4, list_size(list));
    TEST_ASSERT_EQUAL(number_address_of(4), list_get_last(list));
}

void test_list_remove() {
    TEST_ASSERT_NULL(list_remove(list, 0));
    TEST_ASSERT_NULL(list_remove(list, 10));
    insert_strings(1, 6);
    TEST_ASSERT_EQUAL(string_address_of(1), list_remove(list, 0));
    TEST_ASSERT_EQUAL(string_address_of(6), list_remove(list, list_size(list) - 1));
    TEST_ASSERT_EQUAL(string_address_of(4), list_remove(list, 2));
    TEST_ASSERT_EQUAL(string_address_of(5), list_remove(list, 2));
}

void test_list_make_empty() {
    insert_strings(1, 3);
    insert_numbers(1, 3);
    insert_strings(4, 7);
    TEST_ASSERT_FALSE(list_is_empty(list));
    list_make_empty(list, NULL);
    TEST_ASSERT_TRUE(list_is_empty(list));
    TEST_ASSERT_EQUAL(0, list_size(list));
}

void test_list_make_empty_free_elements() {
    // mtrace();
    char* str = malloc(sizeof(char) * 10);
    strcpy(str, "test");
    list_insert_last(list, &str);
    list_make_empty(list, (void (*)(void*))free_str);
}

void test_list_to_array() {
    insert_strings(1, 3);
    char* array[3];
    list_to_array(list, (void**)array);
    TEST_ASSERT_EQUAL(string_address_of(1), array[0]);
    TEST_ASSERT_EQUAL(string_address_of(2), array[1]);
    TEST_ASSERT_EQUAL(string_address_of(3), array[2]);
}

void test_list_count_all() {
    TEST_ASSERT_EQUAL(0, list_count_all(list, (bool (*)(void*, void*))equal_to_string, &strings[0]));
    insert_strings(1, 3);
    insert_strings(1, 3);
    TEST_ASSERT_EQUAL(2, list_count_all(list, (bool (*)(void*, void*))equal_to_string, &strings[0]));
}

void test_list_remove_all() {
    insert_strings(1, 3);
    insert_strings(2, 3);
    TEST_ASSERT_EQUAL(5, list_size(list));
    TEST_ASSERT_EQUAL(1, list_find(list, (bool (*)(void*, void*))equal_to_string, &strings[1]));
    int count = list_remove_all(list, (bool (*)(void*, void*))equal_to_string, NULL, &strings[1]);
    TEST_ASSERT_EQUAL(2, count);
    TEST_ASSERT_EQUAL(3, list_size(list));
    TEST_ASSERT_EQUAL(-1, list_find(list, (bool (*)(void*, void*))equal_to_string, &strings[1]));
    TEST_ASSERT_EQUAL(string_address_of(3), list_get_last(list));
    count = list_remove_all(list, (bool (*)(void*, void*))equal_to_string, NULL, &strings[2]);
    TEST_ASSERT_EQUAL(2, count);
    TEST_ASSERT_EQUAL(string_address_of(1), list_get_last(list));
    list_insert_last(list, &strings[2]);
    TEST_ASSERT_EQUAL(string_address_of(3), list_get_last(list));
    count = list_remove_all(list, (bool (*)(void*, void*))equal_to_string, NULL, &strings[0]);
    TEST_ASSERT_EQUAL(1, count);
}

void test_list_remove_all_custom_free() {
    char* str = malloc(sizeof(char) * 5);
    strcpy(str, "test");
    insert_strings(1, 3);
    list_insert_last(list, &str);
    insert_strings(4, 5);
    char* str_match = "test";
    int count = list_remove_all(list, (bool (*)(void*, void*))equal_to_string, (void (*)(void*))free_str, &str_match);
    TEST_ASSERT_EQUAL(1, count);
}

void test_list_remove_duplicates() {
    insert_strings(1, 3);
    insert_strings(2, 3);
    TEST_ASSERT_EQUAL(5, list_size(list));
    int count = list_remove_duplicates(list, (bool (*)(void*, void*))equal_to_string, NULL, &strings[1]);
    TEST_ASSERT_EQUAL(2, count);
}

void test_list_join() {
    insert_strings(1, 3);
    List l2 = list_create();
    list_insert_last(l2, &strings[3]);
    list_insert_last(l2, &strings[4]);
    List l = list_join(list, l2);
    TEST_ASSERT_EQUAL(5, list_size(l));
    list_destroy(l2, NULL);
    list_destroy(l, NULL);
}

void test_list_get_sublist_between() {
    insert_strings(1, 5);
    List l = list_get_sublist_between(list, 1, 3);
    TEST_ASSERT_EQUAL(string_address_of(2), list_get(l, 0));
    TEST_ASSERT_EQUAL(string_address_of(3), list_get(l, 1));
    TEST_ASSERT_EQUAL(string_address_of(4), list_get(l, 2));
    list_destroy(l, NULL);
}

void test_list_get_sublist() {
    insert_strings(1, 5);
    int indexes[] = {0, 2, 4};
    List l = list_get_sublist(list, indexes, 3);
    TEST_ASSERT_EQUAL(string_address_of(1), list_get(l, 0));
    TEST_ASSERT_EQUAL(string_address_of(3), list_get(l, 1));
    TEST_ASSERT_EQUAL(string_address_of(5), list_get(l, 2));
    list_destroy(l, NULL);
}

int* multiply_10(int* i) {
    int* r = malloc(sizeof(int));
    *r = *i * 10;
    return r;
}

void test_list_map() {
    insert_numbers(1, 5);
    List l = list_map(list, (void* (*)(void*))multiply_10);
    TEST_ASSERT_EQUAL(10, *(int*)list_get(l, 0));
    TEST_ASSERT_EQUAL(20, *(int*)list_get(l, 1));
    TEST_ASSERT_EQUAL(30, *(int*)list_get(l, 2));
    TEST_ASSERT_EQUAL(40, *(int*)list_get(l, 3));
    TEST_ASSERT_EQUAL(50, *(int*)list_get(l, 4));
    list_destroy(l, (void (*)(void*))free_int);
}

bool is_even(int* i) {
    return *i % 2 == 0;
}

void test_list_filter() {
    insert_numbers(1, 5);
    List l = list_filter(list, (bool (*)(void*))is_even);
    TEST_ASSERT_EQUAL(2, list_size(l));
    TEST_ASSERT_EQUAL(2, *(int*)list_get(l, 0));
    TEST_ASSERT_EQUAL(4, *(int*)list_get(l, 1));
    list_destroy(l, NULL);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_list_is_empty);
    RUN_TEST(test_list_size);
    RUN_TEST(test_list_get_first);
    RUN_TEST(test_list_get_last);
    RUN_TEST(test_list_get);
    RUN_TEST(test_list_find);
    RUN_TEST(test_list_insert_first);
    RUN_TEST(test_list_insert_last);
    RUN_TEST(test_list_insert);
    RUN_TEST(test_list_remove_first);
    RUN_TEST(test_list_remove_last);
    RUN_TEST(test_list_remove);
    RUN_TEST(test_list_make_empty);
    RUN_TEST(test_list_to_array);
    RUN_TEST(test_list_make_empty_free_elements);
    RUN_TEST(test_list_count_all);
    RUN_TEST(test_list_remove_all);
    RUN_TEST(test_list_remove_all_custom_free);
    RUN_TEST(test_list_remove_duplicates);
    RUN_TEST(test_list_join);
    RUN_TEST(test_list_get_sublist_between);
    RUN_TEST(test_list_get_sublist);
    RUN_TEST(test_list_map);
    RUN_TEST(test_list_filter);
    return UNITY_END();
}