#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the BST
struct node {
    int data;
    struct node *left;
    struct node *right;
};

// Count total number of nodes
int totalNodes(struct node* tree) {
    if (tree == NULL) return 0;
    return 1 + totalNodes(tree->left) + totalNodes(tree->right);
}

// Count total number of external nodes
int totalExternalNodes(struct node* tree) {
    if (tree == NULL) return 0;
    if (tree->left == NULL && tree->right == NULL) return 1;
    return totalExternalNodes(tree->left) + totalExternalNodes(tree->right);
}

// Count total number of internal nodes
int totalInternalNodes(struct node* tree) {
    if (tree == NULL || (tree->left == NULL && tree->right == NULL)) return 0;
    return 1 + totalInternalNodes(tree->left) + totalInternalNodes(tree->right);
}

// Determine the height of the tree
int height(struct node* tree) {
    if (tree == NULL) return 0;
    int leftHeight = height(tree->left);
    int rightHeight = height(tree->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Find the mirror image of the tree
struct node* mirrorImage(struct node* tree) {
    if (tree == NULL) return NULL;
    struct node* temp = tree->left;
    tree->left = mirrorImage(tree->right);
    tree->right = mirrorImage(temp);
    return tree;
}

// Delete the tree
struct node* deleteTree(struct node* tree) {
    if (tree != NULL) {
        deleteTree(tree->left);
        deleteTree(tree->right);
        free(tree);
    }
    return NULL;
}

// Free memory function
void freeMemory(struct node* tree) {
    deleteTree(tree);
}

// Function to insert an element in the BST
struct node* insertElement(struct node* tree, int val) {
    if (tree == NULL) {
        struct node* newNode = (struct node*)malloc(sizeof(struct node));
        newNode->data = val;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (val < tree->data) {
        tree->left = insertElement(tree->left, val);
    } else {
        tree->right = insertElement(tree->right, val);
    }
    return tree;
}

// Preorder Traversal
void preorderTraversal(struct node* tree) {
    if (tree != NULL) {
        printf("%d\t", tree->data);
        preorderTraversal(tree->left);
        preorderTraversal(tree->right);
    }
}

// Inorder Traversal
void inorderTraversal(struct node* tree) {
    if (tree != NULL) {
        inorderTraversal(tree->left);
        printf("%d\t", tree->data);
        inorderTraversal(tree->right);
    }
}

// Postorder Traversal
void postorderTraversal(struct node* tree) {
    if (tree != NULL) {
        postorderTraversal(tree->left);
        postorderTraversal(tree->right);
        printf("%d\t", tree->data);
    }
}

// Find the smallest element
struct node* findSmallestElement(struct node* tree) {
    if (tree == NULL) return NULL;
    while (tree->left != NULL) {
        tree = tree->left;
    }
    return tree;
}

// Find the largest element
struct node* findLargestElement(struct node* tree) {
    if (tree == NULL) return NULL;
    while (tree->right != NULL) {
        tree = tree->right;
    }
    return tree;
}

// Delete an element from the BST
struct node* deleteElement(struct node* tree, int val) {
    if (tree == NULL) return NULL;

    if (val < tree->data) {
        tree->left = deleteElement(tree->left, val);
    } else if (val > tree->data) {
        tree->right = deleteElement(tree->right, val);
    } else {
        // Node found
        if (tree->left == NULL) {
            struct node* temp = tree->right;
            free(tree);
            return temp;
        } else if (tree->right == NULL) {
            struct node* temp = tree->left;
            free(tree);
            return temp;
        }

        // Node with two children
        struct node* temp = findSmallestElement(tree->right);
        tree->data = temp->data;
        tree->right = deleteElement(tree->right, temp->data);
    }
    return tree;
}

// Main function
int main() {
    struct node* tree = NULL;
    int option, val;

    do {
        printf("\n****** MAIN MENU *******\n");
        printf("1. Insert Element\n");
        printf("2. Preorder Traversal\n");
        printf("3. Inorder Traversal\n");
        printf("4. Postorder Traversal\n");
        printf("5. Find the smallest element\n");
        printf("6. Find the largest element\n");
        printf("7. Delete an element\n");
        printf("8. Count total number of nodes\n");
        printf("9. Count total number of external nodes\n");
        printf("10. Count total number of internal nodes\n");
        printf("11. Determine the height of the tree\n");
        printf("12. Find the mirror image of the tree\n");
        printf("13. Delete the tree\n");
        printf("14. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &option);

        switch(option) {
            case 1:
                printf("Enter the value of the new node: ");
                scanf("%d", &val);
                tree = insertElement(tree, val);
                break;
            case 2:
                printf("Preorder Traversal: ");
                preorderTraversal(tree);
                break;
            case 3:
                printf("Inorder Traversal: ");
                inorderTraversal(tree);
                break;
            case 4:
                printf("Postorder Traversal: ");
                postorderTraversal(tree);
                break;
            case 5:
                {
                    struct node* smallest = findSmallestElement(tree);
                    if (smallest) {
                        printf("Smallest element is: %d\n", smallest->data);
                    } else {
                        printf("Tree is empty.\n");
                    }
                    break;
                }
            case 6:
                {
                    struct node* largest = findLargestElement(tree);
                    if (largest) {
                        printf("Largest element is: %d\n", largest->data);
                    } else {
                        printf("Tree is empty.\n");
                    }
                    break;
                }
            case 7:
                printf("Enter the element to be deleted: ");
                scanf("%d", &val);
                tree = deleteElement(tree, val);
                break;
            case 8:
                printf("Total number of nodes = %d\n", totalNodes(tree));
                break;
            case 9:
                printf("Total number of external nodes = %d\n", totalExternalNodes(tree));
                break;
            case 10:
                printf("Total number of internal nodes = %d\n", totalInternalNodes(tree));
                break;
            case 11:
                printf("The height of the tree = %d\n", height(tree));
                break;
            case 12:
                tree = mirrorImage(tree);
                printf("The mirror image of the tree has been created.\n");
                break;
            case 13:
                tree = deleteTree(tree);
                printf("The tree has been deleted.\n");
                break;
        }
    } while(option != 14);

    freeMemory(tree);
    return 0;
}
