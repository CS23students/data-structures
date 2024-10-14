#include <stdio.h>

// Function to perform binary search
int binarySearch(int arr[], int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Check if the target is present at mid
        if (arr[mid] == target) {
            return mid;
        }

        // If the target is greater, ignore the left half
        if (arr[mid] < target) {
            low = mid + 1;
        }
        // If the target is smaller, ignore the right half
        else {
            high = mid - 1;
        }
    }
    return -1;  // Return -1 if the element is not found
}

int main() {
    int n, target;

    // Input array size
    printf("Enter the number of elements in the sorted array: ");
    scanf("%d", &n);

    int arr[n];

    // Input elements (sorted)
    printf("Enter %d sorted elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Input target element to search
    printf("Enter the target element to search: ");
    scanf("%d", &target);

    // Perform binary search
    int result = binarySearch(arr, 0, n - 1, target);

    if (result == -1) {
        printf("Element not found in the array.\n");
    } else {
        printf("Element found at index %d.\n", result);
    }

    return 0;
}
