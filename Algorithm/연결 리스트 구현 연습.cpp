#include <iostream>
#include <vector>
#include <list>
using namespace std;

// vector
// - push_back : O(1)
// - push_front : O(N) ==> ��ȿ���� ���� ���� ����

// ����Ʈ���� �߰� ����/������ �����ٴ� ���� ���Ǻ������� �´� ���̴�.
// iterator�� ���� ����� �ּҿ� ���� ������ �ִ� ��쿡�� ���������� �׷��� ���� ��쿡�� �� Ȥ�� �ڿ������� ã�Ƶ��� �Ѵ�.

// ��� ����� �ڷᱸ��
template<typename T>
class Node
{
public:
	Node() :
			_prev(nullptr)
		,	_next(nullptr)
		,	_data(T())
	{

	}

	Node(const T& value) :
			_prev(nullptr)
		,	_next(nullptr)
		,	_data(value)
	{

	}

public:
	Node*	_prev; 
	Node*	_next;  
	T		_data;  
	/*
	* �� ������ �������̱� ������ ������ ��
	* �����ʹ� (ũ�Ⱑ ������ - �ּҸ� ����)�ϴ� �ڷ���
	* �̹� 4byte or 8byte�� ũ�Ⱑ �����Ǿ� �����ϱ� �̷������� ������ ��
	* Node* �ؼ�: * ���� ������ �Դϴ�. ���� �ּҸ� ������ �־��. �ּҸ� ���󰡸� �ڷ����� Node�� ���� ���Ϳ�. �̷� �ǹ�.
	* https://twinparadox.tistory.com/439 ���⿡ ���������� 2���� �迭 ������ ������.
	*/
};

// iterator ���� -> iterator�� ������ ������ �ϴ� ��ü�̱� ������ ������ ���� iteraotr�� ����ִ�
// ��带 ������� �̷����� ������ �ϴ� ���̴�.
template<typename T>
class Iterator
{
public:
	Iterator() : _node(nullptr)
	{

	}

	Iterator(Node<T>* node) : _node(node)
	{

	}

	// ++it
	Iterator& operator++()
	{
		_node = _node->_next;
		return *this;
	}

	// it++
	Iterator operator++(int)
	{
		Iterator<T> temp = *this;
		_node = _node->_next;
		return temp;
	}

	// --it
	Iterator& operator--()
	{
		_node = _node->_prev;
		return *this;
	}

	// it--
	Iterator operator--(int)
	{
		Iterator<T> temp = *this;
		_node = _node->_prev;
		return temp;
	}

	// *it  -> ���ͷ����Ͱ� ��� �ִ� ������ ��ü
	T& operator*()
	{
		return _node->_data;
	}

	bool operator==(const Iterator& other)
	{
		return _node == other._node;
	}

	bool operator!=(const Iterator& other)
	{
		return _node != other._node;
	}

public:
	Node<T>* _node;
};


// ���� ��带 ������ �Ʒ� List�� ����� ����
template<typename T>
class List
{
public:
	// _head�� _tail�� nullptr check�� �������Ƿ� ���� ���� �ؼ� _head�� _tail�� � �ּҶ� ������ �ְ� ���ش�.
	List() : _size(0)
	{
		// [head] <-> ... [tail]
		_head = new Node<T>();
		_tail = new Node<T>();
		_head->_next = _tail;
		_tail->_prev = _head;
	}

	~List()
	{
		while (_size > 0)
			pop_back();

		delete _head;
		delete _tail;
	}

	void push_back(const T& value)
	{
		// tail ������� value�� �־���� �� ��
		AddNode(_tail, value);
	}

