#include <stdlib.h>
#include "hash_table.h"

typedef struct{
    void* key;
    void* value;
    bool (*key_equal)(void*, void*);
    void (*key_destroy)(void*);
}t_Item, *Item;


struct t_HashTable{
    int size;
    int num_elements;
    List* table;
    bool (*key_equal)(void*, void*);
    void (*key_destroy)(void*);
    int (*hash)(void*, int);
};

/// Creates a new hash table.
HashTable hash_table_create(int size, int (*hash)(void*, int), bool (*key_equal)(void*, void*), void(*key_destroy)(void*)){
    HashTable htable = malloc(sizeof(struct t_HashTable));
    htable->size = size;
    htable->num_elements = 0;
    htable->hash = hash;
    htable->key_equal = key_equal;
    htable->key_destroy = key_destroy;
    htable->table = malloc(sizeof(List) * size);
    for(int i = 0; i < size; i++){
        htable->table[i] = list_create();
    }
    return htable;
}

// Destroys a hash table.
void hash_table_destroy(HashTable table, void (*value_destroy)(void*)){
    for(int i = 0; i < table->size; i++){
        while(!list_is_empty(table->table[i])){
            void* value = list_remove_last(table->table[i]);
            if(value_destroy != NULL){
                value_destroy(value);
            }
        }
        list_destroy(table->table[i], NULL);
    }
    free(table->table);
    free(table);
}

// Returns true if the hash table contains no elements.
bool hash_table_is_empty(HashTable table){
    return table->num_elements == 0;
}

// Auxiliar function
        Item create_item(void* key, void* value){
            Item item = malloc(sizeof(t_Item));
            item->key = key;
            item->value = value;
            return item;
        }
// End of auxiliar function

// Inserts a new key-value pair into the hash table.
void hash_table_insert(HashTable table, void* key, void* value){
    int index = table->hash(key, table->size);
    List list = table->table[index];
    Item item = create_item(key, value);
    list_insert_last(list, item);
    table->num_elements++;
}

// Removes a key-value pair from the hash table.
void* hash_table_remove(HashTable table, void* key){
    return NULL;
}

// Returns the value associated with the key.
void* hash_table_get(HashTable table, void* key){
    int index = table->hash(key, table->size);
    Item item = list_get_last(table->table[index]);
    if(item != NULL && item->key == key){
        return item->value;
    }
    return NULL;
}

// Updates the value associated with the key.
void* hash_table_update(HashTable table, void* key, void* value){
    return NULL;
}

// Returns the number of elements in the hash table.
int hash_table_size(HashTable table){
    return table->num_elements;
}

// Returns true if the hash table contains no elements.
List hash_table_keys(HashTable table){
    return NULL;
}

// Returns the keys of the hash table.
List hash_table_values(HashTable table){
    return NULL;
}

// Returns the values of the hash table.
List hash_table_entries(HashTable table){
    return NULL;
}

// Returns the entries of the hash table.
void hash_table_rehash(HashTable table, int new_size){
    return NULL;
}