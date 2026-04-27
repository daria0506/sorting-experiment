#include <stdlib.h>
#include "sorts.h"

/* =========================
   BUBBLE SORT
   ========================= */
void bubble_sort(int arr[], int n) {
    int i, j, temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/* =========================
   INSERTION SORT
   ========================= */
void insertion_sort(int arr[], int n) {
    int i, j, key;

    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

/* =========================
   SELECTION SORT
   ========================= */
void selection_sort(int arr[], int n) {
    int i, j, min_index, temp;

    for (i = 0; i < n - 1; i++) {
        min_index = i;

        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
}

/* =========================
   PANCAKE SORT
   ========================= */

static void flip(int arr[], int i) {
    int start = 0;
    int temp;

    while (start < i) {
        temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
        start++;
        i--;
    }
}

static int find_max_index(int arr[], int n) {
    int max_index = 0;
    int i;

    for (i = 1; i < n; i++) {
        if (arr[i] > arr[max_index]) {
            max_index = i;
        }
    }

    return max_index;
}

void pancake_sort(int arr[], int n) {
    int curr_size;
    int max_index;

    for (curr_size = n; curr_size > 1; curr_size--) {
        max_index = find_max_index(arr, curr_size);

        if (max_index != curr_size - 1) {
            if (max_index != 0) {
                flip(arr, max_index);
            }
            flip(arr, curr_size - 1);
        }
    }
}

/* =========================
   HEAP SORT
   ========================= */

static void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int temp;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heap_sort(int arr[], int n) {
    int i, temp;

    for (i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (i = n - 1; i > 0; i--) {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

/* =========================
   MERGE SORT
   ========================= */

static void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    if (L == NULL || R == NULL) {
        free(L);
        free(R);
        return;
    }

    int i, j, k;

    for (i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }

    for (j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

/* =========================
   QUICK SORT
   ========================= */

static void swap_int(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void quick_sort_internal(int arr[], int low, int high) {
    while (low < high) {
        int mid = low + (high - low) / 2;
        int pivot = arr[mid];

        int lt = low;
        int i = low;
        int gt = high;

        /* 3-way partition:
           arr[low..lt-1] < pivot
           arr[lt..gt] == pivot
           arr[gt+1..high] > pivot
        */
        while (i <= gt) {
            if (arr[i] < pivot) {
                swap_int(&arr[lt], &arr[i]);
                lt++;
                i++;
            } else if (arr[i] > pivot) {
                swap_int(&arr[i], &arr[gt]);
                gt--;
            } else {
                i++;
            }
        }

        /* Recurse on smaller side first to keep stack shallow */
        if ((lt - low) < (high - gt)) {
            if (low < lt - 1) {
                quick_sort_internal(arr, low, lt - 1);
            }
            low = gt + 1;
        } else {
            if (gt + 1 < high) {
                quick_sort_internal(arr, gt + 1, high);
            }
            high = lt - 1;
        }
    }
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        quick_sort_internal(arr, low, high);
    }
}

/* =========================
   SHELL SORT
   ========================= */

void shell_sort(int arr[], int n) {
    int gap, i, j, temp;

    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            temp = arr[i];

            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }

            arr[j] = temp;
        }
    }
}
