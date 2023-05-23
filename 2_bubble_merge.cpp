#include <iostream>
#include <omp.h>

using namespace std;

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void parallelBubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        #pragma omp parallel for
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int left[n1], right[n2];

    for (int i = 0; i < n1; i++) {
        left[i] = arr[low + i];
    }
    for (int j = 0; j < n2; j++) {
        right[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergeSort(arr, low, mid);
            }
            #pragma omp section
            {
                mergeSort(arr, mid + 1, high);
            }
        }

        merge(arr, low, mid, high);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = {5, 3, 8, 1, 4, 2, 7, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original Array: ";
    printArray(arr, n);

    // Sequential Bubble Sort
    bubbleSort(arr, n);
    cout << "Sequential Bubble Sort: ";
    printArray(arr, n);

    // Reset the array
    int resetArr[] = {5, 3, 8, 1, 4, 2, 7, 6};

    // Parallel Bubble Sort
    parallelBubbleSort(resetArr, n);
    cout << "Parallel Bubble Sort: ";
    printArray(resetArr, n);

    // Reset the array
    int resetArr2[] = {5, 3, 8, 1, 4, 2, 7, 6};

    // Sequential Merge Sort
    mergeSort(resetArr2, 0, n - 1);
    cout << "Sequential Merge Sort: ";
    printArray(resetArr2, n);

    // Reset the array
    int resetArr3[] = {5, 3, 8, 1, 4, 2, 7, 6};

    // Parallel Merge Sort
    mergeSort(resetArr3, 0, n - 1);
    cout << "Parallel Merge Sort: ";
    printArray(resetArr3, n);

    return 0;
}
