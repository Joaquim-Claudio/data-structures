#include "unity/unity.h"

#include "../src/hash_table.h"

#include <stdlib.h>
#include <string.h>
// #include <mcheck.h>
#include <stdbool.h>

HashTable htable;

int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
char* key_num[] = {"num_one", "num_two", "num_three", "num_four", "num_five", "num_six", "num_seven", "num_eight", "num_nine", "num_ten"};
char* strings[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
char* key_string[] = {"str_one", "str_two", "str_three", "str_four", "str_five", "str_six", "str_seven", "str_eight", "str_nine", "str_ten"};

// Hash function
int hash_function(void* key, int size){
    int result = 0, a = 127;
    char* key_str = (char*)key;
    for(int i = 0; key_str[i] != '\0'; i++){
        result = (result*a + key_str[i]) % size;
    }
    return result;
}
// End of hash function

void setUp(void) {
    htable = hash_table_create(DEFAULT_SIZE, (int(*)(void*, int))hash_function, NULL, NULL);
}

void tearDown(void) {
    hash_table_destroy(htable, NULL);
}

/*******************************************************************************
 Helper functions.
 ******************************************************************************/

bool is_equal(void* a, void* b) {
    return a == b;
}

void insert_numbers(int start, int end) {
    for (int i = start - 1; i < end; i++) {
        hash_table_insert(htable, &numbers[i] ,&numbers[i]);
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
       hash_table_insert(htable, &strings[i], &strings[i]);
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

void test_hash_table_is_empty() {
    TEST_ASSERT(hash_table_is_empty(htable));
}

void test_hash_table_size() {
    TEST_ASSERT_EQUAL(0, hash_table_size(htable));
    insert_numbers(1, 1);
    TEST_ASSERT_EQUAL(1, hash_table_size(htable));
    insert_strings(3, 3);
    TEST_ASSERT_EQUAL(2, hash_table_size(htable));
}

void test_hash_table_get() {
    TEST_ASSERT_NULL(hash_table_get(htable, &key_num[0]));
    insert_numbers(1, 5);
    TEST_ASSERT_EQUAL(number_address_of(2), hash_table_get(htable, &key_num[1]));
}

void test_hash_table_insert() {
    TEST_ASSERT_EQUAL(0, hash_table_size(htable));
    TEST_ASSERT_NULL(hash_table_get(htable, &key_num[0]));
    hash_table_insert(htable, &key_num[0],&numbers[0]);
    TEST_ASSERT_EQUAL(1, hash_table_size(htable));
    TEST_ASSERT_EQUAL(&numbers[0], hash_table_get(htable, &key_num[0]));
    insert_strings(1, 3);
    hash_table_insert(htable, &key_num[1],&numbers[1]);
    TEST_ASSERT_EQUAL(5, hash_table_size(htable));
    TEST_ASSERT_EQUAL(&numbers[1], hash_table_get(htable, &key_num[1]));
    hash_table_insert(htable, key_num[2],&numbers[2]);
    TEST_ASSERT_EQUAL(6, hash_table_size(htable));
    TEST_ASSERT_EQUAL(&numbers[2], hash_table_get(htable, key_num[2]));
}

void test_hash_table_remove() {
    TEST_ASSERT_NULL(hash_table_remove(htable, &key_num[3]));
    insert_strings(1, 6);
    TEST_ASSERT_EQUAL(string_address_of(1), hash_table_remove(htable, &key_string[0]));
    TEST_ASSERT_EQUAL(string_address_of(6), hash_table_remove(htable, &key_string[5]));
    TEST_ASSERT_EQUAL(string_address_of(4), hash_table_remove(htable, &key_string[3]));
    TEST_ASSERT_EQUAL(string_address_of(5), hash_table_remove(htable, &key_string[4]));
    TEST_ASSERT_EQUAL(2, hash_table_size(htable));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_hash_table_is_empty);
    // RUN_TEST(test_hash_table_size);
    // RUN_TEST(test_hash_table_get);
    // RUN_TEST(test_hash_table_insert);
    // RUN_TEST(test_hash_table_remove);
    return UNITY_END();
}