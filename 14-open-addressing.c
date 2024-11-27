// ARRAY IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>

// Global variables
int ch, tsize;

// Hash function
int hasht(int key) {
    return key % tsize;
}

// Linear probing rehash function
int rehashl(int key) {
    return (key + 1) % tsize;
}

// Quadratic probing rehash function
int rehashq(int key, int j) {
    return (key + (j * j)) % tsize;
}

// Insertion function
void insertion(int arr[], int hash[], int n) {
    int key, i, k, j;
    if (ch == 1) {  // Linear probing
        for (k = 0; k < n; k++) {
            key = arr[k];
            i = hasht(key);
            while (hash[i] != -1) {
                i = rehashl(i);
            }
            hash[i] = key;
        }
    } else {  // Quadratic probing
        for (k = 0; k < n; k++) {
            j = 1;
            key = arr[k];
            i = hasht(key);
            while (hash[i] != -1) {
                i = rehashq(i, j);
                j++;
            }
            hash[i] = key;
        }
    }

    printf("\nThe elements in the hash table are:\n");
    for (i = 0; i < tsize; i++)
        printf("Element at position %d: %d\n", i, hash[i]);
}

// Search function
void search(int arr[], int n) {
    int an, i, t = 0;
    printf("Enter the search element: ");
    scanf("%d", &an);
    for (i = 0; i < n; i++) {
        if (arr[i] == an) {
            printf("%d found at position %d\n", an, i + 1);
            t = 1;
        }
    }
    if (t == 0)
        printf("Not found\n");
}

// Delete function
void deleteElement(int hash[], int tsize) {
    int d, i;
    printf("Enter the element to delete: ");
    scanf("%d", &d);
    for (i = 0; i < tsize; i++) {
        if (hash[i] == d) {
            hash[i] = -1;
        }
    }
    printf("The hash table elements after deletion are:\n");
    for (i = 0; i < tsize; i++) {
        printf("Element at position %d: %d\n", i, hash[i]);
    }
}

// Main function
void main() {
    int arr[20], hash[20], n, op = 0;

    printf("Enter the size of the hash table: ");
    scanf("%d", &tsize);

    for (int i = 0; i < tsize; i++)  // Initialize hash table
        hash[i] = -1;

    do {
        printf("\n1. Linear Probing\n2. Quadratic Probing\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        if (ch == 3) {
            break;
        } else {
            printf("\n1. Insertion\n2. Search\n3. Delete\n4. Exit\n");
        }

        do {
            printf("\nEnter your option: ");
            scanf("%d", &op);

            switch (op) {
                case 1:
                    printf("Enter the number of elements: ");
                    scanf("%d", &n);
                    printf("Enter elements: ");
                    for (int i = 0; i < n; i++) {
                        scanf("%d", &arr[i]);
                    }
                    insertion(arr, hash, n);
                    break;

                case 2:
                    search(arr, n);
                    break;

                case 3:
                    deleteElement(hash, tsize);
                    break;

                case 4:
                    break;

                default:
                    printf("Invalid choice\n");
                    break;
            }
        } while (op != 4);
    } while (ch != 3);
}


// ---------------------------------------------------------------------------------------------------------------------------------//


// STRUCUTURE IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10  // Define the size of the hash table
#define EMPTY -1       // Define empty slots in the hash table
#define DELETED -2     // Define deleted slots in the hash table

// Hash table structure
struct HashTable {
    int *table;    // Array to store the values
    int size;      // Size of the hash table
};

// Function to create a hash table
struct HashTable* createHashTable(int size) {
    struct HashTable* hashTable = (struct HashTable*)malloc(sizeof(struct HashTable));
    hashTable->size = size;
    hashTable->table = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        hashTable->table[i] = EMPTY;  // Initialize all slots to EMPTY
    }
    return hashTable;
}

// Hash function (simple modulo)
int hashFunction(int key, int size) {
    return key % size;
}

// Linear Probing Insertion
void insertLinearProbing(struct HashTable* hashTable, int key) {
    int index = hashFunction(key, hashTable->size);
    int originalIndex = index;
    
    while (hashTable->table[index] != EMPTY && hashTable->table[index] != DELETED) {
        index = (index + 1) % hashTable->size;  // Linear probing: increment by 1
        if (index == originalIndex) {  // Table is full
            printf("Hash table is full\n");
            return;
        }
    }
    hashTable->table[index] = key;
}

