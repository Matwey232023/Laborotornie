#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    const int size = 10;                // ������ ��� � �������� �������
    int arr[size][size];                // �������
    double res[size / 2] = { NULL };    // ������ ��� �������� �����������

    // ������������� ������� ���������� �������
    srand((unsigned int)time(NULL));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            arr[i][j] = rand() % 10;

    // ������ ������ �� �����
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++) cout << arr[i][j];
        cout << endl;
    }

    // ������ ������� �������������� ��������� 
    // ������� �� ������ �������� �������
    for (int j = 0; j < size; j++)
        for (int i = 0; i < size; i++)
            if (i != 0 && i % 2 != 0)
                res[i / 2 - 1] += arr[i][j];

    for (int i = 0; i < sizeof(res) / sizeof(double); i++) res[i] /= size;

    // ������ ��������� �� �����
    // (���� �������� ���������� � ����)
    cout << endl;
    for (int i = 0; i < size / 2; i++)
        cout << "average " << 2 * (i + 1) << " column = " << res[i] << endl;

    cout << "---------------------------" << endl;
    system("pause");
    return 0;
}