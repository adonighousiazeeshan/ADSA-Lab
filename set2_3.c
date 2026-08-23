#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];
    return max;
}

void resetArray(int dest[], int src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// 1. Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 2. Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
}

// 3. Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIdx]) minIdx = j;
        swap(&arr[i], &arr[minIdx]);
    }
}

// 4. Shell Sort
void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i], j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

// 5. Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 6. Merge Sort
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// 7. Heap Sort
void heapify(int arr[], int n, int i) {
    int largest = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// 8. Radix Sort
void countSortForRadix(int arr[], int n, int exp) {
    int output[n], count[10] = {0};
    for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
}

void radixSort(int arr[], int n) {
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSortForRadix(arr, n, exp);
}

// 9. Counting Sort
void countingSort(int arr[], int n) {
    int max = getMax(arr, n);
    int count[max + 1];
    for (int i = 0; i <= max; i++) count[i] = 0;
    for (int i = 0; i < n; i++) count[arr[i]]++;
    int idx = 0;
    for (int i = 0; i <= max; i++) {
        while (count[i] > 0) {
            arr[idx++] = i;
            count[i]--;
        }
    }
}

// 10. Bucket Sort
struct Node {
    int data;
    struct Node* next;
};

void bucketSort(int arr[], int n) {
    struct Node* buckets[10] = {NULL};
    int max = getMax(arr, n);

    for (int i = 0; i < n; i++) {
        int bIdx = (arr[i] * 10) / (max + 1);
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = arr[i];
        newNode->next = NULL;

        if (!buckets[bIdx] || buckets[bIdx]->data >= arr[i]) {
            newNode->next = buckets[bIdx];
            buckets[bIdx] = newNode;
        } else {
            struct Node* temp = buckets[bIdx];
            while (temp->next && temp->next->data < arr[i])
                temp = temp->next;
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    int idx = 0;
    for (int i = 0; i < 10; i++) {
        struct Node* temp = buckets[i];
        while (temp) {
            arr[idx++] = temp->data;
            struct Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
}

// 11. Radix Exchange Sort
void radixExchangeSortRec(int arr[], int l, int r, int bit) {
    if (l >= r || bit < 0) return;
    int i = l, j = r;
    while (i <= j) {
        while (i <= r && !((arr[i] >> bit) & 1)) i++;
        while (j >= l && ((arr[j] >> bit) & 1)) j--;
        if (i < j) swap(&arr[i], &arr[j]);
    }
    radixExchangeSortRec(arr, l, j, bit - 1);
    radixExchangeSortRec(arr, i, r, bit - 1);
}

void radixExchangeSort(int arr[], int n) {
    radixExchangeSortRec(arr, 0, n - 1, 30);
}

// 12. Address Calculation Sort
void addressCalculationSort(int arr[], int n) {
    bucketSort(arr, n);
}

int main() {
    int original[] = {64, 34, 25, 12, 22, 11, 90, 5};
    int n = sizeof(original) / sizeof(original[0]);
    int arr[n];

    printf("Original array: ");
    printArray(original, n);
    printf("----------------------------------------\n");

    // 1. Insertion Sort
    resetArray(arr, original, n);
    insertionSort(arr, n);
    printf("1. Insertion Sort: ");
    printArray(arr, n);

    // 2. Bubble Sort
    resetArray(arr, original, n);
    bubbleSort(arr, n);
    printf("2. Bubble Sort:    ");
    printArray(arr, n);

    // 3. Selection Sort
    resetArray(arr, original, n);
    selectionSort(arr, n);
    printf("3. Selection Sort: ");
    printArray(arr, n);

    // 4. Shell Sort
    resetArray(arr, original, n);
    shellSort(arr, n);
    printf("4. Shell Sort:     ");
    printArray(arr, n);

    // 5. Quick Sort
    resetArray(arr, original, n);
    quickSort(arr, 0, n - 1);
    printf("5. Quick Sort:     ");
    printArray(arr, n);

    // 6. Merge Sort
    resetArray(arr, original, n);
    mergeSort(arr, 0, n - 1);
    printf("6. Merge Sort:     ");
    printArray(arr, n);

    // 7. Heap Sort
    resetArray(arr, original, n);
    heapSort(arr, n);
    printf("7. Heap Sort:      ");
    printArray(arr, n);

    // 8. Radix Sort
    resetArray(arr, original, n);
    radixSort(arr, n);
    printf("8. Radix Sort:     ");
    printArray(arr, n);

    // 9. Counting Sort
    resetArray(arr, original, n);
    countingSort(arr, n);
    printf("9. Counting Sort:  ");
    printArray(arr, n);

    // 10. Bucket Sort
    resetArray(arr, original, n);
    bucketSort(arr, n);
    printf("10. Bucket Sort:   ");
    printArray(arr, n);

    // 11. Radix Exchange Sort
    resetArray(arr, original, n);
    radixExchangeSort(arr, n);
    printf("11. Radix Ex. Sort:");
    printArray(arr, n);

    // 12. Address Calculation Sort
    resetArray(arr, original, n);
    addressCalculationSort(arr, n);
    printf("12. Address Calc:  ");
    printArray(arr, n);

    return 0;
}