// Quadratic Probing Insertion
void insertQuadraticProbing(struct HashTable* hashTable, int key) {
    int index = hashFunction(key, hashTable->size);
    int i = 0;

    while (hashTable->table[index] != EMPTY && hashTable->table[index] != DELETED) {
        index = (hashFunction(key, hashTable->size) + i * i) % hashTable->size;  // Quadratic probing: increment by i^2
        i++;
        if (i >= hashTable->size) {  // Table is full
            printf("Hash table is full\n");
            return;
        }
    }
    hashTable->table[index] = key;
}

// Linear Probing Search
int searchLinearProbing(struct HashTable* hashTable, int key) {
    int index = hashFunction(key, hashTable->size);
    int originalIndex = index;

    while (hashTable->table[index] != EMPTY) {
        if (hashTable->table[index] == key) {
            return index;
        }
        index = (index + 1) % hashTable->size;  // Linear probing
        if (index == originalIndex) {  // Wrapped around to the original index
            return -1;
        }
    }
    return -1;
}

// Quadratic Probing Search
int searchQuadraticProbing(struct HashTable* hashTable, int key) {
    int index = hashFunction(key, hashTable->size);
    int i = 0;

    while (hashTable->table[index] != EMPTY) {
        if (hashTable->table[index] == key) {
            return index;
        }
        index = (hashFunction(key, hashTable->size) + i * i) % hashTable->size;  // Quadratic probing
        i++;
        if (i >= hashTable->size) {
            return -1;  // Not found
        }
    }
    return -1;  // Key not found
}

// Linear Probing Deletion
void deleteLinearProbing(struct HashTable* hashTable, int key) {
    int index = searchLinearProbing(hashTable, key);
    if (index != -1) {
        hashTable->table[index] = DELETED;
        printf("Key %d deleted using Linear Probing\n", key);
    } else {
        printf("Key %d not found using Linear Probing\n", key);
    }
}

// Quadratic Probing Deletion
void deleteQuadraticProbing(struct HashTable* hashTable, int key) {
    int index = searchQuadraticProbing(hashTable, key);
    if (index != -1) {
        hashTable->table[index] = DELETED;
        printf("Key %d deleted using Quadratic Probing\n", key);
    } else {
        printf("Key %d not found using Quadratic Probing\n", key);
    }
}

// Function to display the hash table
void displayHashTable(struct HashTable* hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->table[i] == EMPTY) {
            printf("Slot %d: EMPTY\n", i);
        } else if (hashTable->table[i] == DELETED) {
            printf("Slot %d: DELETED\n", i);
        } else {
            printf("Slot %d: %d\n", i, hashTable->table[i]);
        }
    }
}

// Main function
int main() {
    int choice, key, n, probeChoice;
    
    struct HashTable* hashTable = createHashTable(TABLE_SIZE);
    
    printf("Choose probing technique:\n1. Linear Probing\n2. Quadratic Probing\n");
    scanf("%d", &probeChoice);
    
    printf("Enter the number of keys to insert: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        printf("Enter key to insert: ");
        scanf("%d", &key);

        if (probeChoice == 1) {
            insertLinearProbing(hashTable, key);
        } else if (probeChoice == 2) {
            insertQuadraticProbing(hashTable, key);
        } else {
            printf("Invalid choice for probing technique!\n");
            return 1;
        }
    }
    
    printf("Hash table after insertions:\n");
    displayHashTable(hashTable);

    printf("\nEnter key to search: ");
    scanf("%d", &key);
    int index;
    if (probeChoice == 1) {
        index = searchLinearProbing(hashTable, key);
    } else {
        index = searchQuadraticProbing(hashTable, key);
    }
    if (index != -1) {
        printf("Key %d found at index %d\n", key, index);
    } else {
        printf("Key %d not found\n", key);
    }

    printf("\nEnter key to delete: ");
    scanf("%d", &key);
    if (probeChoice == 1) {
        deleteLinearProbing(hashTable, key);
    } else {
        deleteQuadraticProbing(hashTable, key);
    }
    
    printf("Hash table after deletion:\n");
    displayHashTable(hashTable);

    // Free memory
    free(hashTable->table);
    free(hashTable);

    return 0;
}
