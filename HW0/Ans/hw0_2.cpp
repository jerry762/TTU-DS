#include <array>
#include <iostream>

using namespace std;

int main()
{
    char cmd = 0;
    array<int, 100> arr{0};
    int num = 0;
    size_t arrLen = 0;

    while (cmd != 'E' && cmd != 'e')
    {
        cout << "Input or delete: ";
        cin >> cmd;

        if (cmd == 'I' || cmd == 'i')
        {
            cout << "Input number: ";
            cin >> num;

            arr.at(arrLen) = num;

            for (int i = 0; i < arrLen; i++)
            {
                if (arr.at(i) > num)
                {
                    for (int j = 0; j < arrLen - i; j++)
                    {
                        arr.at(arrLen - j) = arr.at(arrLen - 1 - j);
                    }
                    arr.at(i) = num;
                    break;
                }
            }

            arrLen++;
        }
        else if (cmd == 'D' || cmd == 'd')
        {
            cout << "Delete number: ";
            cin >> num;

            for (int i = 0; i < arrLen; i++)
            {
                if (arr.at(i) == num)
                {
                    int delNum = 1;

                    for (int j = i + 1; j < arrLen; j++)
                    {
                        if (arr.at(j) == num)
                            delNum++;
                        else
                        {
                            for (int k = 0; k < arrLen - delNum - i; k++)
                            {
                                arr.at(i + k) = arr.at(j + k);
                            }
                            break;
                        }
                    }
                    arrLen -= delNum;
                    break;
                }
            }
        }

        if (arrLen)
        {
            for (int i = 0; i < arrLen; i++)
            {
                cout << arr.at(i) << " ";
            }
        }
        else
            printf("empty !");

        cout << "\n"
             << endl;
    }

    return 0;
}
