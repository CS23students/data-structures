#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure for Priority Queue (Generic Heap)
struct PriorityQueue {
    int data[MAX];    // Array to hold heap elements
    int size;         // Current size of the heap
    int (*compare)(int, int);  // Comparison function pointer (Min or Max)
};

// Function to initialize the Priority Queue with a custom compare function
void initQueue(struct PriorityQueue* pq, int (*cmp)(int, int)) {
    pq->size = 0;
    pq->compare = cmp;  // Assign custom comparison function (Min/Max)
}

// Function to return the index of the parent node
int parent(int i) {
    return (i - 1) / 2;
}

// Function to return the index of the left child
int leftChild(int i) {
    return (2 * i + 1);
}

// Function to return the index of the right child
int rightChild(int i) {
    return (2 * i + 2);
}

// Function to swap two elements
void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Function to insert an element into the heap
void insert(struct PriorityQueue* pq, int value) {
    if (pq->size == MAX) {
        printf("Priority Queue is full!\n");
        return;
    }

    // Insert the new value at the end
    pq->data[pq->size] = value;
    int i = pq->size;
    pq->size++;

    // Adjust the heap property by bubbling up the new value based on the custom compare function
    while (i != 0 && pq->compare(pq->data[parent(i)], pq->data[i])) {
        swap(&pq->data[i], &pq->data[parent(i)]);
        i = parent(i);
    }

    printf("Inserted %d into the Priority Queue.\n", value);
}

// Function to heapify the subtree with root at index i
void heapify(struct PriorityQueue* pq, int i) {
    int best = i;  // For Min Heap, it will store the smallest; for Max Heap, the largest
    int left = leftChild(i);
    int right = rightChild(i);

    // Apply custom comparison to decide if the heap property is violated
    if (left < pq->size && pq->compare(pq->data[best], pq->data[left]))
        best = left;

    if (right < pq->size && pq->compare(pq->data[best], pq->data[right]))
        best = right;

    // If heap property is violated, fix it recursively
    if (best != i) {
        swap(&pq->data[i], &pq->data[best]);
        heapify(pq, best);
    }
}

// Function to extract the root element (min for Min Heap or max for Max Heap)
int extractRoot(struct PriorityQueue* pq) {
    if (pq->size <= 0) {
        printf("Priority Queue is empty!\n");
        return -1;
    }

    if (pq->size == 1) {
        pq->size--;
        return pq->data[0];
    }

    int root = pq->data[0];
    pq->data[0] = pq->data[pq->size - 1];
    pq->size--;
    heapify(pq, 0);

    return root;
}

// Function to get the root element without removing it
int getRoot(struct PriorityQueue* pq) {
    if (pq->size <= 0) {
        printf("Priority Queue is empty!\n");
        return -1;
    }
    return pq->data[0];
}

// Function to print the Priority Queue
void printQueue(struct PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Priority Queue is empty!\n");
        return;
    }

    printf("Priority Queue: ");
    for (int i = 0; i < pq->size; i++) {
        printf("%d ", pq->data[i]);
    }
    printf("\n");
}

// Comparison function for Min Heap
int minCompare(int a, int b) {
    return a > b;  // Return true if a is greater than b (Min Heap logic)
}

// Comparison function for Max Heap
int maxCompare(int a, int b) {
    return a < b;  // Return true if a is less than b (Max Heap logic)
}

// Main function to demonstrate usage
int main() {
    struct PriorityQueue pq;

    // Select whether to use Min Heap or Max Heap
    int heapType;
    printf("Select Heap Type (1 for Min Heap, 2 for Max Heap): ");
    scanf("%d", &heapType);

    if (heapType == 1) {
        // Initialize Min Heap
        initQueue(&pq, minCompare);
        printf("Min Heap initialized.\n");
    } else {
        // Initialize Max Heap
        initQueue(&pq, maxCompare);
        printf("Max Heap initialized.\n");
    }

    int choice, value;

    while (1) {
        printf("\nPriority Queue Operations:\n");
        printf("1. Insert\n");
        printf("2. Extract Root\n");
        printf("3. Get Root\n");
        printf("4. Print Queue\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(&pq, value);
                break;
            case 2:
                value = extractRoot(&pq);
                if (value != -1) {
                    printf("Extracted Root: %d\n", value);
                }
                break;
            case 3:
                value = getRoot(&pq);
                if (value != -1) {
                    printf("Root Element: %d\n", value);
                }
                break;
            case 4:
                printQueue(&pq);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
