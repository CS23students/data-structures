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
            free(newNode); // Free unused node
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

// Function to subtract two polynomials
struct Node* subtractPoly(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exp > poly2->exp) {
            insertTerm(&result, poly1->coeff, poly1->exp);
            poly1 = poly1->next;
        } else if (poly1->exp < poly2->exp) {
            insertTerm(&result, -poly2->coeff, poly2->exp); // Subtract the coefficient
            poly2 = poly2->next;
        } else {
            insertTerm(&result, poly1->coeff - poly2->coeff, poly1->exp);
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
        insertTerm(&result, -poly2->coeff, poly2->exp); // Subtract remaining terms
        poly2 = poly2->next;
    }

    return result;
}

// Function to free the polynomial linked list
void freePoly(struct Node* poly) {
    struct Node* temp;
    while (poly != NULL) {
        temp = poly;
        poly = poly->next;
        free(temp);
    }
}

// Function to get polynomial terms from the user
void getPolynomialInput(struct Node** poly) {
    int n, coeff, exp;
    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and exponent for term %d: ", i + 1);
        scanf("%d %d", &coeff, &exp);
        insertTerm(poly, coeff, exp);
    }
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    struct Node* result = NULL;

    printf("Input for Polynomial 1:\n");
    getPolynomialInput(&poly1);

    printf("Input for Polynomial 2:\n");
    getPolynomialInput(&poly2);

    printf("Polynomial 1: ");
    displayPoly(poly1);

    printf("Polynomial 2: ");
    displayPoly(poly2);

    // Add the two polynomials
    result = addPoly(poly1, poly2);
    printf("Resultant Polynomial after addition: ");
    displayPoly(result);
    freePoly(result); // Free memory after use

    // Subtract the two polynomials
    result = subtractPoly(poly1, poly2);
    printf("Resultant Polynomial after subtraction: ");
    displayPoly(result);
    freePoly(result); // Free memory after use

    // Free memory for original polynomials
    freePoly(poly1);
    freePoly(poly2);

    return 0;
}


// Sample Output: 
// Input for Polynomial 1:
// Enter the number of terms in the polynomial: 3
// Enter coefficient and exponent for term 1: 4 3
// Enter coefficient and exponent for term 2: 5 2
// Enter coefficient and exponent for term 3: 6 0
// Input for Polynomial 2:
// Enter the number of terms in the polynomial: 3
// Enter coefficient and exponent for term 1: 2 2
// Enter coefficient and exponent for term 2: 5 1
// Enter coefficient and exponent for term 3: 3 0
// Polynomial 1: 4x^3 + 5x^2 + 6x^0
// Polynomial 2: 2x^2 + 5x^1 + 3x^0
// Resultant Polynomial after addition: 4x^3 + 7x^2 + 5x^1 + 9x^0
// Resultant Polynomial after subtraction: 4x^3 + 3x^2-5x^1 + 3x^0
