#include <stdbool.h>
#include <stdio.h>

#include "sort.h"

void swap(comparable *collection, const int a, const int b) {
    comparable tmp = collection[a];
    collection[a] = collection[b];
    collection[b] = tmp;
}

int partition(comparable collection[], const int low, const int high, int (*compare)(comparable, comparable)) {
    int pivot_idx = (low + high) / 2;
    comparable pivot = collection[pivot_idx];

    int l = low - 1;
    int h = high + 1;
    while (true) {
        while (compare(collection[++l], pivot) < 0)
            ;
        while (compare(collection[--h], pivot) > 0)
            ;
        if (l >= h) {
            break;
        }
        swap(collection, l, h);
    }
    return h;
}

void quicksort(comparable collection[], const int low, const int high, int (*compare)(comparable, comparable)) {
    if (low < high) {
        int pivot_idx = partition(collection, low, high, compare);
        quicksort(collection, low, pivot_idx, compare);
        quicksort(collection, pivot_idx + 1, high, compare);
    }
}

void sort(comparable collection[], const int size, int (*compare)(comparable, comparable)) {
    quicksort(collection, 0, size - 1, compare);
}