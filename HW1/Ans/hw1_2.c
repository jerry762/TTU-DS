#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node Node;
typedef struct List List;

struct Node
{
    int value;
    Node *nextNode;
};

struct List
{
    Node *headNode;
};

int main(void)
{
    List list;
    char cmd = 0;
    int num = 0;

    list.headNode = NULL;

    while (tolower(cmd) != 'e')
    {
        printf("Input or delete: ");

        scanf("%c", &cmd);

        switch (tolower(cmd))
        {
        case 'i':
            printf("Input number: ");
            scanf("%d", &num);

            if (list.headNode == NULL)
            {
                Node *newNode = (Node *)calloc(1, sizeof(Node));
                newNode->value = num;

                list.headNode = newNode;
            }
            else
            {
                Node *newNode = (Node *)calloc(1, sizeof(Node));
                Node *currNode = list.headNode;
                Node *prevNode = NULL;

                newNode->value = num;

                while (currNode)
                {
                    if (currNode->value > num)
                    {
                        if (list.headNode == currNode)
                            list.headNode = newNode;
                        else
                            prevNode->nextNode = newNode;

                        newNode->nextNode = currNode;
                        break;
                    }
                    prevNode = currNode;
                    currNode = currNode->nextNode;
                }
                if (!currNode)
                    prevNode->nextNode = newNode;
            }
            break;
        case 'd':
            if (list.headNode)
            {
                Node *currNode = list.headNode;
                Node *prevNode = NULL;

                printf("Delete number: ");
                scanf("%d", &num);

                while (currNode)
                {
                    if (currNode->value == num)
                    {
                        Node *delNode = NULL;

                        while (currNode && currNode->value == num)
                        {
                            delNode = currNode;
                            currNode = currNode->nextNode;
                            free(delNode);
                        }

                        if (prevNode)
                            prevNode->nextNode = currNode;
                        else
                            list.headNode = currNode;

                        break;
                    }
                    prevNode = currNode;
                    currNode = currNode->nextNode;
                }
            }
            break;
        default:
            printf("invalid input !\n\n");
            getchar();
            continue;
        }

        if (list.headNode)
        {
            Node *currNode = list.headNode;

            while (currNode)
            {
                printf("%d ", currNode->value);
                currNode = currNode->nextNode;
            }
        }
        else
            printf("empty !");

        getchar();
        printf("\n\n");
    }

    return 0;
}
