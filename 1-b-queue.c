#include <stdio.h>
#define MAX 5 // Maximum size of the queue

int queue[MAX];
int front = 0;
int rear = -1;

// Enqueue operation
void enqueue(int value) {
    if (rear == MAX - 1) {
        printf("Queue overflow\n"); // Queue is full
        return;
    }
    rear++;
    queue[rear] = value;
    printf("%d enqueued to queue\n", value);
}

// Dequeue operation
int dequeue() {
    if (front > rear) {
        printf("Queue underflow\n"); // Queue is empty
        return -1; // Error code
    }
    int value = queue[front];
    front++;
    return value;
}

// Peek operation to get the front element
int peek() {
    if (front > rear) {
        printf("Queue is empty\n");
        return -1; // Error code
    }
    return queue[front];
}

// Display operation to show the queue elements
void display() {
    if (front > rear) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = front; i <= rear; i++) {
        printf("%d ", queue[i]);
    }
    printf("\n");
}

int main() {
    int choice, value;
    
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
                value = dequeue();
                if (value != -1) {
                    printf("Dequeued item: %d\n", value);
                }
                break;
            case 3:
                value = peek();
                if (value != -1) {
                    printf("Front item: %d\n", value);
                }
                break;
            case 4:
                display();
                break;
            case 5:
                return 0; // Exit the program
            default:
                printf("Invalid choice\n");
        }
    }
}
