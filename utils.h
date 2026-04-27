#ifndef UTILS_H
#define UTILS_H

void copy_array(int dest[], const int src[], int n);
int is_sorted(const int arr[], int n);

double get_time_ms();

void write_csv_header(const char *filename);
void append_csv_result(
    const char *filename,
    const char *algorithm,
    const char *input_case,
    int n,
    int trial,
    double time_ms,
    int sorted_ok,
    int repetitions
);

#endif
