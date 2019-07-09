/*
 * SimpleForwardList.h
 *
 *  Created on: 19 мая 2019 г.
 *      Author: sveta
 */
#pragma once
#include <iostream>
#include <iterator>
#include <memory>

template<typename T>
struct Node {
private:
	using data_type = T;
public:
	//узел для однонаправленного списка.

	Node(const Node<T> &node) :
		data(node.data), next(node.next) {

	}
	Node(T &&dt) : data(std::forward<T>(dt)) {
		next = nullptr;
	}

	template<typename ...Args>
	Node(Args &&...args) : data(std::forward<Args>(args)...) {
		next = nullptr;
	}

	~Node() = default;

	// Значение в узле.
	T data;
	// Ссылка на следующий элемент.
	Node *next;

};

template<typename T>
struct NodeIterator {
	// итератор по листу.
private:
	using data_type = T;
public:
	using iterator_category = std::forward_iterator_tag;
	using value_type = Node<T>;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type * ;
	using reference = data_type & ;

	NodeIterator(value_type *p) :
		p(p) {

	}

	NodeIterator(const NodeIterator<data_type> & it) :
		p(it.p) {

	}

	bool operator!=(const NodeIterator<data_type> & other) const {
		return p != other.p;
	}

	bool operator==(const NodeIterator<data_type>& other) const {
		return p == other.p;
	}

	reference operator*() {
		return (*p).data;
	}

	NodeIterator<data_type>& operator++() {
		p = p->next;
		return *this;
	}
	NodeIterator<data_type> operator++(int) {
		NodeIterator tmp = *this;
		++(*this);
		return tmp;
	}
	~NodeIterator() = default;
private:
	pointer p;
};

// Однонаправленный список.
template<typename T, typename Allocator = std::allocator<Node<T>>>class SimpleForwardList {
public:
	using value_type = Node<T>;
	using data_type = T;
	using allocator_type = Allocator;
	using size_type = typename Allocator::size_type;
	using const_reference = const data_type&;
	using iterator = NodeIterator<data_type>;
	using const_iterator = NodeIterator<const data_type>;

	SimpleForwardList(const SimpleForwardList& someList)
		: head(someList.head),
		tail(someList.tail),
		_size(someList._size),
		_allocator(someList._allocator) {
	};
	SimpleForwardList(SimpleForwardList&& someList)
		: head(std::move(someList.head)),
		tail(std::move(someList.tail)),
		_size(std::move(someList._size)),
		_allocator(std::move(someList._allocator)) {
		someList.Init();
	}

	SimpleForwardList(const allocator_type &alloc = allocator_type()) : _allocator(alloc) {
		Init();
	}

	template<typename ...Args>
	void push_back(Args &&...args) {
		if (head == nullptr && _size == 0) {
			head = _allocator.allocate(1);
			_allocator.construct(head, std::forward<Args>(args)...);
			tail = head;
		}
		else {
			tail->next = _allocator.allocate(1);
			_allocator.construct(tail->next, std::forward<Args>(args)...);
			tail = tail->next;
		}
		_size++;

	}

	iterator begin() noexcept {
		return iterator(this->head);
	}

	const_iterator cbegin() const noexcept {
		return const_iterator(this->head);
	}
	iterator end()noexcept {
		return iterator(this->tail);
	}
	const_iterator cend() const noexcept {
		return const_iterator(this->tail);
	}

	void pop_head() {
		if (head != nullptr) {
			auto temp = head;
			head = head->next;
			_allocator.destroy(temp);
			_allocator.deallocate(temp, 1);
			_size--;
		}
	}

	void print() {
		for (auto i = this->begin(); i != this->end(); i++) {
			std::cout << *i << std::endl;
		}
		if (this->end() != nullptr) {
			std::cout << *this->end() << std::endl;
		}
	}
	size_type size() {
		return _size;
	}

	~SimpleForwardList() {
		auto current = head;
		while (current != nullptr) {
			pop_head();
			current = head;
		}
	}
private:
	size_type _size;
	Node<T> *head;
	Node<T> *tail;
	allocator_type _allocator;
	void Init() {
		head = nullptr;
		tail = head;
		_size = 0;
	}
};
