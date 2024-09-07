#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Define structure for stack node
struct StackNode {
    char data;
    struct StackNode* next;
};

// Function to create a new node for the stack
struct StackNode* createNode(char data) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to check if the stack is empty
int isEmpty(struct StackNode* top) {
    return top == NULL;
}

// Function to push an element onto the stack
void push(struct StackNode** top, char data) {
    struct StackNode* newNode = createNode(data);
    newNode->next = *top;
    *top = newNode;
}

// Function to pop an element from the stack
char pop(struct StackNode** top) {
    if (isEmpty(*top)) {
        return '\0';  // Return null character if stack is empty
    }
    struct StackNode* temp = *top;
    char poppedData = temp->data;
    *top = (*top)->next;
    free(temp);
    return poppedData;
}

// Function to return the top element of the stack
char peek(struct StackNode* top) {
    if (isEmpty(top)) {
        return '\0';  // Return null character if stack is empty
    }
    return top->data;
}

// Function to check precedence of operators
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

// Function to check if the character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// Function to convert infix to postfix
void infixToPostfix(char* infix) {
    struct StackNode* stack = NULL;
    int i, k = 0;
    int length = strlen(infix);
    char postfix[100];

    for (i = 0; i < length; i++) {
        char ch = infix[i];

        // If the character is an operand, add it to the output
        if (isalnum(ch)) {
            postfix[k++] = ch;
        }
        // If the character is '(', push it to the stack
        else if (ch == '(') {
            push(&stack, ch);
        }
        // If the character is ')', pop and output from the stack until '(' is found
        else if (ch == ')') {
            while (!isEmpty(stack) && peek(stack) != '(') {
                postfix[k++] = pop(&stack);
            }
            pop(&stack);  // Pop '(' from the stack
        }
        // If the character is an operator
        else if (isOperator(ch)) {
            while (!isEmpty(stack) && precedence(peek(stack)) >= precedence(ch)) {
                postfix[k++] = pop(&stack);
            }
            push(&stack, ch);  // Push the current operator onto the stack
        }
    }

    // Pop the remaining operators from the stack
    while (!isEmpty(stack)) {
        postfix[k++] = pop(&stack);
    }

    postfix[k] = '\0';  // Null-terminate the postfix expression
    printf("Postfix Expression: %s\n", postfix);
}

int main() {
    char infix[100];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix);

    return 0;
}
