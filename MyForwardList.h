/*
 * MyForwardList.h
 *
 *  Created on: 19 мая 2019 г.
 *      Author: sveta
 */
#pragma once
#include <iostream>
#include <iterator>
#include <memory>

template<typename T>
struct MyNode {
//узел
	MyNode(const T &t) :
			data(t), next(nullptr) {

	}

	MyNode(const MyNode<T> &node) :
			data(node.data), next(node.next) {

	}
	~MyNode() = default;

	MyNode *next;
	T data;
};

template<typename T>
struct MyNodeIterator {
// итератор по листу.
private:
	using data_type = T;
public:
	using iterator_category = std::forward_iterator_tag;
	using value_type = MyNode<T>;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type *;
	using reference = data_type &;

	MyNodeIterator(value_type *p) :
			p(p) {

	}

	MyNodeIterator(const MyNodeIterator<data_type> & it) :
			p(it.p) {

	}

	bool operator!=(const MyNodeIterator<data_type> & other) const {
		return p != other.p;
	}

	bool operator==(const MyNodeIterator<data_type>& other) const {
		return p == other.p;
	}

	reference operator*() {
		return (*p).data;
	}

	MyNodeIterator<data_type>& operator++() {
		p = p->next;
		return *this;
	}
	MyNodeIterator<data_type> operator++(int) {
		MyNodeIterator tmp = *this;
		++(*this);
		return tmp;
	}
	~MyNodeIterator() = default;
private:
	pointer p;

};

template<typename T, typename Allocator = std::allocator<MyNode<T>>>

struct MyForwardList {
	using value_type = MyNode<T>;
	using data_type = T;
	using allocator_type = Allocator;
	using size_type= typename Allocator::size_type;
	using const_reference = const data_type&;
	using iterator =MyNodeIterator<data_type>;
	using const_iterator = MyNodeIterator<const data_type>;

	MyNode<T> *head;
	MyNode<T> *tail;

	MyForwardList(const MyForwardList&) = delete;
	MyForwardList(MyForwardList&& someList)
	: head(std::move(someList.head)),
	tail(std::move(someList.tail)),
	_size(std::move(someList._size)),
	_allocator(std::move(someList._allocator)) {
		someList.Init();
	}

	MyForwardList(const allocator_type &alloc = allocator_type()) :_allocator(alloc) {
		Init();
	}

	void push_back(const data_type& value) {
		insert();
		tail->data = value;
		tail->next = nullptr;
		_size++;

	}

	void push_back(data_type&& value) noexcept {
		insert();
		tail->data = std::move(value);
		tail->next = nullptr;
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
		if (head!=nullptr) {
			auto temp=head;
			head=head->next;
			_allocator.deallocate(temp,1);
			_size--;
		}
	}

	void print() {
		for (auto i=this->begin(); i!= this->end(); i++) {
			std::cout<<*i<<std::endl;
		}
		if (this->end()!=nullptr){
			std::cout<<*this->end()<<std::endl;
		}
	}
	size_type size() {
		return _size;
	}

	~MyForwardList() {
		auto current=head;
		while(current!=nullptr) {
			pop_head();
			current=head;
		}
	}
private:
	size_type _size;
	allocator_type _allocator;
	void Init() {
		head = nullptr;
		tail = head;
		_size=0;
	}

	void insert() {
		if (head==nullptr && _size==0) {
			head = _allocator.allocate(1);
			tail=head;
		}
		else {
			tail->next = _allocator.allocate(1);
			tail = tail->next;
		}

	}

};
