#include <stdio.h>
#include <stdlib.h>

// Define a structure for a node in the singly linked list
struct Node {
    int data;          // Data part of the node
    struct Node* next; // Pointer to the next node
};

// Head of the linked list
struct Node* head = NULL;

// Function to insert a node at the beginning
void insertAtBeginning(int value) {
    // Allocate memory for a new node
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = value;      // Assign data to the node
    newNode->next = head;       // Point to the current head (old first node)
    head = newNode;             // Make the new node the head
    printf("%d inserted at the beginning\n", value);
}

// Function to insert a node at the end
void insertAtEnd(int value) {
    // Allocate memory for a new node
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    // If the list is empty, make the new node the head
    if (head == NULL) {
        head = newNode;
    } else {
        struct Node* temp = head;
        // Traverse to the last node
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode; // Link the last node to the new node
    }
    printf("%d inserted at the end\n", value);
}

// Function to delete a node by its value
void deleteByValue(int value) {
    struct Node* temp = head;
    struct Node* prev = NULL;

    // If the head node itself holds the value to be deleted
    if (temp != NULL && temp->data == value) {
        head = temp->next; // Change head
        free(temp);        // Free memory
        printf("%d deleted from the list\n", value);
        return;
    }

    // Search for the value to be deleted, keeping track of the previous node
    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    // If the value was not present in the list
    if (temp == NULL) {
        printf("%d not found in the list\n", value);
        return;
    }

    // Unlink the node from the linked list
    prev->next = temp->next;
    free(temp); // Free memory
    printf("%d deleted from the list\n", value);
}

// Function to display the entire linked list
void displayList() {
    struct Node* temp = head;

    // If the list is empty
    if (temp == NULL) {
        printf("List is empty\n");
        return;
    }

    printf("Linked List: ");
    // Traverse the linked list
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n"); // End of list
}

int main() {
    int choice, value;

    while (1) {
        printf("\n1. Insert at Beginning\n2. Insert at End\n3. Delete by Value\n4. Display List\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert at beginning: ");
                scanf("%d", &value);
                insertAtBeginning(value);
                break;
            case 2:
                printf("Enter value to insert at end: ");
                scanf("%d", &value);
                insertAtEnd(value);
                break;
            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                deleteByValue(value);
                break;
            case 4:
                displayList();
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
}
