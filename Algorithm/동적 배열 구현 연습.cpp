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
		// vector ��ü ���� �Ҹ��
		if (_data)
			delete[] _data;
	}

	void push_back(const T& value)
	{
		// �־��ֱ����� �� ���ִ��� Ȯ�� size�� capacity��
		if (_size == _capacity)
		{
			// �����۾�
			// capacity�� �÷��ְ�
			int newCapacity = static_cast<int>(_capacity * 1.5);
			// _capacity�� 0Ȥ�� 1�� ���� ���. ������ �ȵɶ�
			if (newCapacity == _capacity) 
			{
				newCapacity++;
			}
			// ���ο� vector ������ְ� => ���ο� ����̱� ������ �Լ��� ���� �� ��
			reserve(newCapacity);
		}

		// ������ ����
		_data[_size] = value;

		// ������ ���� ����
		_size++;
	}

	// �޸� ���� ������ �ϴ� �Լ�
	void reserve(int capacity)
	{
		// ���� capacity�� ��û���� �ͺ��� Ŭ ���
		if (_capacity >= capacity)
			return;
			
		// ��û���� �ɷ� �޸� ����(���� �迭�� ����� �ȴ�)
		_capacity = capacity;
		T* newData = new T[_capacity];
		// ������ ����
		for (int i = 0; i < _size; i++)
		{
			newData[i] = _data[i];
		}

		// null üũ�ϰ� ������ �ִ� �� �����ֱ�
		if (_data)
			delete[] _data;

		// ���������� ������ ��ü
		_data = newData;
	}

	T& operator[](const int pos) { return _data[pos]; }

	int size() { return _size; }
	int capacity() { return _capacity; }

	void clear()
	{
		// vector�ȿ� ������ �ڷ����� ����� ���� �ڷ����̸� �ڷ����� �°� �Ҹ��ڸ� ȣ���� ����Ѵ�.
		// �ϴ��� ������ ���� �� ������ ���Ӱ� ���� �迭�� �Ҵ��ϴ� ������ �ߴ�. ������ �Ҵ��ڸ� �̿��ؼ� ����ٰ� �Ѵ�
		if (_data)
		{
			delete[] _data;
			_data = new T[_capacity];
		}

		_size = 0;
	}

private:
	T*		_data =		nullptr; // �̰� ���� �ִ� data ��
	int		_size =		0;
	int		_capacity = 0;
};


int main()
{
	Vector<int> v;
	// ó������ ����� �޸��� ������ �˰� �ִٸ� reserve �Լ��� ���� 
	// �޸𸮸� �����ؼ� ����� �� �ִ�. ���������� ���簡 �Ͼ�� Ƚ���� ���̴� ��
	v.reserve(100);
	for (int i = 0; i < 100; i++)
	{
		v.push_back(i);
		cout << v.size() << " " << v.capacity() << endl;
	}
	v.clear();
	cout << v.size() << " " << v.capacity() << endl;


#pragma region ���� vector
	vector<int> v;

	for (int i = 0; i < 100; i++)
	{
		v.push_back(i);
		cout << v.size() << " " << v.capacity() << endl;
	}
	// size�� ���� ���Ϳ� �� �ִ� ���� �ǹ� 
	// capacity�� �����(�Ҵ��) �� ������ �ǹ� => �����迭�� ���� ����ϴ� �������� 50% ũ�� ������ �Ҵ����ش�.
	// �� �� �þ capacity�� clear�� ������ ���Ѵ�.
	v.clear();
	cout << v.size() << " " << v.capacity() << endl;
#pragma endregion

	return 0;
}