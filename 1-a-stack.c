// stack

#include <stdio.h>

#define MAX 100 // Maximum size of the stack

int stack[MAX]; // Array to hold stack elements
int top = -1;   // Index of the top element

// Push an item onto the stack
void push(int value) {
    if (top < MAX - 1) {
        stack[++top] = value;
    } else {
        printf("Stack overflow\n");
    }
}

// Pop an item from the stack
int pop() {
    if (top >= 0) {
        return stack[top--];
    } else {
        printf("Stack underflow\n");
        return -1; // Error code
    }
}

// Peek at the top item of the stack
int peek() {
    if (top >= 0) {
        return stack[top];
    } else {
        printf("Stack is empty\n");
        return -1; // Error code
    }
}

int main() {
    int value;
    int choice;
    
    while (1) {
        printf("1. Push\n2. Pop\n3. Peek\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(value);
                break;
            case 2:
                printf("Popped item: %d\n", pop());
                break;
            case 3:
                printf("Top item: %d\n", peek());
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
}
