#ifndef PRINT_IP_H
#define PRINT_IP_H

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
typename enable_if<is_integral<T>::value>::type
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
*/
template<typename T>
typename enable_if<is_same<T, vector<typename T::value_type>>::value || is_same<T, list<typename T::value_type>>::value>::type
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
typename enable_if<is_same<T, string>::value>::type
print_ip(T ip)
{
	cout << ip << endl;
}

/**
*	Callback для tuple_utils::tupleForeach
*/
template <typename T>
struct ForeachCallback
{
	using first_type = typename tuple_element<0, T>::type;

	template<typename U>
	void operator()(U&& element, const size_t index)
	{
		using current_type = typename remove_cv<typename remove_reference<U>::type>::type;

		static_assert(is_same<first_type, current_type>::value, "Objects with different types in the tuple");

		if (index) cout << ".";
		std::cout << element;
	}
};

/**
*	Вывод IP адреса из кортежа
*/
template<typename T, typename = typename tuple_element<0, T>::type>
void print_ip(T ip)
{
	ForeachCallback<T> cb;
	tuple_utils::tupleForeach(cb, ip);

	cout << endl;
}

#endif