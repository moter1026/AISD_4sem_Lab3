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

		//получение всех ребер, выходящих из вершины
		std::cout << "\n";
		std::cout << BLUE_TEXT << "получение всех ребер, выходящих из вершин:\n" << RESET_TEXT;
		std::cout << GRAY_TEXT;
		for (size_t i = 0; i < Graph_1.vertices().size(); ++i)
		{
			auto edges = Graph_1.edges(Graph_1.vertex(i));
			size_t degree = Graph_1.degree(Graph_1.vertex(i));
			std::cout << "\tВершина " << Graph_1.vertex(i) << " со степенью " <<
				degree << " : ";
			for (size_t j = 0; j < degree; ++j)
			{
				std::cout << edges[j] << "; ";
			}
			std::cout << "\n";
		}
		std::cout << RESET_TEXT;


		//Проверка алгоритма Дейкстры
		Graph<int> Graph_2;
		int b[] = { 1,2,3,4,5,6,7,8 };
		Graph_2.add_vertex(b[0]);
		Graph_2.add_vertex(b[1]);
		Graph_2.add_vertex(b[2]);
		Graph_2.add_vertex(b[3]);
		Graph_2.add_vertex(b[4]);
		Graph_2.add_vertex(b[5]);
		Graph_2.add_vertex(b[6]);
		Graph_2.add_vertex(b[7]);

		Graph_2.add_edge(b[0], b[1], 2);
		Graph_2.add_edge(b[0], b[2], 5);
		Graph_2.add_edge(b[0], b[5], 3);
		Graph_2.add_edge(b[0], b[6], 6);
		Graph_2.add_edge(b[1], b[2], 4);
		Graph_2.add_edge(b[2], b[3], 3);
		Graph_2.add_edge(b[3], b[1], 4);
		Graph_2.add_edge(b[3], b[4], 3);
		Graph_2.add_edge(b[4], b[0], 7);
		Graph_2.add_edge(b[4], b[5], 5);
		Graph_2.add_edge(b[5], b[3], 8);
		Graph_2.add_edge(b[6], b[2], 6);
		Graph_2.add_edge(b[6], b[4], 7);
		Graph_2.add_edge(b[6], b[5], 4);
		Graph_2.add_edge(b[3], b[7], 1);

		auto shortest_path = Graph_2.shortest_path(b[0], b[4]);
		int size = shortest_path.size();
		std::cout << GREEN_TEXT;
		for (size_t i = 0; i < size; ++i)
		{
			std::cout << shortest_path[i] << "\n";
		}
		std::cout << RESET_TEXT;

		Graph_2.print();

		//Проверка обхода
		std::vector<int> walk = Graph_2.walk(b[0]);
		std::cout << "\n" << GREEN_TEXT << "Обход графа: " << RESET_TEXT;
		for (auto el : walk) {
			std::cout << " -> " << el;
		}
		std::cout << "\n";

		int* best_point = Graph_1.find_stock();
		if (best_point)
		{
			std::cout << "\n" << GREEN_TEXT << "Лучшая точка для склада для графа Graph_1: " <<
				*best_point << "\n" << RESET_TEXT;
		}
		else {
			std::cout << "\n" << YELLOW_TEXT << "Нет лучшей точки графа Graph_1: \n" << RESET_TEXT;
		}



		best_point = Graph_2.find_stock();
		if (best_point)
		{
			std::cout << "\n" << GREEN_TEXT << "Лучшая точка для склада для графа Graph_2: " <<
				*best_point << RESET_TEXT;
		}
		else {
			std::cout << "\n" << YELLOW_TEXT << "Нет лучшей точки графа Graph_2: " << RESET_TEXT;
		}
		

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
