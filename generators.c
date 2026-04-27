#include <stdlib.h>
#include "generators.h"

static int random_in_range(int min_val, int max_val) {
    return min_val + rand() % (max_val - min_val + 1); //find how many possible values are in the interval we want and return a random number from it
}

void generate_random_array(int arr[], int n, int min_val, int max_val) {
    int i;
    for (i = 0; i < n; i++) {
        arr[i] = random_in_range(min_val, max_val);
    }
}

void generate_sorted_array(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        arr[i] = i;
    }
}

void generate_reverse_sorted_array(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

void generate_almost_sorted_array(int arr[], int n, double swap_fraction) {
    int i;
    generate_sorted_array(arr, n);

    int swaps = (int)(n * swap_fraction);
    for (i = 0; i < swaps; i++) {
        int a = rand() % n;
        int b = rand() % n;

        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }
}

void generate_few_distinct_array(int arr[], int n, int distinct_count) {
    int i;

    if (distinct_count <= 0) {
        distinct_count = 1;
    }

    for (i = 0; i < n; i++) {
        arr[i] = rand() % distinct_count;
    }
}
