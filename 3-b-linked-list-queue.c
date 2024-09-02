#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to check if the queue is empty
int isEmpty(struct Node* front) {
    return front == NULL;
}

// Function to enqueue (add) an element to the queue
void enqueue(struct Node** front, struct Node** rear, int data) {
    struct Node* newNode = createNode(data);
    if (*rear == NULL) {
        *front = *rear = newNode;
    } else {
        (*rear)->next = newNode;
        *rear = newNode;
    }
    printf("Enqueued %d into the queue.\n", data);
}

// Function to dequeue (remove) an element from the queue
int dequeue(struct Node** front, struct Node** rear) {
    if (isEmpty(*front)) {
        printf("Queue underflow! Unable to dequeue.\n");
        return -1;
    }
    struct Node* temp = *front;
    int dequeuedData = temp->data;
    *front = (*front)->next;

    if (*front == NULL) {
        *rear = NULL;
    }

    free(temp);
    printf("Dequeued %d from the queue.\n", dequeuedData);
    return dequeuedData;
}

// Function to peek at the front element of the queue
int peek(struct Node* front) {
    if (isEmpty(front)) {
        printf("Queue is empty! Cannot peek.\n");
        return -1;
    }
    return front->data;
}

// Function to display the queue
void displayQueue(struct Node* front) {
    if (isEmpty(front)) {
        printf("Queue is empty!\n");
        return;
    }
    struct Node* temp = front;
    printf("Queue elements: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* front = NULL;  // Initialize front of the queue
    struct Node* rear = NULL;   // Initialize rear of the queue
    int choice, value;

    while (1) {
        printf("\n1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Display Queue\n");
        printf("5. Check if Queue is Empty\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(&front, &rear, value);
                break;

            case 2:
                dequeue(&front, &rear);
                break;

            case 3:
                value = peek(front);
                if (value != -1) {
                    printf("Front element is: %d\n", value);
                }
                break;

            case 4:
                displayQueue(front);
                break;

            case 5:
                if (isEmpty(front)) {
                    printf("Queue is empty.\n");
                } else {
                    printf("Queue is not empty.\n");
                }
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
