#include <stdio.h>
#include <stdlib.h>

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

    while (cmd != 'E' && cmd != 'e')
    {
        printf("Input or delete: ");

        scanf("%c", &cmd);

        if (cmd == 'I' || cmd == 'i')
        {
            Node *newNode = (Node *)calloc(1, sizeof(Node));

            printf("Input number: ");
            scanf("%d", &num);
            getchar();

            newNode->value = num;

            if (list.headNode == NULL)
                list.headNode = newNode;
            else
            {
                Node *currNode = list.headNode;
                Node *prevNode = NULL;

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
        }
        else if (cmd == 'D' || cmd == 'd')
        {
            if (list.headNode)
            {
                Node *currNode = list.headNode;
                Node *prevNode = NULL;

                printf("Delete number: ");
                scanf("%d", &num);
                getchar();

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

        printf("\n\n");
    }

    return 0;
}
