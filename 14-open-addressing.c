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
