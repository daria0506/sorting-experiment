#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sorts.h"
#include "generators.h"
#include "utils.h"

void run_single_test(const char *filename, const char *algorithm, const char *input_case, int original[], int n, int trial) {
    int *work = (int *)malloc(n * sizeof(int));
    if (work == NULL) {
        printf("Memory allocation failed for n = %d\n", n);
        return;
    }

    int repetitions;

    if (n <= 20) {
        repetitions = 20000;
    } else if (n <= 100) {
        repetitions = 10000;
    } else if (n <= 1000) {
        repetitions = 2000;
    } else if (n <= 5000) {
        repetitions = 200;
    } else if (n <= 10000) {
        repetitions = 50;
    } else if (n <= 100000) {
        repetitions = 5;
    } else if (n <= 1000000) {
        repetitions = 2;
    } else {
        repetitions = 1;
    }

    double start, end;
    int r;

    start = get_time_ms();

    for (r = 0; r < repetitions; r++) {
        copy_array(work, original, n);

        if (strcmp(algorithm, "bubble") == 0) {
            bubble_sort(work, n);
        } else if (strcmp(algorithm, "insertion") == 0) {
            insertion_sort(work, n);
        } else if (strcmp(algorithm, "selection") == 0) {
            selection_sort(work, n);
        } else if (strcmp(algorithm, "pancake") == 0) {
            pancake_sort(work, n);
        } else if (strcmp(algorithm, "heap") == 0) {
            heap_sort(work, n);
        } else if (strcmp(algorithm, "merge") == 0) {
            merge_sort(work, 0, n - 1);
        } else if (strcmp(algorithm, "quick") == 0) {
            quick_sort(work, 0, n - 1);
        } else if (strcmp(algorithm, "shell") == 0) {
            shell_sort(work, n);
        } else {
    printf("Unknown algorithm: %s\n", algorithm);
    free(work);
    return;
}
    }

    end = get_time_ms();

    double time_ms = (end - start) / repetitions;
    int sorted_ok = is_sorted(work, n);

    printf("Algorithm=%s | Case=%s | n=%d | trial=%d | avg_time=%.9f ms | sorted=%d | reps=%d\n",
           algorithm, input_case, n, trial, time_ms, sorted_ok, repetitions);

    append_csv_result(filename, algorithm, input_case, n, trial, time_ms, sorted_ok, repetitions);

    free(work);
}

void run_case_for_algorithm_list(const char *filename, const char *input_case, int n, int trial, const char *algorithms[], int num_algorithms) {
    int *original = (int *)malloc(n * sizeof(int));
    if (original == NULL) {
        printf("Memory allocation failed for original array, n = %d\n", n);
        return;
    }

    if (strcmp(input_case, "random") == 0) {
        generate_random_array(original, n, 0, 1000000);
    } else if (strcmp(input_case, "sorted") == 0) {
        generate_sorted_array(original, n);
    } else if (strcmp(input_case, "reverse") == 0) {
        generate_reverse_sorted_array(original, n);
    } else if (strcmp(input_case, "almost_sorted") == 0) {
        generate_almost_sorted_array(original, n, 0.02);
    } else if (strcmp(input_case, "few_distinct") == 0) {
        generate_few_distinct_array(original, n, 10);
    } else {
        printf("Unknown input case: %s\n", input_case);
        free(original);
        return;
    }

    int i;
    for (i = 0; i < num_algorithms; i++) {
        run_single_test(filename, algorithms[i], input_case, original, n, trial);
    }

    free(original);
}

void run_simple_batch() {
    const char *algorithms[] = {"bubble", "insertion", "selection", "pancake"};
    const char *cases[] = {"random", "sorted", "reverse", "almost_sorted", "few_distinct"};
    int sizes[] = {20, 50, 100, 1000, 5000};
    int num_algorithms = 4;
    int num_cases = sizeof(cases) / sizeof(cases[0]);
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    int trial, i, j;

    write_csv_header("results_simple.csv");

    for (trial = 1; trial <= 1; trial++) {
        for (i = 0; i < num_cases; i++) {
            for (j = 0; j < num_sizes; j++) {
                printf("\n[Simple batch] case=%s, n=%d, trial=%d\n", cases[i], sizes[j], trial);
                run_case_for_algorithm_list("results_simple.csv", cases[i], sizes[j], trial, algorithms, num_algorithms);
            }
        }
    }

    printf("\nSimple sorts batch finished. Results written to results_simple.csv\n");
}

void run_efficient_batch() {
    const char *algorithms[] = {"heap", "merge", "quick", "shell"};
    const char *cases[] = {"random", "sorted", "reverse", "almost_sorted", "few_distinct"};
    int sizes[] = {20, 50, 100, 1000, 5000, 10000, 50000, 100000, 1000000};
    int num_algorithms = 4;
    int num_cases = sizeof(cases) / sizeof(cases[0]);
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    int trial, i, j;

    write_csv_header("results_efficient.csv");

    for (trial = 1; trial <= 3; trial++) {
        for (i = 0; i < num_cases; i++) {
            for (j = 0; j < num_sizes; j++) {
                printf("\n[Efficient batch] case=%s, n=%d, trial=%d\n", cases[i], sizes[j], trial);
                run_case_for_algorithm_list("results_efficient.csv", cases[i], sizes[j], trial, algorithms, num_algorithms);
            }
        }
    }

    printf("\nEfficient sorts batch finished. Results written to results_efficient.csv\n");
}

