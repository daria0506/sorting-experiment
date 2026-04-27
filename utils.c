#include <stdio.h>
#include <windows.h>
#include "utils.h"

void copy_array(int dest[], const int src[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int is_sorted(const int arr[], int n) {
    int i;
    for (i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) {
            return 0;
        }
    }
    return 1;
}

double get_time_ms() {
    static LARGE_INTEGER frequency;
    static int initialized = 0;
    LARGE_INTEGER counter;

    if (!initialized) {
        QueryPerformanceFrequency(&frequency);
        initialized = 1;
    }

    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart * 1000.0 / (double)frequency.QuadPart;
}

void write_csv_header(const char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        return;
    }

    fprintf(f, "algorithm,input_case,n,trial,time_ms,sorted_ok,repetitions\n");
    fclose(f);
}

void append_csv_result(
    const char *filename,
    const char *algorithm,
    const char *input_case,
    int n,
    int trial,
    double time_ms,
    int sorted_ok,
    int repetitions
) {
    FILE *f = fopen(filename, "a");
    if (f == NULL) {
        return;
    }

    fprintf(f, "%s,%s,%d,%d,%.9f,%d,%d\n",
            algorithm, input_case, n, trial, time_ms, sorted_ok, repetitions);

    fclose(f);
}
