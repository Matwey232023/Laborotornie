#include <iostream>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Дата приобретения
struct TDate
{
	int d, m, y;
};
// Элементы трансформатора
struct TDetail
{
	int oil_tank;
	int primary_winding;
	int secondary_winding;
	int conclusions_of_the_primary_winding;
	int secondary_winding_terminals;
	int gas_relay;
};
// Трансформатор
struct TTransform
{
	char name[35]; // '\0'
	char firma[22];
	TDetail detail;
	float mass;
	TDate date;
};

// Пользовательские функции
void CinTransform(TTransform& transform)
{
	cout << "Название Трансформатора --> ";
	cin.getline(transform.name, 15);

	cout << "Фирма изготовитель --> ";
	cin.getline(transform.firma, 20);

	cout << "Комплектация трансформатора всеми перечисленными деталями (либо 0 либо 1):" << endl;
	cout << "Масляный бак --> ";
	cin >> transform.detail.oil_tank;
	cout << "Первичная обмотка --> ";
	cin >> transform.detail.primary_winding;
	cout << "Вторичная обмотка --> ";
	cin >> transform.detail.secondary_winding;
	cout << "Выводы первичной обмотки --> ";
	cin >> transform.detail.conclusions_of_the_primary_winding;
	cout << "Выводы вторичной обмотки --> ";
	cin >> transform.detail.secondary_winding_terminals;
	cout << "Газовое реле --> ";
	cin >> transform.detail.gas_relay;

	cout << "Масса трансформатора --> ";
	cin >> transform.mass;

	cout << "Дата приобретения:" << endl;
	cout << "День --> "; cin >> transform.date.d;
	cout << "Месяц --> "; cin >> transform.date.m;
	cout << "Год --> "; cin >> transform.date.y;

	cin.clear();
	while (!isspace(cin.get()))
		continue;
}
// Вывод Трансформатора
void CoutTransform(TTransform transform)
{
	cout << "Название трансформатора: " << transform.name << endl
		<< "Фирма изготовитель:" << transform.firma << endl
		<< "\nУстановленные детали:" << endl
		<< "Масляный бак:" << transform.detail.oil_tank << endl
		<< "Первичная обмотка: " << transform.detail.primary_winding << endl
		<< "Вторичная обмотка: " << transform.detail.secondary_winding << endl
		<< "Выводы первичной обмотки: " << transform.detail.conclusions_of_the_primary_winding << endl
		<< "Выводы вторичной обмотки: " << transform.detail.secondary_winding_terminals << endl
		<< "Газовое реле --> " << transform.detail.gas_relay << endl
		<< "Масса трансформатора: " << transform.mass << endl
		<< "\nДата приобретения:" << endl
		<< "День --> " << transform.date.d << endl
		<< "Месяц --> " << transform.date.m << endl
		<< "Год --> " << transform.date.y << endl;
	cout << endl;
}
//** размер файла *****************************
long filesize(FILE* f)
{
	long curpos, length;

	curpos = ftell(f);		//запоминаем текущее положение
	fseek(f, 0L, SEEK_END);	//перемещаем на конец файла
	length = ftell(f);		//запоминаем положение в конце файла
	fseek(f, curpos, SEEK_SET);	//перемещаем на старое положение
	return length;
}
int main()
{
	setlocale(LC_ALL, "rus");
	int N;
	//	cout << "Введите количество трансформаторов для записи в базу данных --> ";
	//	cin >> N;
	//	
	//	cin.clear(); //очистить поток и затем выставить позиционирование в 0
	//	while (!isspace(cin.get()))
	//    	continue;            //Избавиться от результатов неверного ввода

	TTransform transform;

	cout << "Пример работы со структурой" << endl;

	FILE* f, * g; // описание файловой переменной
	f = fopen("Transform.txt", "a");	// w, r, a, w+, r+, wt, rt, wb, rb 

	//.....
	//fclose(f);

//	cout << "Ввод данных о трансформаторе:"<< endl;
//	
//	for (int i = 0; i < N; i++)
//	{
//		cout << i+1 << " трансформатор:\n";
//		CinTransform(transform);
//		fwrite(&transform, sizeof(transform), 1, f);
//	}


	//system("cls");

	long n = filesize(f);	//Размер файла Transform.txt
	N = n / sizeof(TTransform); // Количество записей в файле
	cout << "Размер файла Transform.txt --> " << n << " байт" << endl
		<< "Размер структуры Transform --> " << sizeof(TTransform) << " байт" << endl
		<< "Количество записей в файле --> " << N << endl;



	cout << "\n\nВывод данных о трансформаторе:\n\n";
	fclose(f);

	TTransform* massiv = NULL;	// 4 byte
	massiv = new TTransform[500000];	// описание динамического массива

	f = fopen("Transform.txt", "r");
	//for (int i = 0; i < N; i++)
	int i = 0;
	while (fread(&transform, sizeof(transform), 1, f))	// !eof(f)
	{
		cout << i + 1 << " трансформатор:\n";
		massiv[i] = transform;
		CoutTransform(massiv[i]);
		i++;
	}
	fclose(f);

	// Найти трансформатор с масляным баком
	cout << "\n\n Список трансформаторов с масляным баком:\n\n";
	int k = 0;
	for (int i = 0; i < N; i++)
	{
		if (massiv[i].detail.oil_tank == 1)
		{
			k++;
			cout << k << " Трансформатор с масляным баком" << endl;
			CoutTransform(massiv[i]);
			cout << "****************************\n";
		}
	}

	// Найти трансформатор купленный у некоторой фирмы
	char search_firma[22];
	cout << "Введите название Фирмы для поиска по базе данных --> ";
	cin.getline(search_firma, 20);
	cout << "\n\n Список трансформаторов купленных у фирмы: " << search_firma << endl;
	k = 0;
	for (int i = 0; i < N; i++)
	{
		if (strcmp(massiv[i].firma, search_firma) == 0)
		{
			k++;
			cout << k << " Трансформатор купленный у фирмы: " << search_firma << endl;
			CoutTransform(massiv[i]);
			cout << "****************************\n\n";
		}
	}

	delete[] massiv;

	cout << endl;
	system("pause");
	return 0;
}