void run_custom_single_test() {
    int n;
    int case_choice;
    const char *input_case;

    printf("\nEnter array size: ");
    scanf("%d", &n);

    printf("\nChoose input case:\n");
    printf("1. random\n");
    printf("2. sorted\n");
    printf("3. reverse\n");
    printf("4. almost_sorted\n");
    printf("5. few_distinct\n");
    printf("Your choice: ");
    scanf("%d", &case_choice);

    switch (case_choice) {
        case 1: input_case = "random"; break;
        case 2: input_case = "sorted"; break;
        case 3: input_case = "reverse"; break;
        case 4: input_case = "almost_sorted"; break;
        case 5: input_case = "few_distinct"; break;
        default:
            printf("Invalid choice.\n");
            return;
    }

    if (n <= 5000) {
        const char *all_algorithms[] = {
            "bubble", "insertion", "selection", "pancake",
            "heap", "merge", "quick", "shell"
        };

        printf("\nRunning all 8 algorithms on the same generated input...\n\n");

        write_csv_header("results_custom_live.csv");
        run_case_for_algorithm_list("results_custom_live.csv", input_case, n, 1, all_algorithms, 8);
    } else {
        const char *fast_algorithms[] = {"heap", "merge", "quick", "shell"};

        printf("\nSize too large for slow algorithms. Running only efficient sorts.\n");
        write_csv_header("results_custom_live.csv");
        run_case_for_algorithm_list("results_custom_live.csv", input_case, n, 1, fast_algorithms, 4);
    }

    printf("\nCustom test finished. Results written to results_custom_live.csv\n");


}

void run_custom_batch() {
    int group_choice;
    int trials;

    printf("\nChoose algorithm group:\n");
    printf("1. Simple sorts (bubble, insertion, selection, pancake)\n");
    printf("2. Efficient sorts (heap, merge, quick, shell)\n");
    printf("Your choice: ");
    scanf("%d", &group_choice);

    printf("\nEnter number of trials: ");
    scanf("%d", &trials);

    if (trials <= 0) {
        printf("Invalid number of trials.\n");
        return;
    }

    if (group_choice == 1) {
        const char *algorithms[] = {"bubble", "insertion", "selection", "pancake"};
        const char *cases[] = {"random", "sorted", "reverse", "almost_sorted", "few_distinct"};
        int sizes[] = {10, 20, 50, 100, 1000, 5000};
        int num_algorithms = 4;
        int num_cases = sizeof(cases) / sizeof(cases[0]);
        int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

        int trial, i, j;

        write_csv_header("results_custom_batch_simple.csv");
        printf("\nRunning custom batch: SIMPLE SORTS\n\n");

        for (trial = 1; trial <= trials; trial++) {
            for (i = 0; i < num_cases; i++) {
                for (j = 0; j < num_sizes; j++) {
                    printf("[Custom batch - simple] case=%s, n=%d, trial=%d\n",
                           cases[i], sizes[j], trial);
                    run_case_for_algorithm_list("results_custom_batch_simple.csv", cases[i], sizes[j], trial, algorithms, num_algorithms);
                }
            }
        }

        printf("\nCustom simple batch finished. Results written to results_custom_batch_simple.csv\n");

    } else if (group_choice == 2) {
        const char *algorithms[] = {"heap", "merge", "quick", "shell"};
        const char *cases[] = {"random", "sorted", "reverse", "almost_sorted", "few_distinct"};
        int sizes[] = {20, 50, 100, 1000, 5000, 10000, 50000, 100000, 1000000};
        int num_algorithms = 4;
        int num_cases = sizeof(cases) / sizeof(cases[0]);
        int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

        int trial, i, j;

        write_csv_header("results_custom_batch_efficient.csv");
        printf("\nRunning custom batch: EFFICIENT SORTS\n\n");

        for (trial = 1; trial <= trials; trial++) {
            for (i = 0; i < num_cases; i++) {
                for (j = 0; j < num_sizes; j++) {
                    printf("[Custom batch - efficient] case=%s, n=%d, trial=%d\n",
                           cases[i], sizes[j], trial);
                    run_case_for_algorithm_list("results_custom_batch_efficient.csv", cases[i], sizes[j], trial, algorithms, num_algorithms);
                }
            }
        }

        printf("\nCustom efficient batch finished. Results written to results_custom_batch_efficient.csv\n");

    } else {
        printf("Invalid choice.\n");
    }
}


int main() {
    int choice;

    srand((unsigned int)time(NULL));

    do {
        printf("\n===== SORTING EXPERIMENT MENU =====\n");
        printf("1. Run simple sorts batch\n");
        printf("2. Run efficient sorts batch\n");
        printf("3. Run custom live comparison\n");
        printf("4. Run custom batch\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                run_simple_batch();
                break;
            case 2:
                run_efficient_batch();
                break;
            case 3:
                run_custom_single_test();
                break;
            case 4:
                run_custom_batch();
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
            } while (choice != 5);

    return 0;
}
