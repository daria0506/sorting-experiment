#ifndef GENERATORS_H
#define GENERATORS_H

void generate_random_array(int arr[], int n, int min_val, int max_val);
void generate_sorted_array(int arr[], int n);
void generate_reverse_sorted_array(int arr[], int n);
void generate_almost_sorted_array(int arr[], int n, double swap_fraction);
void generate_few_distinct_array(int arr[], int n, int distinct_count);

#endif