	void pop_back()
	{
		// ������ ������ ��带 ����
		RemoveNode(_tail->_prev);
	}

private:
	// ��带 �о� ���� �� �ִ� ���� �Լ��� ���´�. ������ ���(before ���) ������ ���ο� ��带 ���� ���� �߰��� ��
	// [head] <-> [1] <-> [prevNode] <-> [before] <-> [tail]  -> ��� �ֱ� ��
	// [head] <-> [1] <-> [prevNode] <-> [newNode] <-> [before] <-> [tail] -> ��� ���� ��
	Node<T>* AddNode(Node<T>* before, const T& value)
	{
		Node<T>* newNode = new Node<T>(value);
		Node<T>* prevNode = before->_prev;

		prevNode->_next = newNode;
		newNode->_prev = prevNode;


		newNode->_next = before;
		before->_prev = newNode;

		_size++;

		return newNode;
	}

	// [head] <-> [prevNode] <-> [node] <-> [nextNode] <-> [tail]  -> ��� ���� ��
	// [head] <-> [prevNode] <-> [nextNode] <-> [tail] -> ��� �� ��
	// �� �Լ����� ���� ������ ��尡 node. ������ ��尡 node�� ��
	Node<T>* RemoveNode(Node<T>* node)
	{
		Node<T>* prevNode = node->_prev; // �����ͷ� ���� ����� �ּҸ� ������ �ְ� �ϴ±���
		Node<T>* nextNode = node->_next;

		prevNode->_next = nextNode;
		nextNode->_prev = prevNode;

		delete node;

		_size--;

		return nextNode;
	}

	int size() { return _size; }

public:
	using iterator = Iterator<T>; // using �̶� typedef�� ������ ���
	
	iterator begin() { return iterator(_head->_next); }
	iterator end() { return iterator(_tail); }

	// it '�տ�' �߰�
	iterator insert(iterator it, const T& value) 
	{
		Node<T>* node = AddNode(it._node, value);
		return iterator(node); // ����� �ּҸ� ������ �ִ� ��ü�� ��ȯ���ش�.
	}

	iterator erase(iterator it)
	{
		Node<T>* node = RemoveNode(it._node);
		return iterator(node);
	}


private:
	// ���� ���� �� ��忡 ���� ����(�ּ�)�� ������ �ִ� �����Ͱ� �ʿ��ϴ�
	Node<T>*	_head;
	Node<T>*	_tail;
	int			_size;
};


int main()
{


#pragma region STL list ����
	//list<int> li;

	//list<int>::iterator eraseit;

	//for (int i = 0; i < 10; i++)
	//{
	//	if (i == 5)
	//	{
	//		// insert�� ���� iterator�� ���� �ְ� ���� ��� �ٷ� ������ ����Ű�� �־���Ѵ�.
	//		// insert�� ���� �����͸� �߰��� ����� iterator�� ��ȯ�Ѵ�.
	//		// insert �̿��ؼ� �߰� ����
	//		eraseit = li.insert(li.end(), i);
	//	}
	//	else
	//	{
	//		li.push_back(i);
	//		// li.push_front();
	//		// li[3] �������� ���� �� ��
	//	}
	//}

	//li.pop_back(); // �ڿ��� ���� ��
	//li.erase(eraseit); // iterator �̿��ؼ� �߰� ����

	//// list�� ���� ������ �ȵǱ� ������ iterator(�ݺ���, ������ ������ �ϴ� ��ü)�� �̿��ؼ� �����Ѵ�.
	//for (list<int>::iterator it = li.begin(); it != li.end(); it++)
	//{
	//	cout << (*it) << endl;
	//}
#pragma endregion

	// ���� ���� ��
	List<int> li;
	
	List<int>::iterator eraseit;
	
	for (int i = 0; i < 10; i++)
	{
		if (i == 5)
		{

			eraseit = li.insert(li.end(), i);
		}
		else
		{
			li.push_back(i);
			// li.push_front();
			// li[3] �������� ���� �� ��
		}
	}

	li.pop_back(); // �ڿ��� ���� ��
	li.erase(eraseit); // iterator �̿��ؼ� �߰� ����

	// list�� ���� ������ �ȵǱ� ������ iterator(�ݺ���, ������ ������ �ϴ� ��ü)�� �̿��ؼ� �����Ѵ�.
	for (List<int>::iterator it = li.begin(); it != li.end(); it++)
	{
		cout << (*it) << endl;
	}


	return 0;
}