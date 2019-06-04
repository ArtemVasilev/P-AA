#include <iostream>
#include <climits>
#include <cstring>
#include <queue>
#include <map>

#define N 'z'

using List = std:: map <char, std:: map <char, int>>;

class Graph {

private:
    char way[N];         //массив предков (родителей вершин)
    List Given_graph;          //список смежности заданного графа
    List RealFlow;             //список смежности фактического графа
    std:: array <bool, N> check; //насыщенность

    int Residualweight(char from, char to) { //остаточный поток (разница между заданным и фактическим)
        return (Given_graph[from][to] - RealFlow[from][to]);
    }

    bool Bfs(char source, char sink) {     //поиск в ширину
        check.fill (false);                //заполняем контейнер значениями false - не просмотрены
        check[source] = true;              //сток помечаем, как посещённую вершину
        way[source] = -1;              //у истока нет родителей
        std:: queue <char> queue;          //объявили очередь вершин
        queue.push(source);
        while (!queue.empty()) {           //пока есть вершины в очереди
            char from = queue.front();     //рассматриваем первую вершину очереди
            for (char to = 0; to < N; to++) {                        //проходим по соседним вершинам
                if (!check[to] && Residualweight(from, to) > 0) {  //вершина должна быть не просмотрена,а поток не насыщен
                    queue.push(to);
                    check[to] = true;
                    way[to] = from;
                    if (to == sink) {
                        queue.pop();
                        return (true);
                    }
                }
            }
            queue.pop(); 	                   //удаление первого элемента из очереди
        }
        return (false);
    }

public:

    void AddEdge(char from, char to, int weight) {  //функция заполения списка смежности графа
        Given_graph[from][to] = weight;
        RealFlow[to][from]= 0;
    }

    int Ford_Fulkerson(char source, char sink) {                       //алгорит Форда-Фалкерсона
        int maxFlow = 0;                                               //значение максимального потока
        while (Bfs(source, sink)) {                                    //пока существует путь от истока к стоку
            int minFlow = INT_MAX;                                     //изначально минимальному потоку присваиваем значение максимального int
            char to = sink;
            for(int i = sink; 0 <= way[i]; i = way[i])	       //идём по найденому пути
                minFlow = std:: min(minFlow, Residualweight(way[i], i));
            for(int i = sink; 0 <= way[i]; i = way[i]) {
                RealFlow[way[i]][i] += minFlow;
                RealFlow[i][way[i]] -= minFlow;
            }
            maxFlow += minFlow;
            memset(way, -1, N * sizeof(char));
            check.fill (false);
        }
        return (maxFlow);
    }

    void Print() {
        for (char i = 0; i < N; i++)
            for (char j = 0; j < N; j++)
                if (Given_graph[i][j])
                    std:: cout << char(i) << " " << char(j) << " " << std:: max(RealFlow[i][j], 0) << std:: endl;
    }
};

int main() {
    int count, weight;
    char source, sink, from, to;
    std:: cin >> count >> source >> sink;
    Graph graph;
    for (int i = 0; i < count; i++) {
        std:: cin >> from >> to >> weight;
        graph.AddEdge(from, to, weight);
    }
    std:: cout << graph.Ford_Fulkerson(source, sink) << std::endl;
    graph.Print();
    return 0;
}
