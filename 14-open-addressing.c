// ARRAY IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
int ch;

int tsize, count;
int hasht(int key)
{
    int i;
    i = key % tsize;
    return i;
}
//-------LINEAR PROBING-------
int rehashl(int key)
{
    int i;
    i = (key + 1) % tsize;
    return i;
}
//-------QUADRATIC PROBING-------
int rehashq(int key, int j)
{
    int i;
    i = (key + (j * j)) % tsize;
    return i;
}

int Search(int ele, int arr[], int n)
{
    int i, t = 0;
    for (i = 0; i < n; i++)
        printf("%d\t", arr[i]);
    if (ele == arr[i])
        return 1;
    else
        return 0;
}

void main()
{
    int an, key, arr[20], hash[20], i, n, s, op = 0, j, k, d;

    printf("Enter the size of the hash table: ");
    scanf("%d", &tsize);

    do
    {
        printf("1.Linear probing\n2.Quadratic probing\n3.Exit\n");
        printf("\nEnter your choice:");
        scanf("%d", &ch);

        if (ch == 3)
            break;
        else
        {
            if (ch == 1)
                printf("\nLinear Probing:\n");
            else
                printf("\nQuadratic Probing:\n");
            printf("\n1.Insertion\n2.search\n3.delete \n4.Exit\n");
        }
        do
        {
            printf("\n\nEnter your option: ");

            scanf("%d", &op);
            switch (op)
            {

            case 1:

                printf("\nEnter the number of elements: ");
                scanf("%d", &n);
                for (i = 0; i < tsize; i++)
                    hash[i] = -1;
                printf("Enter Elements: ");
                for (i = 0; i < n; i++)
                {
                    scanf("%d", &arr[i]);
                }
                printf("\nElements:\n");
                for (i = 0; i < n; i++)
                    printf("%d\t", arr[i]);

                if (ch == 1)
                {
                    for (i = 0; i < tsize; i++)
                        hash[i] = -1;
                    for (k = 0; k < n; k++)
                    {
                        key = arr[k];
                        i = hasht(key);
                        while (hash[i] != -1)
                        {
                            i = rehashl(i);
                        }
                        hash[i] = key;
                    }
                    printf("\nThe elements in the array are: ");
                    for (i = 0; i < tsize; i++)
                        printf("\n Element at position %d: %d", i, hash[i]);
                }
                else
                {
                    for (i = 0; i < tsize; i++)
                        hash[i] = -1;
                    ;
                    for (k = 0; k < n; k++)
                    {
                        j = 1;
                        key = arr[k];
                        i = hasht(key);
                        while (hash[i] != -1)
                        {
                            i = rehashq(i, j);
                            j++;
                        }
                        hash[i] = key;
                    }
                    printf("\nThe elements in the array are: ");
                    for (i = 0; i < tsize; i++)
                    {
                        printf("\n Element at position %d: %d", i, hash[i]);
                    }
                }

                break;

            case 2:
                printf("Enter the search element");
                scanf("%d", &an);
                int i, t = 0;
                for (i = 0; i < n; i++)
                {
                    if (arr[i] == an)
                    {
                        printf("%d Found at position %d",an,i+1);
                        t = 1;
                    }
                }
                if (t == 0)
                    printf("Not found");
                break;

            case 3:
                printf("Enter the element to delete");
                scanf("%d", &d);
                for (i = 0; i < tsize; i++)
                {
                    if (hash[i] == d)
                        hash[i] = -1;
                }
                printf("The hash table elements after deleting are\n\n");
                for (i = 0; i < tsize; i++)
                {
                    printf("\n Element at position %d: %d", i, hash[i]);
                }
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
