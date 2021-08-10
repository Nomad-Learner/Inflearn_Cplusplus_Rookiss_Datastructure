#include <iostream>
#include <stack>
using namespace std;

#pragma region Stack
/*

- Stack (LIFO 후입선출)

[1][2][3][4] << 밀어넣음

되돌리기 (Ctrl + z) 기능 구현

*/
#pragma endregion

int main()
{
#pragma region STL stack 사용법
	stack<int> s;

	//삽입
	s.push(1);
	s.push(2);
	s.push(3);

	while (s.empty() == false)
	{
		// 최상위 원소 확인 => 스택에서 실질적으로 꺼낸 것은 아니다
		int data = s.top();
		// 최상위 원소 삭제 => 실질적으로 삭제한 부분
		s.pop();
		cout << data << endl;
	}
	// 스택에 들어가 있는 데이터 개수
	int size = s.size();

#pragma endregion


	return 0;
}