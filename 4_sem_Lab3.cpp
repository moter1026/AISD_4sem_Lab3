// 4_sem_Lab2.cpp: определяет точку входа для приложения.
//
#pragma once

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <array>
#include <random>
#include "libraries/4_sem_Lab3_lib.h"



int main() {
	try
	{
		setlocale(LC_ALL, "Russian");
		std::random_device rd;   
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(1, 10);
		

		//Функция для проверки на утечку памяти
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		Graph<int> Graph_1;
		std::array<int, 10> a = { 1,2,3,4,5,6,7,8,9,10 };

		//Заполняю граф значениями из массива
		for (auto& element : a)
		{
			Graph_1.add_vertex(element);
		}

		//Заполняю граф рандомными рёбрами
		for (size_t i = 0; i < 30; i++)
		{
			int index_1 = 0, index_2 = 0;
			while (true)
			{
				index_1 = dist(gen) - 1;
				index_2 = dist(gen) - 1;
				if (-2 == Graph_1.has_edge(a[index_1], a[index_2]) ||
					0 <= Graph_1.has_edge(a[index_1], a[index_2]))
					continue;
				else break;
			}
			Graph_1.add_edge(a[index_1], a[index_2], dist(gen) * dist(gen));
		}
		Graph_1.print();
		//Удаляю рандомные вершины
		for (size_t i = 10; i > 6; --i)
		{
			dist = std::uniform_int_distribution<>(1, i);
			int index_1 = dist(gen) - 1;
			Graph_1.remove_vertex(a[index_1]);
		}
		Graph_1.print();

		//Удаляю рандомное ребро
		std::cout << "Удаляю рёбра 1-м методом. Рез-ты: ";
		for(size_t i = 0; i < 5; ++i)
		{
			dist = std::uniform_int_distribution<>(1, Graph_1.vertices().size());
			
			int index_1 = dist(gen) - 1;
			int index_2 = dist(gen) - 1;
			std::cout << Graph_1.remove_edge(Graph_1.vertex(index_1),
				Graph_1.vertex(index_2)) << ", ";
		}
		std::cout << "\n";
		std::cout << "Удаляю рёбра 2-м методом. Рез-ты: ";
		for (size_t i = 0; i < 5; ++i)
		{
			dist = std::uniform_int_distribution<>(1, Graph_1.all_edges().size());

			int index_1 = dist(gen) - 1;
			std::cout << Graph_1.remove_edge(Graph_1.edge(index_1)) << ", ";
		}
		std::cout << "\n";
		Graph_1.print();
	}
	catch (const std::exception& e)
	{
		std::cout << std::endl << RED_TEXT <<
			e.what() << RESET_TEXT << std::endl;
	}

	//Вывод информации об утечке памяти во вкладку "Вывод" в VS
	_CrtDumpMemoryLeaks();
	return 0;
}
