#include <iostream>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

// ���� ������������
struct TDate
{
	int d, m, y;
};
// �������� ��������������
struct TDetail
{
	int oil_tank;
	int primary_winding;
	int secondary_winding;
	int conclusions_of_the_primary_winding;
	int secondary_winding_terminals;
	int gas_relay;
};
// �������������
struct TTransform
{
	char name[35]; // '\0'
	char firma[22];
	TDetail detail;
	float mass;
	TDate date;
};

// ���������������� �������
void CinTransform(TTransform& transform)
{
	cout << "�������� �������������� --> ";
	cin.getline(transform.name, 15);

	cout << "����� ������������ --> ";
	cin.getline(transform.firma, 20);

	cout << "������������ �������������� ����� �������������� �������� (���� 0 ���� 1):" << endl;
	cout << "�������� ��� --> ";
	cin >> transform.detail.oil_tank;
	cout << "��������� ������� --> ";
	cin >> transform.detail.primary_winding;
	cout << "��������� ������� --> ";
	cin >> transform.detail.secondary_winding;
	cout << "������ ��������� ������� --> ";
	cin >> transform.detail.conclusions_of_the_primary_winding;
	cout << "������ ��������� ������� --> ";
	cin >> transform.detail.secondary_winding_terminals;
	cout << "������� ���� --> ";
	cin >> transform.detail.gas_relay;

	cout << "����� �������������� --> ";
	cin >> transform.mass;

	cout << "���� ������������:" << endl;
	cout << "���� --> "; cin >> transform.date.d;
	cout << "����� --> "; cin >> transform.date.m;
	cout << "��� --> "; cin >> transform.date.y;

	cin.clear();
	while (!isspace(cin.get()))
		continue;
}
// ����� ��������������
void CoutTransform(TTransform transform)
{
	cout << "�������� ��������������: " << transform.name << endl
		<< "����� ������������:" << transform.firma << endl
		<< "\n������������� ������:" << endl
		<< "�������� ���:" << transform.detail.oil_tank << endl
		<< "��������� �������: " << transform.detail.primary_winding << endl
		<< "��������� �������: " << transform.detail.secondary_winding << endl
		<< "������ ��������� �������: " << transform.detail.conclusions_of_the_primary_winding << endl
		<< "������ ��������� �������: " << transform.detail.secondary_winding_terminals << endl
		<< "������� ���� --> " << transform.detail.gas_relay << endl
		<< "����� ��������������: " << transform.mass << endl
		<< "\n���� ������������:" << endl
		<< "���� --> " << transform.date.d << endl
		<< "����� --> " << transform.date.m << endl
		<< "��� --> " << transform.date.y << endl;
	cout << endl;
}
//** ������ ����� *****************************
long filesize(FILE* f)
{
	long curpos, length;

	curpos = ftell(f);		//���������� ������� ���������
	fseek(f, 0L, SEEK_END);	//���������� �� ����� �����
	length = ftell(f);		//���������� ��������� � ����� �����
	fseek(f, curpos, SEEK_SET);	//���������� �� ������ ���������
	return length;
}
int main()
{
	setlocale(LC_ALL, "rus");
	int N;
	//	cout << "������� ���������� ��������������� ��� ������ � ���� ������ --> ";
	//	cin >> N;
	//	
	//	cin.clear(); //�������� ����� � ����� ��������� ���������������� � 0
	//	while (!isspace(cin.get()))
	//    	continue;            //���������� �� ����������� ��������� �����

	TTransform transform;

	cout << "������ ������ �� ����������" << endl;

	FILE* f, * g; // �������� �������� ����������
	f = fopen("Transform.txt", "a");	// w, r, a, w+, r+, wt, rt, wb, rb 

	//.....
	//fclose(f);

//	cout << "���� ������ � ��������������:"<< endl;
//	
//	for (int i = 0; i < N; i++)
//	{
//		cout << i+1 << " �������������:\n";
//		CinTransform(transform);
//		fwrite(&transform, sizeof(transform), 1, f);
//	}


	//system("cls");

	long n = filesize(f);	//������ ����� Transform.txt
	N = n / sizeof(TTransform); // ���������� ������� � �����
	cout << "������ ����� Transform.txt --> " << n << " ����" << endl
		<< "������ ��������� Transform --> " << sizeof(TTransform) << " ����" << endl
		<< "���������� ������� � ����� --> " << N << endl;



	cout << "\n\n����� ������ � ��������������:\n\n";
	fclose(f);

	TTransform* massiv = NULL;	// 4 byte
	massiv = new TTransform[500000];	// �������� ������������� �������

	f = fopen("Transform.txt", "r");
	//for (int i = 0; i < N; i++)
	int i = 0;
	while (fread(&transform, sizeof(transform), 1, f))	// !eof(f)
	{
		cout << i + 1 << " �������������:\n";
		massiv[i] = transform;
		CoutTransform(massiv[i]);
		i++;
	}
	fclose(f);

	// ����� ������������� � �������� �����
	cout << "\n\n ������ ��������������� � �������� �����:\n\n";
	int k = 0;
	for (int i = 0; i < N; i++)
	{
		if (massiv[i].detail.oil_tank == 1)
		{
			k++;
			cout << k << " ������������� � �������� �����" << endl;
			CoutTransform(massiv[i]);
			cout << "****************************\n";
		}
	}

	// ����� ������������� ��������� � ��������� �����
	char search_firma[22];
	cout << "������� �������� ����� ��� ������ �� ���� ������ --> ";
	cin.getline(search_firma, 20);
	cout << "\n\n ������ ��������������� ��������� � �����: " << search_firma << endl;
	k = 0;
	for (int i = 0; i < N; i++)
	{
		if (strcmp(massiv[i].firma, search_firma) == 0)
		{
			k++;
			cout << k << " ������������� ��������� � �����: " << search_firma << endl;
			CoutTransform(massiv[i]);
			cout << "****************************\n\n";
		}
	}

	delete[] massiv;

	cout << endl;
	system("pause");
	return 0;
}