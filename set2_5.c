#include <stdio.h>

// Merge two sorted parts:
// arr[left ... mid] and arr[mid+1 ... right]
void merge(int arr[], int temp[], int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    // Merge both parts into temp[]
    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k] = arr[i];
            i++;
        }
        else
        {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements from left part
    while (i <= mid)
    {
        temp[k] = arr[i];
        i++;
        k++;
    }

    // Copy remaining elements from right part
    while (j <= right)
    {
        temp[k] = arr[j];
        j++;
        k++;
    }

    // Copy merged result back to original array
    for (i = left; i <= right; i++)
    {
        arr[i] = temp[i];
    }
}


void mergeSort(int arr[], int n)
{
    int temp[n];

    int size;
    int left;

    // size = size of the subarrays we are merging
    // 1 -> 2 -> 4 -> 8 -> ...
    for (size = 1; size < n; size = size * 2)
    {
        // Pick two neighboring subarrays of current size
        for (left = 0; left < n - 1; left = left + 2 * size)
        {
            int mid = left + size - 1;
            int right = left + 2 * size - 1;

            // If right exceeds array size
            if (right >= n)
                right = n - 1;

            // If second part actually exists
            if (mid < right)
                merge(arr, temp, left, mid, right);
        }
    }
}


int main()
{
    int arr[] = {38, 27, 43, 3, 9, 82, 10};

    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Before sorting:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    mergeSort(arr, n);

    printf("\n\nAfter sorting:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}