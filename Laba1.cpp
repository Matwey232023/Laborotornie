#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    const int size = 10;                // размер кол и столбцов матрицы
    int arr[size][size];                // матрица
    double res[size / 2] = { NULL };    // массив для хранения результатов

    // инициализирую матрицу случайными числами
    srand((unsigned int)time(NULL));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            arr[i][j] = rand() % 10;

    // вывожу массив на экран
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++) cout << arr[i][j];
        cout << endl;
    }

    // нахожу среднее арифметическое элементов 
    // каждого из четных столбцов матрицы
    for (int j = 0; j < size; j++)
        for (int i = 0; i < size; i++)
            if (i != 0 && i % 2 != 0)
                res[i / 2 - 1] += arr[i][j];

    for (int i = 0; i < sizeof(res) / sizeof(double); i++) res[i] /= size;

    // вывожу результат на экран
    // (счёт столбцов начинается с нуля)
    cout << endl;
    for (int i = 0; i < size / 2; i++)
        cout << "average " << 2 * (i + 1) << " column = " << res[i] << endl;

    cout << "---------------------------" << endl;
    system("pause");
    return 0;
}