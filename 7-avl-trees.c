// method 1
#include <stdio.h>
#include <stdlib.h>

// Node structure for AVL Tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};

// Function to get the height of a node
int height(struct Node* node) {
    return (node == NULL) ? 0 : node->height;
}

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // New node has height 1
    return node;
}

// Function to get the balance factor of a node
int getBalance(struct Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Utility function to perform right rotation
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    printf("Performed Right Rotation\n");
    return x; // New root
}

// Utility function to perform left rotation
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    printf("Performed Left Rotation\n");
    return y; // New root
}

// Function to insert a node in the AVL tree
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        printf("Inserted %d.\n", data);
        return createNode(data);
    }

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    else {
        printf("Duplicate values are not allowed.\n");
        return root;
    }

    // Update height
    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));

    // Get balance factor
    int balance = getBalance(root);

    // Perform rotations if unbalanced
    if (balance > 1 && data < root->left->data)
        return rightRotate(root); // Left Left Case
    if (balance < -1 && data > root->right->data)
        return leftRotate(root); // Right Right Case
    if (balance > 1 && data > root->left->data) { // Left Right Case
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && data < root->right->data) { // Right Left Case
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to find the node with minimum value
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node from the AVL tree
struct Node* deleteNode(struct Node* root, int data) {
    if (root == NULL) {
        printf("Value %d not found in the tree.\n", data);
        return root;
    }

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
            printf("Deleted %d.\n", data);
        } else {
            struct Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    // Update height
    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));

    // Get balance factor
    int balance = getBalance(root);

    // Perform rotations if unbalanced
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root); // Left Left Case
    if (balance > 1 && getBalance(root->left) < 0) { // Left Right Case
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root); // Right Right Case
    if (balance < -1 && getBalance(root->right) > 0) { // Right Left Case
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to search for an element in the AVL tree
void search(struct Node* root, int key) {
    if (root == NULL) {
        printf("Element %d not found.\n", key);
        return;
    }
    if (key == root->data) {
        printf("Element %d found.\n", key);
    } else if (key < root->data) {
        search(root->left, key);
    } else {
        search(root->right, key);
    }
}

// Main function
int main() {
    struct Node* root = NULL;
    int choice, value;
    
    printf("\n1. Insert Element\n");
    printf("2. Delete Element\n");
    printf("3. Search Element\n");
    printf("4. Left Rotate\n");
    printf("5. Right Rotate\n");
    printf("6. Exit\n");
    
    while (1) {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Enter the value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 3:
                printf("Enter the value to search: ");
                scanf("%d", &value);
                search(root, value);
                break;
            case 4:
                root = leftRotate(root);
                break;
            case 5:
                root = rightRotate(root);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}


// OUTPUT:
// 1. Insert Element
// 2. Delete Element
// 3. Search Element
// 4. Left Rotate
// 5. Right Rotate
// 6. Exit
// Enter your choice: 1
// Enter the value to insert: 12
// Inserted 12.
// Enter your choice: 1
// Enter the value to insert: 23
// Inserted 23.
// Enter your choice: 1
// Enter the value to insert: 34
// Inserted 34.
// Performed Left Rotation
// Enter your choice: 3
// Enter the value to search: 12
// Element 12 found.
// Enter your choice: 4
// Performed Left Rotation
// Enter your choice: 5
// Performed Right Rotation
// Enter your choice: 3
// Enter the value to search: 23
// Element 23 found.
// Enter your choice: 5
// Exiting...


//-------------------------------------------------------------------------------------------------------//


// another method (this also the same like first method)
#include <stdio.h>
#include <stdlib.h>

// Structure of the tree node
struct node {
    int data;
    struct node* left;
    struct node* right;
    int ht;
};

// Global initialization of root node
struct node* root = NULL;

// Function prototyping
struct node* create(int);
struct node* insert(struct node*, int);
int delete(struct node**, int);
struct node* search(struct node*, int);
struct node* rotate_left(struct node*);
struct node* rotate_right(struct node*);
int balance_factor(struct node*);
int height(struct node*);

int main() {
    int ch, data;
    struct node* result = NULL;

    printf("\n\n------- AVL TREE --------\n");
    printf("\n1. Create Node");
    printf("\n2. Insert");
    printf("\n3. Delete");
    printf("\n4. Search");
    printf("\n5. Right Rotation");
    printf("\n6. Left Rotation");
    printf("\n7. EXIT");

    do {
        printf("\n\nEnter Your Choice: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1:
                printf("\nEnter data: ");
                scanf("%d", &data);
                root = create(data);
                if (root != NULL) {
                    printf("Node with data %d created.\n", data);
                }
                break;

            case 2:
                printf("\nEnter data: ");
                scanf("%d", &data);
                root = insert(root, data);
                printf("Inserted %d.\n", data);
                break;

            case 3:
                printf("\nEnter data: ");
                scanf("%d", &data);
                if (delete(&root, data)) {
                    printf("Deleted %d.\n", data);
                } else {
                    printf("Node %d not found.\n", data);
                }
                break;

            case 4:
                printf("\nEnter data: ");
                scanf("%d", &data);
                result = search(root, data);
                if (result) {
                    printf("\nNode %d found!\n", data);
                } else {
                    printf("\nNode %d not found.\n", data);
                }
                break;

            case 5:
                root = rotate_right(root);
                printf("Right rotation performed.\n");
                break;

            case 6:
                root = rotate_left(root);
                printf("Left rotation performed.\n");
                break;

            case 7:
                printf("\n\tProgram Terminated\n");
                return 0;

            default:
                printf("\n\tInvalid Choice\n");
        }
    } while(ch != 7);

    return 0;
}

// Creates a new tree node
struct node* create(int data) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("\nMemory can't be allocated\n");
        return NULL;
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->ht = 1; // Initialize height
    return new_node;
}

// Rotates to the left
struct node* rotate_left(struct node* root) {
    struct node* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;

    // Update heights
    root->ht = height(root);
    right_child->ht = height(right_child);

    return right_child;
}

// Rotates to the right
struct node* rotate_right(struct node* root) {
    struct node* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;

    // Update heights
    root->ht = height(root);
    left_child->ht = height(left_child);

    return left_child;
}

// Calculates the balance factor of a node
int balance_factor(struct node* root) {
    int lh = (root->left ? root->left->ht : 0);
    int rh = (root->right ? root->right->ht : 0);
    return lh - rh;
}

// Calculates the height of the node
int height(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    return root->ht;
}

// Inserts a new node in the AVL tree
struct node* insert(struct node* root, int data) {
    if (root == NULL) {
        return create(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    } else {
        // Duplicate data is not allowed
        return root;
    }

    // Update height
    root->ht = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));

    // Balance the tree
    int balance = balance_factor(root);

    // Left Left Case
    if (balance > 1 && data < root->left->data) {
        return rotate_right(root);
    }

    // Right Right Case
    if (balance < -1 && data > root->right->data) {
        return rotate_left(root);
    }

    // Left Right Case
    if (balance > 1 && data > root->left->data) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    // Right Left Case
    if (balance < -1 && data < root->right->data) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

// Deletes a node from the AVL tree
int delete(struct node** root, int x) {
    if (*root == NULL) {
        return 0; // Node not found
    }

    if (x < (*root)->data) {
        if (delete(&((*root)->left), x)) {
            if (balance_factor(*root) == -2) {
                if (balance_factor((*root)->right) <= 0) {
                    *root = rotate_left(*root);
                } else {
                    (*root)->right = rotate_right((*root)->right);
                    *root = rotate_left(*root);
                }
            }
            return 1; // Node found and deleted
        }
    } else if (x > (*root)->data) {
        if (delete(&((*root)->right), x)) {
            if (balance_factor(*root) == 2) {
                if (balance_factor((*root)->left) >= 0) {
                    *root = rotate_right(*root);
                } else {
                    (*root)->left = rotate_left((*root)->left);
                    *root = rotate_right(*root);
                }
            }
            return 1; // Node found and deleted
        }
    } else {
        // Node to be deleted is found
        struct node* temp;
        if ((*root)->right != NULL) {
            temp = (*root)->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            (*root)->data = temp->data;
            delete(&((*root)->right), temp->data);
        } else {
            struct node* leftChild = (*root)->left;
            free(*root);
            *root = leftChild;
        }
    }

    (*root)->ht = height(*root);
    return 1; // Node found and deleted
}

// Search a node in the AVL tree
struct node* search(struct node* root, int key) {
    if (root == NULL) {
        return NULL; // Node not found
    }

    if (root->data == key) {
        return root; // Node found
    }

    if (key < root->data) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}






// -------------------------------------------------//


// another method
#include <stdio.h>
#include <stdlib.h>

// Node structure for AVL Tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};

// Function to get the height of a node
int height(struct Node* node) {
    return (node == NULL) ? 0 : node->height;
}

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // Initially, height of a new node is 1
    return node;
}

