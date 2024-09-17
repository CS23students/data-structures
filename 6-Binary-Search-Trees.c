#include <stdio.h>
#include <stdlib.h>

// Define structure for a node in the binary search tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a new node in the BST
struct Node* insert(struct Node* root, int data) {
    // If the tree is empty, return a new node
    if (root == NULL) {
        return createNode(data);
    }
    
    // Otherwise, recur down the tree
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    
    // Return the root node (unchanged pointer)
    return root;
}

// Function to perform an inorder traversal of the tree (Left, Root, Right)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Function to search for a value in the BST
struct Node* search(struct Node* root, int key) {
    // Base case: root is null or key is present at root
    if (root == NULL || root->data == key) {
        return root;
    }
    
    // Key is greater than root's key
    if (key > root->data) {
        return search(root->right, key);
    }
    
    // Key is smaller than root's key
    return search(root->left, key);
}

// Main function to demonstrate the BST operations
int main() {
    struct Node* root = NULL;
    int choice, value, searchValue;
    
    while (1) {
        printf("\n1. Insert\n");
        printf("2. Inorder Traversal\n");
        printf("3. Search\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
                
            case 2:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;
                
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &searchValue);
                struct Node* result = search(root, searchValue);
                if (result != NULL) {
                    printf("Value %d found in the tree.\n", searchValue);
                } else {
                    printf("Value %d not found in the tree.\n", searchValue);
                }
                break;
                
            case 4:
                exit(0);
                
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    
    return 0;
}
