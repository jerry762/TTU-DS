#include <stdio.h>
#include <ctype.h>

#define MAX_LENGTH 100

void printArr(int *arr, size_t len);

int main(void)
{
    char cmd = 0;
    int arr[MAX_LENGTH] = {0};
    size_t len = 0;

    while (tolower(cmd) != 'e')
    {
        printf("Input or delete(i to input | d to delete | e to end): ");

        cmd = getchar();

        switch (tolower(cmd))
        {
        case 'i':
        {
            int num = 0;

            printf("Input number: ");
            scanf("%d", &num);
            getchar();

            arr[len] = num;

            for (size_t i = 0; i < len; i++)
            {
                if (arr[i] > num)
                {
                    for (size_t j = 0; j < len - i; j++)
                    {
                        arr[len - j] = arr[len - 1 - j];
                    }
                    arr[i] = num;
                    break;
                }
            }
            len++;

            printArr(arr, len);
        }
        break;
        case 'd':
        {
            int num = 0;

            printf("Delete number: ");
            scanf("%d", &num);
            getchar();

            for (size_t i = 0; i < len; i++)
            {
                if (arr[i] == num)
                {
                    size_t delNum = 0;

                    for (size_t j = i; j < len; j++)
                    {
                        if (arr[j] == num)
                            delNum++;
                        else
                            arr[i++] = arr[j];
                    }
                    len -= delNum;
                    break;
                }
            }
            printArr(arr, len);
        }
        break;
        case 'e':
            continue;
        default:
            printf("Invalid input !");
            getchar();
            break;
        }
        printf("\n\n");
    }
    return 0;
}

void printArr(int *arr, size_t len)
{
    if (len)
    {
        for (size_t i = 0; i < len; i++)
        {
            printf("%d ", arr[i]);
        }
    }
    else
        printf("Empty !");
}
