#include <stdio.h>

#define MAX 100 // Maximum size of the queue

int queue[MAX]; // Array to hold queue elements
int front = 0;  // Index of the front element
int rear = -1;  // Index of the rear element
int size = 0;   // Number of elements in the queue

// Enqueue an item
void enqueue(int value) {
    if (size < MAX) {
        rear = (rear + 1) % MAX;
        queue[rear] = value;
        size++;
    } else {
        printf("Queue overflow\n");
    }
}

// Dequeue an item
int dequeue() {
    if (size > 0) {
        int value = queue[front];
        front = (front + 1) % MAX;
        size--;
        return value;
    } else {
        printf("Queue underflow\n");
        return -1; // Error code
    }
}

// Peek at the front item
int peek() {
    if (size > 0) {
        return queue[front];
    } else {
        printf("Queue is empty\n");
        return -1; // Error code
    }
}

// Display all items in the queue
void display() {
    if (size == 0) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", queue[(front + i) % MAX]);
    }
    printf("\n");
}

int main() {
    int value;
    int choice;
    
    while (1) {
        printf("\n1. Enqueue\n2. Dequeue\n3. Peek\n4. Display Queue\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                printf("Dequeued item: %d\n", dequeue());
                break;
            case 3:
                printf("Front item: %d\n", peek());
                break;
            case 4:
                display();
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
}
