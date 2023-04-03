#include <stdio.h>

#include "sort.h"

void sort(comparable collection[], const int size, int (*compare)(comparable, comparable)) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (compare(collection[j], collection[j + 1]) > 0) {
                comparable aux = collection[j];
                collection[j] = collection[j + 1];
                collection[j + 1] = aux;
            }
        }
    }
}
