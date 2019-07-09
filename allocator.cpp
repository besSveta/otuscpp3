// allocator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <map>
#include <forward_list>
#include "SimpleForwardList.h"
#include "ListAllocator.h"
#define _ 0
struct hard {
	std::string str_val;
	hard(const char * ch, size_t sz) {
		str_val = std::string(ch, sz);
	};
	hard(const hard &) = delete;
};
int main(int, char *[]) {
	// создание экземпляра std::map<int, int>
	const int n = 10;
	auto map1 = std::map<int, int>{};
	auto factorial = 1;

	// заполнение 10 элементами, где ключ это число от 0 до 9, а значение -	 факториал ключа
	map1[0] = factorial;
	for (size_t i = 1; i < n; ++i) {
		factorial = factorial * i;
		map1[i] = factorial;
	}

	// создание экземпляра std::map<int, int> с новым аллокатором ограниченным 10 элементами
	auto map2 = std::map<int, int, std::less<int>, logging_allocator<std::pair<const int, int>, n>>{ };

	// вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
	for (size_t i = 0; i < n; ++i) {
		map2[i]=map1[i];
		std::cout << i << " " << map2[i] << std::endl;
	}


	// создание экземпляра своего контейнера для хранения int
	SimpleForwardList<int> list;

	// заполнение 10 элементами от 0 до 9
	for (auto i = 0; i < n; i++) {
		list.push_back(7);
	}

	// создание экземпляра своего контейнера для хранения int с новым	аллокатором ограниченным 10 элементами
	SimpleForwardList<int, logging_allocator<Node<int>, n>> list2;
	// заполнение 10 элементами от 0 до 9
	for (auto i = 0; i < n; i++) {
		list2.push_back(i);
	}
	// вывод на экран всех значений хранящихся в контейнере
	std::cout << "forward check" << std::endl;
	list2.print();


	// создание экземпляра своего контейнера для хранения hard
	SimpleForwardList<hard, logging_allocator<Node<hard>, n> >list3;
	list3.push_back("one", 1);

	// вывод на экран всех значений хранящихся в контейнере
	std::cout << "new container" << std::endl;
	for (auto i = list3.begin(); i != list3.end(); i++) {
		std::cout << (*i).str_val << std::endl;
	}
	if (list3.end() != nullptr) {
		std::cout << (*list3.end()).str_val << std::endl;
	}
	return 0;
}
