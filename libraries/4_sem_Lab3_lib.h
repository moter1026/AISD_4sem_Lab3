#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <exception>

const char* BLACK_TEXT = "\033[30m";
const char* RED_TEXT = "\033[31m";
const char* GREEN_TEXT = "\033[32m";
const char* YELLOW_TEXT = "\033[33m";
const char* BLUE_TEXT = "\033[34m";
const char* LIGHT_BLUE_TEXT = "\033[36m";
const char* GRAY_TEXT = "\033[37m";
const char* RESET_TEXT = "\033[0m";



template<typename Vertex, typename Distance = double>
class Graph {
public:
    struct Edge {
        std::shared_ptr<Vertex> _from;
        std::shared_ptr<Vertex> _to;
        Distance _distance;

        Edge() = default;
        Edge(std::shared_ptr<Vertex> from, std::shared_ptr<Vertex> to, Distance distance) {
            if (from == to)
                throw std::runtime_error("Создание замкнутого ребра");
            this->_distance = distance;
            this->_from = from;
            this->_to = to;
        }
        Edge(const Vertex& from, const Vertex& to, Distance distance) {
            if (from == to)
                throw std::runtime_error("Создание замкнутого ребра");
            this->_distance = distance;
            this->_from = std::make_shared<Vertex>(from);
            this->_to = std::make_shared<Vertex>(to);
        }
        ~Edge() = default;

        Distance get_distance() const;
        std::shared_ptr<Vertex>& get_from() const;
        std::shared_ptr<Vertex>& get_to() const;

        bool operator==(const Edge& e) {
            if (*(this->_from) == *(e._from) &&
                *(this->_to) == *(e._to) &&
                this->_distance == e._distance)
            {
                return true;
            }
            return false;
        }
    };
private:
    std::vector<Vertex> _vertices;
    std::vector<Edge> _edges;
public:
    Graph() = default;
    Graph(const Graph<Vertex, Distance>& graph) {
        this->_edges = graph._edges;
        this->_vertices = graph._vertices;
    }
    ~Graph() = default;


    //проверка-добавление-удаление вершин
    int has_vertex(const Vertex& v) const;
    void add_vertex(const Vertex& v);
    bool remove_vertex(const Vertex& v);
    const std::vector<Vertex>& vertices() const;
    const Vertex& vertex(size_t index) const;


    //проверка-добавление-удаление ребер
    void add_edge(const Vertex& from, const Vertex& to,
        const Distance& d);
    bool remove_edge(const Vertex& from, const Vertex& to);
    bool remove_edge(const Edge& e); //c учетом расстояния
    //возвращает индекс ребра в векторе
    int has_edge(const Vertex& from, const Vertex& to) const;
    int has_edge(const Edge& e); //c учетом расстояния в Edge
    const std::vector<Edge>& all_edges() const;
    const Edge& edge(size_t index) const {
        return this->_edges.at(index);
    }

    //получение всех ребер, выходящих из вершины
    std::vector<Edge> edges(const Vertex& vertex) {
        std::vector<Edge> edgesFrom;
        for (size_t i = 0; i < this->_edges.size(); ++i)
        {
            if (*(this->_edges[i]._from.get()) == vertex) {
                edgesFrom.push_back(this->_edges[i]);
            }
        }
        return edgesFrom;
    };

    size_t order() const; //порядок 
    size_t degree(const Vertex& v) const; //степень вершины


    //поиск кратчайшего пути
    std::vector<Edge> shortest_path(const Vertex& from,
        const Vertex& to) const;
    //обход
    std::vector<Vertex>  walk(const Vertex& start_vertex)const;

    void print() const;
};









// Class Graph::Edge_______________
template<typename Vertex, typename Distance>
std::shared_ptr<Vertex>& Graph<Vertex, Distance>::Edge::get_from() const
{
    return this->_from;
}

template<typename Vertex, typename Distance>
std::shared_ptr<Vertex>& Graph<Vertex, Distance>::Edge::get_to() const
{
    return this->_to;
}

template<typename Vertex, typename Distance>
Distance Graph<Vertex, Distance>::Edge::get_distance() const
{
    return this->_distance;
}


// Class Graph_______________
    //проверка-добавление-удаление вершин
