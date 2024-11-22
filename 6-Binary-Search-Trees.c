#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the BST
struct node {
    int data;
    struct node *left;
    struct node *right;
};

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

// Function to delete an element from the BST
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
        struct node* temp = tree->right;
        while (temp && temp->left != NULL) {
            temp = temp->left;
        }
        tree->data = temp->data;
        tree->right = deleteElement(tree->right, temp->data);
    }
    return tree;
}

// Function to search for an element in the BST
struct node* searchElement(struct node* tree, int val) {
    if (tree == NULL || tree->data == val) {
        return tree;
    }
    if (val < tree->data) {
        return searchElement(tree->left, val);
    } else {
        return searchElement(tree->right, val);
    }
}

// Preorder Traversal (Node → Left → Right)
void preorderTraversal(struct node* tree) {
    if (tree != NULL) {
        printf("%d\t", tree->data);
        preorderTraversal(tree->left);
        preorderTraversal(tree->right);
    }
}

// Inorder Traversal (Left → Node → Right)
void inorderTraversal(struct node* tree) {
    if (tree != NULL) {
        inorderTraversal(tree->left);
        printf("%d\t", tree->data);
        inorderTraversal(tree->right);
    }
}

// Postorder Traversal (Left → Right → Node)
void postorderTraversal(struct node* tree) {
    if (tree != NULL) {
        postorderTraversal(tree->left);
        postorderTraversal(tree->right);
        printf("%d\t", tree->data);
    }
}

// Main function
int main() {
    struct node* tree = NULL;
    int option, val;

    do {
        printf("\n****** MAIN MENU *******\n");
        printf("1. Insert Element\n");
        printf("2. Delete Element\n");
        printf("3. Search Element\n");
        printf("4. Preorder Traversal\n");
        printf("5. Inorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("7. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &option);

        switch(option) {
            case 1:
                printf("Enter the value of the new node: ");
                scanf("%d", &val);
                tree = insertElement(tree, val);
                break;
            case 2:
                printf("Enter the value to be deleted: ");
                scanf("%d", &val);
                tree = deleteElement(tree, val);
                break;
            case 3:
                printf("Enter the value to search: ");
                scanf("%d", &val);
                struct node* foundNode = searchElement(tree, val);
                if (foundNode) {
                    printf("Element %d found in the tree.\n", foundNode->data);
                } else {
                    printf("Element %d not found in the tree.\n", val);
                }
                break;
            case 4:
                printf("Preorder Traversal: ");
                preorderTraversal(tree);
                printf("\n");
                break;
            case 5:
                printf("Inorder Traversal: ");
                inorderTraversal(tree);
                printf("\n");
                break;
            case 6:
                printf("Postorder Traversal: ");
                postorderTraversal(tree);
                printf("\n");
                break;
        }
    } while(option != 7);

    return 0;
}
