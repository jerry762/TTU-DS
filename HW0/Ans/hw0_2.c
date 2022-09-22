#include <stdio.h>
#include <ctype.h>

#define MAX_LENGTH 100

void printArr(int *arr, int len);

int main(void)
{
    char cmd = 0;
    int arr[MAX_LENGTH] = {0};
    size_t len = 0;
    int num = 0;

    while (tolower(cmd) != 'e')
    {
        printf("Input or delete(i to input | d to delete | e to end): ");

        cmd = getchar();

        switch (tolower(cmd))
        {
        case 'i':
        {
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
            printf("Delete number: ");
            scanf("%d", &num);
            getchar();

            for (size_t i = 0; i < len; i++)
            {
                if (arr[i] == num)
                {
                    int delNum = 1;

                    for (size_t j = i + 1; j < len; j++)
                    {
                        if (arr[j] == num)
                            delNum++;
                        else
                        {
                            for (size_t k = 0; k < len - delNum - i; k++)
                            {
                                arr[i + k] = arr[j + k];
                            }
                            break;
                        }
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
            printf("invalid input !");
            getchar();
            break;
        }
        printf("\n\n");
    }
    return 0;
}

void printArr(int *arr, int len)
{
    if (len)
    {
        for (int i = 0; i < len; i++)
        {
            printf("%d ", arr[i]);
        }
    }
    else
        printf("empty !");
}
