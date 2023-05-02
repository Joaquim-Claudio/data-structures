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


/*******************************************************************************
 Helper functions.
 ******************************************************************************/
// Create an item - "element in the list"
        Item create_item(void* key, void* value){
            Item item = malloc(sizeof(t_Item));
            item->key = key;
            item->value = value;
            return item;
        }

// Returns true if the  elements have the same key
        bool equal_element(void* e1, void* e2){
            Item item_e1 = (Item)e1;
            Item item_e2 = (Item)e2;
            return item_e1->key == item_e2->key;
        }

// Returns the element position in the list
        int get_list_position (List list, void* key){
            Item aux_item = create_item(key, NULL);
            int pos = list_find(list, (bool(*)(void*, void*))equal_element, aux_item);
            free(aux_item);
            return pos;
        }

/*******************************************************************************
 End helper functions.
 ******************************************************************************/


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
    int index = table->hash(key, table->size);
    int pos = get_list_position(table->table[index], key);
    Item item = list_remove(table->table[index], pos);
    if(item != NULL){
        void* value = item->value;
        free(item);
        table->num_elements--;
        return value;
    }
    return NULL;
}

// Returns the value associated with the key.
void* hash_table_get(HashTable table, void* key){
    int index = table->hash(key, table->size);
    int pos = get_list_position(table->table[index], key);
    Item item = list_get(table->table[index], pos);
    if(item != NULL){
        return item->value;
    }
    return NULL;
}

// Returns the number of elements in the hash table.
int hash_table_size(HashTable table){
    return table->num_elements;
}

// Updates the value associated with the key.
void* hash_table_update(HashTable table, void* key, void* value){
    int index = table->hash(key, table->size);
    int pos = get_list_position(table->table[index], key);
    Item item = list_get(table->table[index], pos);
    if(item == NULL){
        hash_table_insert(table, key, value);
        return NULL;
    }
    void* old_value = item->value;
    item->value = value;
    return old_value;
}

// Returns all the keys of the hash table.
List hash_table_keys(HashTable table){
    if(hash_table_is_empty(table)){
        return NULL;
    }
    List keys_list = list_create();
    for(int i = 0; i < table->size; i++){
        list_iterator_start(table->table[i]);
        while(list_iterator_has_next(table->table[i])){
            Item item = list_iterator_get_next(table->table[i]);
            list_insert_last(keys_list, item->key);
        }
    }
    return keys_list;
}

// Returns all the values of the hash table.
List hash_table_values(HashTable table){
    return NULL;
}

// Returns the entries of the hash table.
List hash_table_entries(HashTable table){
    return NULL;
}

void hash_table_rehash(HashTable table, int new_size){
    return NULL;
}