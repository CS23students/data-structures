#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the BST
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

// Function to insert a node in the BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);  // Create a new node if tree is empty
    }

    // Recursively insert the new data
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

// Function to search for a node in the BST
struct Node* search(struct Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;  // Return the found node or NULL if not found
    }

    if (data < root->data) {
        return search(root->left, data);  // Search in the left subtree
    }

    return search(root->right, data);  // Search in the right subtree
}

// Function to find the minimum value node in the BST
struct Node* findMin(struct Node* root) {
    struct Node* current = root;

    // Loop down to find the leftmost leaf
    while (current && current->left != NULL) {
        current = current->left;
    }

    return current;
}

// Function to delete a node from the BST
struct Node* deleteNode(struct Node* root, int data) {
    if (root == NULL) {
        return root;  // If the tree is empty
    }

    // Recursively find the node to be deleted
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        // Node found, handle the three cases
        if (root->left == NULL) {  // Node with only right child or no child
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {  // Node with only left child
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        struct Node* temp = findMin(root->right);

        // Replace data with the inorder successor's data
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

// Function to perform inorder traversal (Left, Root, Right)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Function to perform preorder traversal (Root, Left, Right)
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Function to perform postorder traversal (Left, Right, Root)
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Function to find the maximum value node in the BST
struct Node* findMax(struct Node* root) {
    struct Node* current = root;

    // Loop down to find the rightmost leaf
    while (current && current->right != NULL) {
        current = current->right;
    }

    return current;
}

// Main function to demonstrate BST operations
int main() {
    struct Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Inorder Traversal\n");
        printf("5. Preorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("7. Find Minimum\n");
        printf("8. Find Maximum\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;

            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                struct Node* searchResult = search(root, value);
                if (searchResult != NULL) {
                    printf("Node with value %d found in the tree.\n", searchResult->data);
                } else {
                    printf("Node with value %d not found in the tree.\n", value);
                }
                break;

            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                printf("Node with value %d deleted from the tree.\n", value);
                break;

            case 4:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;

            case 6:
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;

            case 7:
                struct Node* minNode = findMin(root);
                if (minNode != NULL) {
                    printf("Minimum value in the tree is: %d\n", minNode->data);
                } else {
                    printf("The tree is empty.\n");
                }
                break;

            case 8:
                struct Node* maxNode = findMax(root);
                if (maxNode != NULL) {
                    printf("Maximum value in the tree is: %d\n", maxNode->data);
                } else {
                    printf("The tree is empty.\n");
                }
                break;

            case 9:
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
