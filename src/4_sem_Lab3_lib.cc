//#pragma once
//
//#include "../libraries/4_sem_Lab3_lib.h"
//
//
//// Class Graph::Edge_______________
//template<typename Vertex, typename Distance>
//std::shared_ptr<Vertex>& Graph<Vertex, Distance>::Edge::get_from() const
//{
//    return this->_from;
//}
//
//template<typename Vertex, typename Distance>
//std::shared_ptr<Vertex>& Graph<Vertex, Distance>::Edge::get_to() const
//{
//    return this->_to;
//}
//
//template<typename Vertex, typename Distance>
//Distance Graph<Vertex, Distance>::Edge::get_distance() const
//{
//    return this->_distance;
//}
//
//
//// Class Graph_______________
//    //проверка-добавление-удаление вершин
//template<typename Vertex, typename Distance>
//bool Graph<Vertex, Distance>::has_vertex(const Vertex& v) const
//{
//    for (size_t i = 0; i < this->_vertices.size(); ++i)
//    {
//        if (v == this->_vertices[i]) return true;
//    }
//    return false;
//}
//
//template<typename Vertex, typename Distance>
//void Graph<Vertex, Distance>::add_vertex(const Vertex& v)
//{
//    if (this->has_vertex(v)) throw std::runtime_error("данна€ вершина уже существует!");
//    this->_vertices.push_back(v);
//}
//
//template<typename Vertex, typename Distance>
//bool Graph<Vertex, Distance>::remove_vertex(const Vertex& v)
//{
//    for (size_t i = 0; i < this->_vertices.size(); ++i)
//    {
//        if (v == this->_vertices[i]) 
//        {
//            this->_vertices.erase(this->_vertices.begin() + i);
//            return true;
//        }
//    }
//    return false;
//}
//
//template<typename Vertex, typename Distance>
//const std::vector<Vertex>& Graph<Vertex, Distance>::vertices() const
//{
//    return this->_vertices;
//}
//
//
//    //проверка-добавление-удаление ребер
//template<typename Vertex, typename Distance>
//void Graph<Vertex, Distance>::add_edge(const Vertex& from, const Vertex& to, const Distance& d)
//{
//}
//
//template<typename Vertex, typename Distance>
//bool Graph<Vertex, Distance>::remove_edge(const Vertex& from, const Vertex& to)
//{
//    return false;
//}
//
//template<typename Vertex, typename Distance>
//bool Graph<Vertex, Distance>::remove_edge(const Edge& e)
//{
//    return false;
//}
//
//template<typename Vertex, typename Distance>
//int Graph<Vertex, Distance>::has_edge(const Vertex& from, const Vertex& to) const
//{
//    size_t count_edges = this->_edges.size();
//
//    for (size_t i = 0; i < count_edges; ++i)
//    {
//        if (from == *(this->_edges[i]._from) &&
//            to == *(this->_edges[i]._to))
//        {
//            return i;
//        }
//    }
//    return -1;
//}
//
//template<typename Vertex, typename Distance>
//bool Graph<Vertex, Distance>::has_edge(const Edge& e)
//{
//    return false;
//}
//
//
//
//template<typename Vertex, typename Distance>
//size_t Graph<Vertex, Distance>::order() const //пор€док 
//{
//    return size_t();
//}
//
//template<typename Vertex, typename Distance>
//size_t Graph<Vertex, Distance>::degree(const Vertex& v) const //степень вершины
//{
//    return size_t();
//}
//
////поиск кратчайшего пути
//template<typename Vertex, typename Distance>
//std::vector<typename  Graph<Vertex, Distance>::Edge>
//    Graph<Vertex, Distance>::shortest_path(const Vertex& from, const Vertex& to) const
//{
//    return std::vector<Edge>();
//}
//
////обход
//template<typename Vertex, typename Distance>
//std::vector<Vertex> Graph<Vertex, Distance>::walk(const Vertex& start_vertex) const
//{
//    return std::vector<Vertex>();
//}
//
//template<typename Vertex, typename Distance>
//void Graph<Vertex, Distance>::print() const
//{
//    size_t count_vertex = this->_vertices.size();
//    size_t count_edges = this->_edges.size();
//
//    //«аголовочна€ строка со всеми вершинами графа
//    std::cout << LIGHT_BLUE_TEXT << std::setw(5) << " ";
//    for (size_t i = 0; i < count_vertex; ++i)
//    {
//        std::cout << std::setw(5) << std::left << this->_vertices[i];
//    }
//    std::cout << RESET_TEXT << std::endl;
//
//    for (size_t i = 0; i < count_vertex; ++i)
//    {
//        const Vertex& now_vertex = this->_vertices[i];
//
//        //¬ывод в левой колонке вершины, из которой выход€т рЄбра
//        std::cout << LIGHT_BLUE_TEXT << std::setw(10) <<
//            std::left << now_vertex << RESET_TEXT;
//
//        for (size_t j = 0; j < count_vertex; j++)
//        {
//            int index_edge = this->has_edge(now_vertex, this->_vertices[j]);
//            if (0 <= index_edge)
//            {
//                std::cout << std::setw(5) << this->_edges[index_edge];
//            }
//            else
//            {
//                std::cout << std::setw(5) << "-";
//            }
//        }
//        std::cout << std::endl;
//    }
//}