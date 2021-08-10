#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class Vector
{
public:

	Vector()
	{

	}

	~Vector()
	{
		// vector 객체 최종 소멸시
		if (_data)
			delete[] _data;
	}

	void push_back(const T& value)
	{
		// 넣어주기전에 다 차있는지 확인 size와 capacity로
		if (_size == _capacity)
		{
			// 증설작업
			// capacity를 늘려주고
			int newCapacity = static_cast<int>(_capacity * 1.5);
			// _capacity가 0혹은 1일 때를 대비. 증가가 안될때
			if (newCapacity == _capacity) 
			{
				newCapacity++;
			}
			// 새로운 vector 만들어주고 => 새로운 기능이기 때문에 함수로 따로 뺀 것
			reserve(newCapacity);
		}

		// 데이터 저장
		_data[_size] = value;

		// 데이터 개수 증가
		_size++;
	}

	// 메모리 증설 역할을 하는 함수
	void reserve(int capacity)
	{
		// 현재 capacity가 요청받은 것보다 클 경우
		if (_capacity >= capacity)
			return;
			
		// 요청받은 걸로 메모리 증설(동적 배열로 만들면 된다)
		_capacity = capacity;
		T* newData = new T[_capacity];
		// 데이터 복사
		for (int i = 0; i < _size; i++)
		{
			newData[i] = _data[i];
		}

		// null 체크하고 기존에 있던 값 날려주기
		if (_data)
			delete[] _data;

		// 최종적으로 데이터 교체
		_data = newData;
	}

	T& operator[](const int pos) { return _data[pos]; }

	int size() { return _size; }
	int capacity() { return _capacity; }

	void clear()
	{
		// vector안에 들어오는 자료형이 사용자 정의 자료형이면 자료형에 맞게 소멸자를 호출해 줘야한다.
		// 일단은 기존의 값을 다 날리고 새롭게 동적 배열을 할당하는 구조로 했다. 원래는 할당자를 이용해서 만든다고 한다
		if (_data)
		{
			delete[] _data;
			_data = new T[_capacity];
		}

		_size = 0;
	}

private:
	T*		_data =		nullptr; // 이게 원래 있던 data 값
	int		_size =		0;
	int		_capacity = 0;
};


int main()
{
	Vector<int> v;
	// 처음부터 사용할 메모리의 개수를 알고 있다면 reserve 함수를 통해 
	// 메모리를 예약해서 사용할 수 있다. 내부적으로 복사가 일어나는 횟수를 줄이는 것
	v.reserve(100);
	for (int i = 0; i < 100; i++)
	{
		v.push_back(i);
		cout << v.size() << " " << v.capacity() << endl;
	}
	v.clear();
	cout << v.size() << " " << v.capacity() << endl;


#pragma region 원래 vector
	vector<int> v;

	for (int i = 0; i < 100; i++)
	{
		v.push_back(i);
		cout << v.size() << " " << v.capacity() << endl;
	}
	// size는 실제 벡터에 들어가 있는 값을 의미 
	// capacity는 예약된(할당된) 총 공간을 의미 => 동적배열은 실제 사용하는 공간보다 50% 크게 공간을 할당해준다.
	// 한 번 늘어난 capacity는 clear로 줄이지 못한다.
	v.clear();
	cout << v.size() << " " << v.capacity() << endl;
#pragma endregion

	return 0;
}