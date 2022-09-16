#include <stdio.h>

int main(void)
{
    char cmd = 0;
    int arr[100] = {0};
    size_t len = 0;
    int num = 0;

    while (cmd != 'E' && cmd != 'e')
    {
        printf("Input or delete: ");

        scanf("%c", &cmd);

        if (cmd == 'I' || cmd == 'i')
        {
            printf("Input number: ");
            scanf("%d", &num);
            getchar();

            arr[len] = num;

            for (int i = 0; i < len; i++)
            {
                if (arr[i] > num)
                {
                    for (int j = 0; j < len - i; j++)
                    {
                        arr[len - j] = arr[len - 1 - j];
                    }
                    arr[i] = num;
                    break;
                }
            }
            len++;
        }
        else if (cmd == 'D' || cmd == 'd')
        {
            printf("Delete number: ");
            scanf("%d", &num);
            getchar();

            for (int i = 0; i < len; i++)
            {
                if (arr[i] == num)
                {
                    int delNum = 1;

                    for (int j = i + 1; j < len; j++)
                    {
                        if (arr[j] == num)
                            delNum++;
                        else
                        {
                            for (int k = 0; k < len - delNum - i; k++)
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
        }

        if (len)
        {
            for (int i = 0; i < len; i++)
            {
                printf("%d ", arr[i]);
            }
        }
        else
            printf("empty !");

        printf("\n\n");
    }
    return 0;
}