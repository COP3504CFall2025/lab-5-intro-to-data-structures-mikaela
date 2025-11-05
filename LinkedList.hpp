#pragma once
#include <iostream>
using namespace std;



template <typename T>
class LinkedList {
	struct Node {
		T data = 0;
		Node* prev = nullptr;
		Node* next = nullptr;
		explicit Node(const T& data){
			this->data = data;
		}
	};
public:
	// Behaviors
	void printForward() const {
		Node* current = head;
		while (current != nullptr) {
			std::cout << current->data << " ";
			current = current->next;
		}
	}
	void printReverse() const {
		Node* current = tail;
		while (current != head) {
			std::cout << current->data << " ";
			current = current->prev;
		}
		std::cout << current->data << std::endl;
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return count;
	}

	Node* getHead() {
		return head;
	}
	const Node* getHead() const {
		return head;
	}
	Node* getTail() {
		return tail;
	}
	const Node* getTail() const {
		return tail;
	}

	// Insertion
	void AddHead(const T& data) {
		Node* newHead = new Node(data);
		newHead->next = head;
		if (head != nullptr) {
			head->prev = newHead;
		}else {
			tail = newHead;
		}
		head = newHead;
		count++;
	}
	void AddTail(const T& data) {
		Node* newTail = new Node(data);
		newTail->prev = tail;
		if (tail != nullptr) {
			tail->next = newTail;
		}
		else {
			head = newTail;
		}
		tail = newTail;
		count++;
	}

	// Removal
	bool RemoveHead() {
		if (head == nullptr) {
			return false;
		}
		if (head == tail) {
			delete head;
			head = nullptr;
			tail = nullptr;
			count--;
			return true;
		}
		Node* temp = head;
		head = head->next;
		head->prev = nullptr;

		delete temp;
		count--;
		return true;
	}
	bool RemoveTail() {
		if (tail == nullptr) {
			return false;
		}
		Node* tempTail = tail;
		tail = tail->prev;

		if (tail != nullptr) {
			tail->next = nullptr;
		}else {
			head = nullptr;
		}
		delete tempTail;
		count--;
		return true;
	}
	void Clear() {
		while (head != nullptr) {
			RemoveHead();
		}
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	// Operators

	//move assignment
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (this == &other) {
			return *this;
		}
		//make sure that the place we are transferring to is empty with no data leaked
		Clear();

		//now transfer and set to empty
		head = other.head;
		other.head = nullptr;
		tail = other.tail;
		other.tail = nullptr;
		count = other.count;
		other.count = 0;
		return *this;

	}
	//copy assignment THIS IS WRONG
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this == &rhs) {
			return *this;
		}
		Clear();
		for (Node* node = rhs.head; node != nullptr; node = node->next) {
			addTail(node->data);
		}
		return *this;
	}


	// Construction/Destruction
	LinkedList() {
		head = nullptr;
		tail = nullptr;
		count = 0;
	}
	//copy constructor
	LinkedList(const LinkedList<T>& list){
		head = nullptr;
		tail = nullptr;
		count = 0;
		for (Node* node = list.head; node != nullptr; node = node->next) {
			addTail(node->data);
		}
	}

	//move constructor
	LinkedList(LinkedList<T>&& other) noexcept {
		count = other.count;
		head = other.head;
		tail = other.tail;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}

	//destructor
	~LinkedList() {
		Clear();
	}

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};


