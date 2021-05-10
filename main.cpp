// main.cpp: определяет точку входа для приложения.
//

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <type_traits>

#include "tuple_utils.h"

using namespace std;

/**
*	Вывод IP адреса из целого числа
*/
template<typename T>
typename enable_if_t<is_integral_v<T>>
print_ip(T ip)
{
	int size = sizeof(ip);

	for (int i = 0; i < size; ++i)
	{
		unsigned u = (ip >> (8 * (size - 1 - i))) & 0xFF;

		if (i) cout << ".";
		cout << (unsigned)u;
	}

	cout << endl;
}

/**
*	Вывод IP адреса из контейнера vector или list
*	Проверка на наличие в типе Т функции emplace, в обоих контейнерах она есть
*/
template<typename T>
typename enable_if_t<is_member_function_pointer_v<decltype(&T::emplace<>)>>
print_ip(T ip)
{
	for (auto p = ip.cbegin(); p != ip.cend(); ++p)
	{
		if (p != ip.cbegin()) cout << ".";
		cout << *p;
	}

	cout << endl;
}

/**
*	Вывод IP адреса из объекта string
*/
template<typename T>
typename enable_if_t<is_same_v<T, string>>
print_ip(T ip)
{
	cout << ip << endl;
}

/**
*	Callback для tupleForeach
*/
template <typename T>
struct ForeachCallback
{
	template<size_t index, typename U>
	void operator()(U&& element)
	{
		using first_type = typename tuple_element<0, T>::type;
		using current_type = typename remove_cv<typename remove_reference<U>::type>::type;

		static_assert(is_same_v<first_type, current_type>, "Objects with different types in the tuple");

		if (index) cout << ".";
		std::cout << element;
	}
};

/**
*	Вывод IP адреса из кортежа
*/
template<typename T, typename=tuple_element<0, T>::type>
void print_ip(T ip)
{
	tuple_utils::tupleForeach(ForeachCallback<T>(), ip);

	cout << endl;
}

int main()
{
	print_ip(char{ -1 }); // 255 
	print_ip(short{ 0 }); // 0.0 
	print_ip(int{ 2130706433 }); // 127.0.0.1 
	print_ip(long long{ 8875824491850138409 }); // 123.45.67.89.101.112.131.41 
	print_ip(string{ "Hello, World!" }); // Hello, World! 
	print_ip(vector<int>{100, 200, 300, 400}); // 100.200.300.400 
	print_ip(list<short>{400, 300, 200, 100}); // 400.300.200.100 
	print_ip(make_tuple(123, 456, 789, 0));  // 123.456.789.0
}
