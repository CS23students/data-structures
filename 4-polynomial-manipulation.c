#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
struct Node {
    int coeff;      // Coefficient of the term
    int exp;        // Exponent of the term
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int coeff, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a term in the polynomial
void insertTerm(struct Node** poly, int coeff, int exp) {
    struct Node* newNode = createNode(coeff, exp);
    
    // If the list is empty or the exponent is larger than the first node
    if (*poly == NULL || (*poly)->exp < exp) {
        newNode->next = *poly;
        *poly = newNode;
    } else {
        struct Node* temp = *poly;
        while (temp->next != NULL && temp->next->exp > exp) {
            temp = temp->next;
        }
        if (temp->next != NULL && temp->next->exp == exp) {
            temp->next->coeff += coeff;  // Add coefficients if exponent is the same
        } else {
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
}

// Function to display the polynomial
void displayPoly(struct Node* poly) {
    struct Node* temp = poly;
    while (temp != NULL) {
        printf("%dx^%d", temp->coeff, temp->exp);
        if (temp->next != NULL && temp->next->coeff >= 0) {
            printf(" + ");
        }
        temp = temp->next;
    }
    printf("\n");
}

// Function to add two polynomials
struct Node* addPoly(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exp > poly2->exp) {
            insertTerm(&result, poly1->coeff, poly1->exp);
            poly1 = poly1->next;
        } else if (poly1->exp < poly2->exp) {
            insertTerm(&result, poly2->coeff, poly2->exp);
            poly2 = poly2->next;
        } else {
            insertTerm(&result, poly1->coeff + poly2->coeff, poly1->exp);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    // Add remaining terms
    while (poly1 != NULL) {
        insertTerm(&result, poly1->coeff, poly1->exp);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) {
        insertTerm(&result, poly2->coeff, poly2->exp);
        poly2 = poly2->next;
    }

    return result;
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    struct Node* result = NULL;

    // Polynomial 1: 3x^3 + 4x^2 + 5
    insertTerm(&poly1, 3, 3);
    insertTerm(&poly1, 4, 2);
    insertTerm(&poly1, 5, 0);

    // Polynomial 2: 5x^2 + 2x + 3
    insertTerm(&poly2, 5, 2);
    insertTerm(&poly2, 2, 1);
    insertTerm(&poly2, 3, 0);

    printf("Polynomial 1: ");
    displayPoly(poly1);

    printf("Polynomial 2: ");
    displayPoly(poly2);

    // Add the two polynomials
    result = addPoly(poly1, poly2);

    printf("Resultant Polynomial after addition: ");
    displayPoly(result);

    return 0;
}
