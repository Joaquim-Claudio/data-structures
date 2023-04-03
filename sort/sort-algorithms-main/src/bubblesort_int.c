#include "sort_int.h"

void sort(int collection[], const int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size - 1; j++) {
            if(collection[j] > collection[j + 1]) {
                int aux = collection[j];
                collection[j] = collection[j + 1];
                collection[j + 1] = aux;
            }
        }
    }
}