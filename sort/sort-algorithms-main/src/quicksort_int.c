#include <stdbool.h>
#include <stdio.h>

#include "sort_int.h"

void swap(int *collection, const int a, const int b) {
    int tmp = collection[a];
    collection[a] = collection[b];
    collection[b] = tmp;
}

int partition(int collection[], const int low, const int high) {
    int pivot_idx = (low + high) / 2;
    int pivot = collection[pivot_idx];

    int l = low - 1;
    int h = high + 1;
    while (true) {
        while (collection[++l] < pivot)
            ;
        while (collection[--h] > pivot)
            ;
        if (l >= h) {
            break;
        }
        swap(collection, l, h);
    }
    return h;
}

void quicksort(int collection[], const int low, const int high) {
    if (low < high) {
        int pivot_idx = partition(collection, low, high);
        quicksort(collection, low, pivot_idx);
        quicksort(collection, pivot_idx + 1, high);
    }
}

void sort(int collection[], const int size) {
    quicksort(collection, 0, size - 1);
}