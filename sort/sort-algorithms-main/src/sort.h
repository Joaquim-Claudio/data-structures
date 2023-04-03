#ifndef SORT_H
#define SORT_H

typedef void* comparable;

void sort(comparable collection[], const int size, int (*compare)(comparable, comparable));

#endif
