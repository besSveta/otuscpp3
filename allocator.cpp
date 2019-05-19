// allocator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include "MyForwardList.h"
#include "MyAllocator.h"

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
	auto map2 = std::map<int, int, std::less<int>,logging_allocator<std::pair<const int, int>, n>> { };

	// вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
	for (size_t i = 0; i < n; ++i) {
		map2[i] = map1[i];
		std::cout << i<<" "<<map2[i]<< std::endl;
	}


	// создание экземпляра своего контейнера для хранения int
	MyForwardList<int> list;

	// заполнение 10 элементами от 0 до 9
	for (auto i = 0; i < n; i++) {
		list.push_back(i);
	}
	// создание экземпляра своего контейнера для хранения int с новым	аллокатором ограниченным 10 элементами
	MyForwardList<int,logging_allocator<MyNode<int>, n>> list2;
	// заполнение 10 элементами от 0 до 9
	for (auto i = 0; i < n; i++) {
			list2.push_back(i);
		}
	// вывод на экран всех значений хранящихся в контейнере
	std::cout<<"new container"<<std::endl;
	list2.print();
	return 0;
}
