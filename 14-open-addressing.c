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

// SAMPLE OUTPUT :
// Choose probing technique:
// 1. Linear Probing
// 2. Quadratic Probing
// 1
// Enter the number of keys to insert: 4
// Enter key to insert: 4 10
// Enter key to insert: 20
// Enter key to insert: 30
// Enter key to insert: 40
// Hash table after insertions:
// Slot 0: 10
// Slot 1: 20
// Slot 2: 30
// Slot 3: 40
// Slot 4: EMPTY
// Slot 5: EMPTY
// Slot 6: EMPTY
// Slot 7: EMPTY
// Slot 8: EMPTY
// Slot 9: EMPTY

// Enter key to search: 20
// Key 20 found at index 1

// Enter key to delete: 20
// Key 20 deleted using Linear Probing
// Hash table after deletion:
// Slot 0: 10
// Slot 1: DELETED
// Slot 2: 30
// Slot 3: 40
// Slot 4: EMPTY
// Slot 5: EMPTY
// Slot 6: EMPTY
// Slot 7: EMPTY
// Slot 8: EMPTY
// Slot 9: EMPTY


// SAMPLE OUTPUT :
// Choose probing technique:
// 1. Linear Probing
// 2. Quadratic Probing
// 1 2
// Enter the number of keys to insert: 4
// Enter key to insert: 20
// Enter key to insert: 2 30
// Enter key to insert: 50
// Enter key to insert: 60
// Hash table after insertions:
// Slot 0: 20
// Slot 1: 30
// Slot 2: EMPTY
// Slot 3: EMPTY
// Slot 4: 50
// Slot 5: EMPTY
// Slot 6: EMPTY
// Slot 7: EMPTY
// Slot 8: EMPTY
// Slot 9: 60

// Enter key to search: 30
// Key 30 found at index 1

// Enter key to delete: 50
// Key 50 deleted using Quadratic Probing
// Hash table after deletion:
// Slot 0: 20
// Slot 1: 30
// Slot 2: EMPTY
// Slot 3: EMPTY
// Slot 4: DELETED
// Slot 5: EMPTY
// Slot 6: EMPTY
// Slot 7: EMPTY
// Slot 8: EMPTY
// Slot 9: 60
