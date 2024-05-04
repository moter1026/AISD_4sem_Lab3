#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <memory>
#include <iomanip>
#include <exception>
#include <fstream>

const char* BLACK_TEXT = "\033[30m";
const char* RED_TEXT = "\033[31m";
const char* GREEN_TEXT = "\033[32m";
const char* YELLOW_TEXT = "\033[33m";
const char* BLUE_TEXT = "\033[34m";
const char* LIGHT_BLUE_TEXT = "\033[36m";
const char* GRAY_TEXT = "\033[37m";
const char* RESET_TEXT = "\033[0m";

template<typename T>
int find_in_vector(const std::vector<T>& vec, const T& el) {
    size_t length = vec.size();
    for (int i = 0; i < length; ++i)
    {
        if (vec[i] == el) return i;
    }
    return -1;
}



template<typename Vertex, typename Distance = double>
class Graph {
public:
    struct Color {
        bool _black;
        bool _gray;
        bool _white;
        Color() : _black(false), _gray(false), _white(true) {};
        void next_step() {
            if (this->_white) {
                this->_white = false;
                this->_gray = true;
            }
            else if (this->_gray) {
                this->_gray = false;
                this->_black = true;
            }
        }
    };
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

        //_________________________
        Distance get_distance() const;
        std::shared_ptr<Vertex>& get_from() const;
        std::shared_ptr<Vertex>& get_to() const;
        //_________________________

