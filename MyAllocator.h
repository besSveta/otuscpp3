/*
 * MyAllocator.h

 *
 *  Created on: 19 мая 2019 г.
 *      Author: sveta
 */
#pragma once
#include <iostream>
#include <memory>
template<typename T, int I>
struct logging_allocator {
	using value_type = T;
	using pointer = T *;
	using const_pointer = const T*;
	using reference = T &;
	using const_reference = const T&;
	using size_type= std::size_t;
	int counter = 0;
	T* allocated = NULL;

	template<typename U>
	struct rebind {
		using other = logging_allocator<U, I>;
	};

	T *allocate(std::size_t n) {
		if (counter >= I) {
			std::cout
					<< "The size of the array can not be > " + std::to_string(I)
					<< std::endl;
			throw std::bad_alloc();
		}
		std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
		//std::cout << __FUNCSIG__ << "[n = " << n << "]" << std::endl;
		counter = counter + 1;
		if (counter == 1) {
			if (I > 1 && n == 1)
				n = n * I;
			auto p = std::malloc(n * sizeof(T));
			if (!p)
				throw std::bad_alloc();
			allocated = reinterpret_cast<T *>(p);
			return allocated;
		}
		return allocated + (counter - 1);

	}

	void deallocate(T *p, std::size_t n) {
		std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
		//std::cout << __FUNCSIG__ << "[n = " << n << "]" << std::endl;
		if (I > 1) {
			if (counter == 1) {
				std::free(allocated);
				allocated = NULL;
			} else {
				counter--;
			}
		} else
			std::free(p);
	}

	template<typename U, typename ...Args>
	void construct(U *p, Args &&...args) {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		//std::cout << __FUNCSIG__ << std::endl;
		new (p) U(std::forward<Args>(args)...);
	}
	;

	void destroy(T *p) {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		//std::cout << __FUNCSIG__ << std::endl;
		p->~T();
	}

};
