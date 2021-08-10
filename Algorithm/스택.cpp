#include <iostream>
#include <stack>
using namespace std;

#pragma region Stack
/*

- Stack (LIFO ���Լ���)

[1][2][3][4] << �о����

�ǵ����� (Ctrl + z) ��� ����

*/
#pragma endregion

int main()
{
#pragma region STL stack ����
	stack<int> s;

	//����
	s.push(1);
	s.push(2);
	s.push(3);

	while (s.empty() == false)
	{
		// �ֻ��� ���� Ȯ�� => ���ÿ��� ���������� ���� ���� �ƴϴ�
		int data = s.top();
		// �ֻ��� ���� ���� => ���������� ������ �κ�
		s.pop();
		cout << data << endl;
	}
	// ���ÿ� �� �ִ� ������ ����
	int size = s.size();

#pragma endregion


	return 0;
}