        bool operator==(const Edge& e) {
            if (*(this->_from) == *(e._from) &&
                *(this->_to) == *(e._to) &&
                this->_distance == e._distance)
            {
                return true;
            }
            return false;
        }
        friend std::ostream& operator<<(std::ostream& stream, Edge& e) {
            stream << "from: " << *(e._from) << ", " <<
                "to: " << *(e._to) << " with distance: " << e._distance;
            return stream;
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
    std::vector<Edge> edges(const Vertex& vertex) const
    {
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
    return this->edges(v).size();
}

//поиск кратчайшего пути
template<typename Vertex, typename Distance>
std::vector<typename  Graph<Vertex, Distance>::Edge>
Graph<Vertex, Distance>::shortest_path(const Vertex& from, const Vertex& to) const
{
//    //Объявляем необходимые переменные и делаем необходимые проверки
    size_t count_vertex = this->_vertices.size();
    if (count_vertex < 1) throw std::runtime_error("Слишком мало вершин в графе!");

    std::vector<std::vector<std::unique_ptr<Distance>>> alg_table(count_vertex);
    for (size_t i = 0; i < count_vertex; ++i) {
        for (size_t j = 0; j < count_vertex; ++j) {
            alg_table[i].push_back(std::make_unique<Distance>()); // Создаем и добавляем уникальный указатель
        }
    }
    std::vector<Distance> min_len;
    std::vector<Vertex> fixed;
    Distance shortest_length;

    //Заполняем самую первую строку nullptr, кроме эл-та from
    std::cout << GREEN_TEXT << "Алгоритм Дейкстры:\n" << RESET_TEXT;
    for (size_t i = 0; i < count_vertex; ++i)
    {
        if (this->_vertices[i] == from)
        {
            alg_table[0][i] = std::make_unique<Distance>(Distance(0));
            std::cout << std::setw(5) << *(alg_table[0][i]);
        }
        else
        {
            alg_table[0][i] = nullptr;
            std::cout << std::setw(5) << "-";
        }

    }
    std::cout << std::endl;


    //Основная часть выполнения алгоритма
    bool first_row = true;
    for (size_t index = 0; index < count_vertex; ++index)
    {
        Vertex now_min_vertex;
        //first_el нужна для запоминания первого эл-та, который не был обработан,
        //чтобы в дальнейшем искать МИНИМАЛЬНЫЙ доступный в строке
        bool first_el = true;
        Distance now_min = (first_row)? 0 : min_len.back();
        for (size_t i = 0; i < count_vertex; ++i)
        {
            if (!first_row &&
                (alg_table[index][i] == nullptr ||
                -1 != find_in_vector(fixed, this->_vertices[i]) ))
            {
                continue;
            }
            else if (first_el)
            {
                now_min = *(alg_table[index][i]);
                now_min_vertex = this->_vertices[i];
                first_el = false;
            }
            else if(alg_table[index][i] != nullptr &&
                now_min > *(alg_table[index][i]))
            {
                now_min = *(alg_table[index][i]);
                now_min_vertex = this->_vertices[i];
            }
        }
        first_row = false;
        min_len.push_back(now_min);
        fixed.push_back(now_min_vertex);
        if (now_min_vertex == to)
            shortest_length = now_min;

        //Получаем все дуги, выходящие из нашей вершины,
        //и создаём вектор с конечными вершинами
        auto edges = this->edges(now_min_vertex);
        int length_edges = edges.size();
        std::vector<Vertex> to_vertices;
        for (size_t i = 0; i < length_edges; ++i)
        {
            to_vertices.push_back( *(edges[i]._to) );
        }

        //Если дошли до последней строки, то необходимо выйти из цикла,
        //чтобы не выйти за пределы разрешённой памяти
        if (index == count_vertex - 1)
            break;
        //Дальше заполняем следующую строку по алгоритму Дейкстры
        for (size_t i = 0; i < count_vertex; ++i)
        {
            //Если вершина не была фиксирована и нынешняя зафиксированная вершина
            //имеет ребро в итерируемый эл-нт, то либо меняем значение в таблице,
            //либо оставляем прежнее
            if (-1 != find_in_vector(to_vertices, this->_vertices[i]) &&
                -1 == find_in_vector(fixed, this->_vertices[i]))
            {
                int ind = find_in_vector(to_vertices, this->_vertices[i]);
                if (alg_table[index][i] == nullptr)
                {
                    alg_table[index + 1][i] = std::make_unique<Distance>(min_len.back() + edges[ind]._distance);
                }
                else if (*(alg_table[index][i]) > (min_len.back() + edges[ind]._distance))
                {
                    alg_table[index + 1][i] = std::make_unique<Distance>(min_len.back() + edges[ind]._distance);
                }
                else
                {
                    Distance el = *(alg_table[index][i]);
                    alg_table[index + 1][i] = std::make_unique<Distance>(el);
                }
                std::cout << std::setw(5) << *(alg_table[index + 1][i]);
            }
            //Если вершина была фиксирована или нынешняя зафиксированная вершина
            //НЕ имеет ребро до итерируемого эл-нта, то оставляем прошлое значение
            else
            {
                if (alg_table[index][i] == nullptr ||
                    -1 != find_in_vector(fixed, this->_vertices[i]))
                    alg_table[index + 1][i] = nullptr;
                else
                    alg_table[index + 1][i] = std::make_unique<Distance>(*(alg_table[index][i]));
                //___
                if (alg_table[index + 1][i] == nullptr)
                    std::cout << std::setw(5) << "-";
                else
                    std::cout << std::setw(5) << *(alg_table[index + 1][i]);

            }
        }
        std::cout << std::endl;
    }

    std::vector<Graph<Vertex, Distance>::Edge> result;
    int index_in_fixed = find_in_vector(fixed, to);
    std::vector<Graph<Vertex, Distance>::Edge> all_edges = this->all_edges();
    size_t count_all_edges = all_edges.size();
    int index = index_in_fixed;
    while (index > 0)
    {
        //Находим вершины, из которых выходят рёбра в итерируемый элемент
        //и запоминаем их в to_el
        Distance now_len = min_len[index];
        std::vector<Graph<Vertex, Distance>::Edge> to_el;
        std::vector<Distance> min_distance_to_el;

        for (size_t i = 0; i < count_all_edges; ++i)
        {
            if (*(all_edges[i]._to) == fixed[index])
                to_el.push_back(all_edges[i]);
        }
        size_t count_edges_to_el = to_el.size();

        //Находим минимальные пути до найденных ранее элементов
        for (size_t i = 0; i < count_edges_to_el; ++i)
        {
            int index_el = find_in_vector(this->_vertices, *(to_el[i]._from));
            Distance min = now_len;
            for (size_t j = 0; j < count_vertex; ++j)
            {
                if (alg_table[j][index_el] != nullptr &&
                    *(alg_table[j][index_el]) < min)
                    min = *(alg_table[j][index_el]);
            }
            min_distance_to_el.push_back(min);
        }

        //Проверяем из какого эл-та могли прийти в наш эл-нт
        for (size_t i = 0; i < count_edges_to_el; ++i)
        {
            Distance distance = to_el[i]._distance;
            
            if (now_len - distance == min_distance_to_el[i])
            {
                result.push_back(to_el[i]);
                index = find_in_vector(fixed, *(to_el[i]._from));
                break;
            }
            else
            {
                throw std::runtime_error("Нет кратчайшего пути :-(");
            }
        }
        
    }

    return result;
}

//обход
template<typename Vertex, typename Distance>
std::vector<Vertex> Graph<Vertex, Distance>::walk(const Vertex& start_vertex) const
{
    //Инициализация
    int count_vertecies = this->_vertices.size();
    std::vector<std::shared_ptr<Graph::Color>> colors;
    std::vector<std::shared_ptr<Vertex>> parents;
    std::vector<int> lenghts;
    for (size_t i = 0; i < count_vertecies; ++i)
    {
        Graph::Color color_white;
        colors.push_back(std::make_shared<Graph::Color>(color_white));

        parents.push_back(std::make_shared<Vertex>());
        lenghts.push_back(-1);
    }

    std::vector<Vertex> result;

    //Процедура обхода
    int start_index = find_in_vector(this->_vertices, start_vertex);
    std::queue<Vertex> queue;
    queue.push(start_vertex);
    (*(colors[start_index])).next_step();
    parents[start_index] = nullptr;
    lenghts[start_index] = 0;

    while (!queue.empty())
    {
        Vertex& now_el = queue.front();
        int now_index = find_in_vector(this->_vertices, now_el);
        std::vector<Graph<Vertex, Distance>::Edge> edges = this->edges(now_el);
        std::vector<Vertex> to_from_now_el;
        for (auto el_edges : edges) {
            Vertex& el = *(el_edges._to);

            int index_vert = find_in_vector(this->_vertices, el);
            if ((*(colors[index_vert]))._white == true)
            {
                (*(colors[index_vert])).next_step();
                parents[index_vert] = std::make_shared<Vertex>(now_el);
                lenghts[index_vert] = lenghts[now_index] + 1;
                queue.push(el);
            }
        }
        (*(colors[now_index])).next_step();
        queue.pop();
        result.push_back(now_el);
    }

    return result;
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

