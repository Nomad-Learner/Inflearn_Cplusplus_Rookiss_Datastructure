#include <iostream>
using namespace std;


class K
{

};


int main()
{

	int a[5]; // �Ϲ����� �迭 �����ϴ� ���

	int** ptr = nullptr;
	
	ptr = new int* [5];

	for (int i = 0; i < 5; i++)
	{
		ptr[i] = new int[5];
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			ptr[i][j] = i * 10;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << ptr[i][j]<< " ";
		}
		cout << endl;
	}
	cout << "Dfafa" << endl;
	return 0;
}

