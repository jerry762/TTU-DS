#include <array>
#include <iostream>
#include <cctype>

#define MAX_LENGTH 100

using namespace std;

void printArr(array<int, MAX_LENGTH> &arr, size_t arrLen);

int main()
{
    char cmd = 0;
    array<int, MAX_LENGTH> arr{0};
    size_t arrLen = 0;

    while (tolower(cmd) != 'e')
    {
        cout << "Input or delete(i to input | d to delete | e to end): ";
        cin >> cmd;

        if (cmd == 'i')
        {
            int num = 0;

            cout << "Input number: ";
            cin >> num;
            arr.at(arrLen) = num;

            for (size_t i = 0; i < arrLen; i++)
            {
                if (arr.at(i) > num)
                {
                    for (size_t j = 0; j < arrLen - i; j++)
                    {
                        arr.at(arrLen - j) = arr.at(arrLen - 1 - j);
                    }
                    arr.at(i) = num;
                    break;
                }
            }
            arrLen++;
        }
        if (cmd == 'd')
        {
            int num = 0;

            cout << "Delete number: ";
            cin >> num;

            for (size_t i = 0; i < arrLen; i++)
            {
                if (arr.at(i) == num)
                {
                    size_t delNum = 0;

                    for (size_t j = i; j < arrLen; j++)
                    {
                        if (arr.at(j) == num)
                            delNum++;
                        else
                            arr.at(i++) = arr.at(j);
                    }
                    arrLen -= delNum;
                    break;
                }
            }
        }
        printArr(arr, arrLen);
    }
    return 0;
}

void printArr(array<int, MAX_LENGTH> &arr, size_t arrLen)
{
    if (arrLen)
    {
        for (size_t i = 0; i < arrLen; i++)
        {
            cout << arr.at(i) << " ";
        }
    }
    else
        cout << "Empty !";
    cout << endl;
}
