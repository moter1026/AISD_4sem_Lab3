// 4_sem_Lab2.cpp: определяет точку входа для приложения.
//
#pragma once

#include <iostream>
#include "libraries/4_sem_Lab3_lib.h"

int main() {
	setlocale(LC_ALL, "Russian");

	std::cout << "hello world!\n";

	Graph<int> Graph_1;
	int a[] = {1,2,3,4};


	Graph_1.add_vertex(a[0]);
	Graph_1.add_vertex(a[1]);
	Graph_1.add_vertex(a[2]);
	Graph_1.add_vertex(a[3]);

	Graph_1.print();

	return 0;
}