// Function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Right rotate the subtree rooted at y
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    printf("Performing Right Rotation:\n");
    printf("Root before rotation: %d\n", y->data);
    printf("New root after rotation: %d\n", x->data);

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; // Return the new root
}

// Left rotate the subtree rooted at x
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    printf("Performing Left Rotation:\n");
    printf("Root before rotation: %d\n", x->data);
    printf("New root after rotation: %d\n", y->data);

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // Return the new root
}

// Insert a node in AVL tree and return the new root
struct Node* insert(struct Node* node, int data) {
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node; // Equal data are not allowed

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = height(node->left) - height(node->right);

    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Search for a node
struct Node* search(struct Node* root, int data) {
    if (root == NULL || root->data == data)
        return root;

    if (data < root->data)
        return search(root->left, data);

    return search(root->right, data);
}

// AVL Tree Driver
int main() {
    struct Node* root = NULL;
    int choice, data;

    while (1) {
        printf("\nAVL Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Right Rotate\n");
        printf("5. Left Rotate\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                printf("Inserted %d.\n", data);
                break;
            case 2:
                printf("Deletion is not yet implemented.\n");
                break;
            case 3:
                printf("Enter the value to search: ");
                scanf("%d", &data);
                struct Node* result = search(root, data);
                if (result)
                    printf("Value %d found in the tree.\n", data);
                else
                    printf("Value %d not found in the tree.\n", data);
                break;
            case 4:
                printf("Enter the value to perform Right Rotation: ");
                scanf("%d", &data);
                struct Node* nodeForRightRotation = search(root, data);
                if (nodeForRightRotation) {
                    root = rightRotate(nodeForRightRotation);
                } else {
                    printf("Value %d not found for rotation.\n", data);
                }
                break;
            case 5:
                printf("Enter the value to perform Left Rotation: ");
                scanf("%d", &data);
                struct Node* nodeForLeftRotation = search(root, data);
                if (nodeForLeftRotation) {
                    root = leftRotate(nodeForLeftRotation);
                } else {
                    printf("Value %d not found for rotation.\n", data);
                }
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}


