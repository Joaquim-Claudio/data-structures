#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief A list is a sequence of pointers to elements.
 *
 * The elements can be of any type, but the list itself is homogeneous.
 */
typedef struct List_* List;

/**
 * @brief Creates a new list.
 *
 * @return List The new list.
 */
List list_create();

/**
 * @brief Destroys a list.
 *
 * Frees all memory allocated for the list, and for all elements of the list.
 *
 * @param list The list to destroy.
 * @param free_element The function to free the elements of the list.
 */
void list_destroy(List list, void (*free_element)(void*));

/**
 * @brief Returns true iff the list contains no elements.
 *
 * @param list The linked list.
 * @return true iff the list contains no elements.
 */
bool list_is_empty(List list);

/**
 * @brief Returns the number of elements in the list.
 *
 * @param list The linked list.
 * @return size_t The number of elements in the list.
 */
size_t list_size(List list);

/**
 * @brief Returns the first element of the list.
 *
 * @param list The linked list.
 * @return void* The first element of the list.
 */
void* list_get_first(List list);

/**
 * @brief Returns the last element of the list.
 *
 * @param list The linked list.
 * @return void* The last element of the list.
 */
void* list_get_last(List list);

/**
 * @brief Returns the element at the specified position in the list.
 *
 * Range of valid positions: 0, ..., size()-1.
 *
 * @param list The linked list.
 * @param position The position of the element to return.
 * @return void* The element at the specified position in the list.
 */
void* list_get(List list, size_t position);

/**
 * @brief Returns the position in the list of the first occurrence of the specified element.
 *
 * Returns -1 if the specified element does not occur in the list.
 *
 * @param list The linked list.
 * @param equal The function to compare two elements.
 * @param element The element to search for.
 * @return int The position in the list of the first occurrence of the specified element, or -1 if the specified element does not occur in the list.
 */
int list_find(List list, bool (*equal)(void*, void*), void* element);

/**
 * @brief Inserts the specified element at the first position in the list.
 *
 * @param list The linked list.
 * @param element The element to insert.
 */
void list_insert_first(List list, void* element);

/**
 * @brief Inserts the specified element at the last position in the list.
 *
 * @param list The linked list.
 * @param element The element to insert.
 */
void list_insert_last(List list, void* element);

/**
 * @brief Inserts the specified element at the specified position in the list.
 *
 * Range of valid positions: 0, ..., size().
 * If the specified position is 0, insert corresponds to insertFirst.
 * If the specified position is size(), insert corresponds to insertLast.
 *
 * @param list The linked list.
 * @param element The element to insert.
 * @param position The position at which to insert the specified element.
 */
void list_insert(List list, void* element, size_t position);

/**
 * @brief Removes and returns the element at the first position in the list.
 *
 * @param list The linked list.
 * @return void* The element at the first position in the list.
 */
void* list_remove_first(List list);

/**
 * @brief Removes and returns the element at the last position in the list.
 *
 * @param list The linked list.
 * @return void* The element at the last position in the list.
 */
void* list_remove_last(List list);

/**
 * @brief Removes and returns the element at the specified position in the list.
 *
 * Range of valid positions: 0, ..., size()-1.
 *
 * @param list The linked list.
 * @param position The position of the element to remove.
 * @return void* The element at the specified position in the list.
 */
void* list_remove(List list, size_t position);

/**
 * @brief Removes all elements from the list.
 *
 * @param list The linked list.
 * @param free_element The function to free the elements of the list.
 */
void list_make_empty(List list, void (*free_element)(void*));

/**
 * @brief Returns an array with the elements of the list.
 *
 * @param list The linked list.
 * @param out_array The array to fill with the elements of the list.
 */
void list_to_array(List list, void** out_array);

/**
 * @brief Returns the number of occurrences on an element.
 *
 * @param list The linked list.
 * @param equal The function to compare two elements.
 * @param element The element to search for.
 * @return int The number of occurrences on an element.
 */
int list_count_all(List list, bool (*equal)(void*, void*), void* element);

/**
 * @brief Removes all occurrences of an element, and returns the number of occurrences.
 *
 * @param list The linked list.
 * @param equal_element The function to compare two elements.
 * @param free_element The function to free the elements of the list.
 * @param element The element to search for.
 * @return int The number of occurrences on an element.
 */
int list_remove_all(List list, bool (*equal_element)(void*, void*), void (*free_element)(void*), void* element);

/**
 * @brief Removes all duplicate occurrences of an element.
 *
 * Keeps only the first occurrence, and returns the number of occurrences.
 *
 * @param list The linked list.
 * @param equal_element The function to compare two elements.
 * @param free_element The function to free the elements of the list.
 * @param element The element to search for.
 * @return int The number of occurrences on an element.
 */
int list_remove_duplicates(List list, bool (*equal_element)(void*, void*), void (*free_element)(void*), void* element);

/**
 * @brief Returns the resulting from the join of two lists.
 *
 * Preserves order.
 *
 * @param list1 The first linked list.
 * @param list2 The second linked list.
 * @return List The resulting from the join of two lists.
 */
List list_join(List list1, List list2);

/**
 * @brief Outputs a formatted representation of the list.
 *
 * @param list The linked list.
 * @param print_element The function to print the elements of the list.
 */
void list_print(List list, void (*print_element)(void* element));

/**
 * @brief Returns a list with the elements from start_idx to end_idx.
 *
 * @param list The linked list.
 * @param start_idx The index of the first element to include.
 * @param end_idx The index of the last element to include.
 * @return List A list with the elements from start_idx to end_idx.
 */
List list_get_sublist_between(List list, int start_idx, int end_idx);

/**
 * @brief Returns a list with the elements in the given array of unordered indexes.
 *
 * Returns the size of the array in the out parameter count.
 *
 * @param list The linked list.
 * @param indexes The array of unordered indexes.
 * @param[out] count The size of the array.
 * @return List A list with the elements in the given array of unordered indexes.
 */
List list_get_sublist(List list, int indexes[], int count);

/**
 * @brief Returns a list with the result of the execution of the function func with each element of the list as parameter.
 *
 * @param list The linked list.
 * @param func The function to apply to each element of the list.
 * @return List A list with the result of the execution of the function func with each element of the list as parameter.
 */
List list_map(List list, void* (*func)(void*));

/**
 * @brief Returns a list with the elements that return true when applied with the given function.
 *
 * @param list The linked list.
 * @param func The boolean function to apply to each element of the list.
 * @return List A list with the elements that return true when applied with the given function.
 */
List list_filter(List list, bool (*func)(void*));

#endif