template<typename Vertex, typename Distance>
int Graph<Vertex, Distance>::has_vertex(const Vertex& v) const
{
    for (int i = 0; i < this->_vertices.size(); ++i)
    {
        if (v == this->_vertices[i]) return i;
    }
    return -1;
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::add_vertex(const Vertex& v)
{
    if (this->has_vertex(v) >= 0) throw std::runtime_error("данная вершина уже существует!");
    this->_vertices.push_back(v);
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_vertex(const Vertex& v)
{
    for (size_t i = 0; i < this->_edges.size(); i++)
    {
        if (*(this->_edges[i]._from) == v ||
            *(this->_edges[i]._to) == v)
        {
            this->_edges.erase(this->_edges.begin() + i);
            --i;
        }
    }
    size_t count_vertices = this->_vertices.size();
    for (size_t i = 0; i < count_vertices; ++i)
    {
        if (v == this->_vertices[i])
        {
            this->_vertices.erase(this->_vertices.begin() + i);
            return true;
        }
    }
    return false;
}

template<typename Vertex, typename Distance>
const std::vector<Vertex>& Graph<Vertex, Distance>::vertices() const
{
    return this->_vertices;
}

template<typename Vertex, typename Distance> 
const Vertex& Graph<Vertex, Distance>::vertex(size_t index) const
{
    return this->_vertices.at(index);
}


//проверка-добавление-удаление ребер
template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::add_edge(const Vertex& from, const Vertex& to, const Distance& d)
{
    int ind_vertex_from = has_vertex(from);
    int ind_vertex_to = has_vertex(to);

    if (ind_vertex_from != -1 && ind_vertex_to != -1 &&
        (from != to) && this->has_edge(from, to) == -1)
    {
        std::shared_ptr<Graph<Vertex, Distance>::Edge> edge =
            std::make_shared<Graph<Vertex, Distance>::Edge>(
                Graph<Vertex, Distance>::Edge(from, to, d));
        this->_edges.push_back(*edge);
        return;
    }
    else if (this->has_edge(from, to) >= 0) return;
    throw std::runtime_error("Ошибка при создании ребра!");
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_edge(const Vertex& from, const Vertex& to)
{
    int index_edge = this->has_edge(from, to);
    if (index_edge >= 0)
    {
        this->_edges.erase(this->_edges.begin() + index_edge);
        return true;
    }
    return false;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_edge(const Edge& e)
{
    int index_edge = this->has_edge(e);
    if (index_edge >= 0)
    {
        this->_edges.erase(this->_edges.begin() + index_edge);
        return true;
    }
    return false;
}

template<typename Vertex, typename Distance>
int Graph<Vertex, Distance>::has_edge(const Vertex& from, const Vertex& to) const
{
    if (!from || !to) throw std::runtime_error("Переданы несуществющие вершины!");
    if (from == to) return -2;

    size_t count_edges = this->_edges.size();

    for (int i = 0; i < count_edges; ++i)
    {
        if (from == *(this->_edges[i]._from) &&
            to == *(this->_edges[i]._to))
        {
            return i;
        }
    }
    return -1;
}

template<typename Vertex, typename Distance>
int Graph<Vertex, Distance>::has_edge(const Edge& e)
{
    size_t count_edges = this->_edges.size();
    for (size_t i = 0; i < count_edges; i++)
    {
        if (e == this->_edges[i]) 
            return i;
    }
    return -1;
}

template<typename Vertex, typename Distance>
const std::vector<typename  Graph<Vertex, Distance>::Edge>& 
Graph<Vertex, Distance>::all_edges() const 
{
    return this->_edges;
}

template<typename Vertex, typename Distance>
size_t Graph<Vertex, Distance>::order() const //порядок 
{
    return size_t();
}

template<typename Vertex, typename Distance>
size_t Graph<Vertex, Distance>::degree(const Vertex& v) const //степень вершины
{
    return size_t();
}

//поиск кратчайшего пути
template<typename Vertex, typename Distance>
std::vector<typename  Graph<Vertex, Distance>::Edge>
Graph<Vertex, Distance>::shortest_path(const Vertex& from, const Vertex& to) const
{
    return std::vector<Edge>();
}

//обход
template<typename Vertex, typename Distance>
std::vector<Vertex> Graph<Vertex, Distance>::walk(const Vertex& start_vertex) const
{
    return std::vector<Vertex>();
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::print() const
{
    std::cout << YELLOW_TEXT << "Кол-во вершин: " << this->_vertices.size() << std::endl;
    std::cout << "Кол-во рёбер: " << this->_edges.size() << RESET_TEXT << std::endl;
    size_t count_vertex = this->_vertices.size();

    //Заголовочная строка со всеми вершинами графа
    std::cout << LIGHT_BLUE_TEXT << std::setw(10) << " ";
    for (size_t i = 0; i < count_vertex; ++i)
    {
        std::cout << std::setw(5) << std::left << this->_vertices[i];
    }
    std::cout << RESET_TEXT << std::endl;

    for (size_t i = 0; i < count_vertex; ++i)
    {
        const Vertex& now_vertex = this->_vertices[i];

        //Вывод в левой колонке вершины, из которой выходят рёбра
        std::cout << LIGHT_BLUE_TEXT << std::setw(10) <<
            std::left << now_vertex << RESET_TEXT;

        for (size_t j = 0; j < count_vertex; j++)
        {
            int index_edge = this->has_edge(now_vertex, this->_vertices[j]);
            if (0 <= index_edge)
            {
                std::cout << std::setw(5) << this->_edges[index_edge]._distance;
            }
            else
            {
                std::cout << std::setw(5) << "-";
            }
        }
        std::cout << std::endl;
    }
}

