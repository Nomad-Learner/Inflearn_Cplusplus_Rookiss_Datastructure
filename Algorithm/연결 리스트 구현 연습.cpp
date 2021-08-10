#include <iostream>
#include <vector>
#include <list>
using namespace std;

// vector
// - push_back : O(1)
// - push_front : O(N) ==> 비효율적 따라서 제공 안함

// 리스트에서 중간 삽입/삭제가 빠르다는 말은 조건부적으로 맞는 말이다.
// iterator를 통해 노드의 주소에 대한 정보가 있는 경우에는 빠르겠지만 그렇지 않은 경우에은 앞 혹은 뒤에서부터 찾아들어가야 한다.

// 노드 기반의 자료구조
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
	* 이 구조가 포인터이기 때문에 가능한 것
	* 포인터는 (크기가 고정된 - 주소를 저장)하는 자료형
	* 이미 4byte or 8byte로 크기가 고정되어 있으니까 이런식으로 가능한 것
	* Node* 해석: * 나는 포인터 입니다. 나는 주소를 가지고 있어요. 주소를 따라가면 자료형이 Node인 것이 나와요. 이런 의미.
	* https://twinparadox.tistory.com/439 여기에 이중포인터 2차원 배열 설명이 괜찮다.
	*/
};

// iterator 구현 -> iterator는 포인터 역할을 하는 객체이기 때문에 구현할 때도 iteraotr가 들고있는
// 노드를 기반으로 이런저런 연산을 하는 것이다.
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

	// *it  -> 이터레이터가 들고 있는 데이터 자체
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


// 위에 노드를 가지고 아래 List를 만드는 구조
template<typename T>
class List
{
public:
	// _head와 _tail의 nullptr check가 귀찮으므로 더미 노드라 해서 _head와 _tail이 어떤 주소라도 가지고 있게 해준다.
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
		// tail 노드전에 value를 넣어줘라 이 뜻
		AddNode(_tail, value);
	}

	void pop_back()
	{
		// 실제로 삭제할 노드를 지정
		RemoveNode(_tail->_prev);
	}

private:
	// 노드를 밀어 넣을 수 있는 공통 함수를 적는다. 지정한 노드(before 노드) 이전에 새로운 노드를 만들어서 값을 추가할 것
	// [head] <-> [1] <-> [prevNode] <-> [before] <-> [tail]  -> 노드 넣기 전
	// [head] <-> [1] <-> [prevNode] <-> [newNode] <-> [before] <-> [tail] -> 노드 넣은 후
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

	// [head] <-> [prevNode] <-> [node] <-> [nextNode] <-> [tail]  -> 노드 빼기 전
	// [head] <-> [prevNode] <-> [nextNode] <-> [tail] -> 노드 뺀 후
	// 이 함수에서 내가 지정한 노드가 node. 삭제할 노드가 node인 것
	Node<T>* RemoveNode(Node<T>* node)
	{
		Node<T>* prevNode = node->_prev; // 포인터로 만들어서 노드의 주소를 가지고 있게 하는구나
		Node<T>* nextNode = node->_next;

		prevNode->_next = nextNode;
		nextNode->_prev = prevNode;

		delete node;

		_size--;

		return nextNode;
	}

	int size() { return _size; }

public:
	using iterator = Iterator<T>; // using 이랑 typedef랑 유사한 기능
	
	iterator begin() { return iterator(_head->_next); }
	iterator end() { return iterator(_tail); }

	// it '앞에' 추가
	iterator insert(iterator it, const T& value) 
	{
		Node<T>* node = AddNode(it._node, value);
		return iterator(node); // 노드의 주소를 가지고 있는 객체를 반환해준다.
	}

	iterator erase(iterator it)
	{
		Node<T>* node = RemoveNode(it._node);
		return iterator(node);
	}


private:
	// 시작 노드와 끝 노드에 대한 정보(주소)를 가지고 있는 포인터가 필요하다
	Node<T>*	_head;
	Node<T>*	_tail;
	int			_size;
};


int main()
{


#pragma region STL list 내용
	//list<int> li;

	//list<int>::iterator eraseit;

	//for (int i = 0; i < 10; i++)
	//{
	//	if (i == 5)
	//	{
	//		// insert에 들어가는 iterator는 내가 넣고 싶은 장소 바로 다음을 가리키고 있어야한다.
	//		// insert는 내가 데이터를 추가한 장소의 iterator를 반환한다.
	//		// insert 이용해서 중간 삽입
	//		eraseit = li.insert(li.end(), i);
	//	}
	//	else
	//	{
	//		li.push_back(i);
	//		// li.push_front();
	//		// li[3] 임의접근 지원 안 함
	//	}
	//}

	//li.pop_back(); // 뒤에서 빼는 것
	//li.erase(eraseit); // iterator 이용해서 중간 삭제

	//// list는 임의 접근이 안되기 때문에 iterator(반복자, 포인터 역할을 하는 객체)를 이용해서 접근한다.
	//for (list<int>::iterator it = li.begin(); it != li.end(); it++)
	//{
	//	cout << (*it) << endl;
	//}
#pragma endregion

	// 내가 만든 것
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
			// li[3] 임의접근 지원 안 함
		}
	}

	li.pop_back(); // 뒤에서 빼는 것
	li.erase(eraseit); // iterator 이용해서 중간 삭제

	// list는 임의 접근이 안되기 때문에 iterator(반복자, 포인터 역할을 하는 객체)를 이용해서 접근한다.
	for (List<int>::iterator it = li.begin(); it != li.end(); it++)
	{
		cout << (*it) << endl;
	}


	return 0;
}