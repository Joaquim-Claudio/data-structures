#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>
#include "../utils/list.h"

typedef struct t_HashTable* HashTable;

// Creates a new hash table.
HashTable hash_table_create(int size, int (*hash)(void*, int), bool (*key_equal)(void*, void*), void(*key_destroy)(void*));

// Destroys a hash table.
void hash_table_destroy(HashTable table, void (*value_destroy)(void*));

// Returns true if the hash table contains no elements.
bool hash_table_is_empty(HashTable table);

// Inserts a new key-value pair into the hash table.
void hash_table_insert(HashTable table, void* key, void* value);

// Removes a key-value pair from the hash table.
void* hash_table_remove(HashTable table, void* key);

// Returns the value associated with the key.
void* hash_table_get(HashTable table, void* key);
// Returns the number of elements in the hash table.
int hash_table_size(HashTable table);

// Updates the value associated with the key.
void* hash_table_update(HashTable table, void* key, void* value);

// Returns the keys of the hash table.
List hash_table_keys(HashTable table);

// Returns the values of the hash table.
List hash_table_values(HashTable table);

// Returns the entries of the hash table.
List hash_table_entries(HashTable table);


void hash_table_rehash(HashTable table, int new_size);

#endif