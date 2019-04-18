#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <tuple>

#define N 100

class Matrix{
    int** graph;
    std::vector<char> nodes;
    std::vector<int> way;
    bool* is_visited;
    int** flows;
    char source;
    char stock;
    unsigned size;
    std::vector<std::tuple<char, char, int>> edges;
public:
    Matrix(): way(N, 0){
        char from , to;
        int number, cost;
        std::cin >> number >> source >> stock;
        for (unsigned i = 0; i < number; i++){
            std::cin >> from >> to >> cost;
            if (std::find(nodes.begin(), nodes.end(), from) == nodes.end())
                nodes.push_back(from);
            if (std::find(nodes.begin(), nodes.end(), to) == nodes.end())
                nodes.push_back(to);
            edges.push_back(std::make_tuple(from, to, cost));
        }
       size = nodes.size();
       create_graph(edges);
    }


    void create_graph(std::vector<std::tuple<char, char, int>> edges){
        int cost;
        std::vector<char>::iterator it;
        char from, to;
        is_visited = new bool[size];
        graph = new int*[size];
        flows = new int*[size];
        for (int i = 0; i < size; i++){
            way[i] = -1;
            is_visited[i] = false;
            graph[i] = new int[size];
            flows[i] = new int[size];
            for (int j = 0; j < size; j++) {
                graph[i][j] = 0;
                 flows[i][j] = 0;
            }
        }
        for(auto i : edges){
            std::tie(from, to, cost) = i;
            it = std::find(nodes.begin(), nodes.end(), from);
            int index_from = it - nodes.begin();
            it = std::find(nodes.begin(), nodes.end(), to);
            int index_to = it - nodes.begin();
            graph[index_from][index_to] = cost;
        }
    }

    int find_index(char node){
        std::vector<char>::iterator it;
        it = std::find(nodes.begin(), nodes.end(), node);
        return it - nodes.begin();
    }

    void DFS(char node) {
        is_visited[find_index(node)] = true;
        for (int i = 0; i<size; i++)
            if (!is_visited[i] && 
			   (graph[find_index(node)][i] - flows[find_index(node)][i] > 0 && 
				graph[find_index(node)][i] != 0 || 
				flows[find_index(node)][i] < 0 && 
				graph[i][find_index(node)] != 0)) {
                way[i] = find_index(node);
                DFS(nodes[i]);
            }
    }


    bool get_way() {
            DFS(source);
            for (size_t i = 0; i < size; i++) {
                is_visited[i] = false;
            }
            return (way[find_index(stock)] != -1);
    }

    int FF() {
        int max_flow = 0;
        while (get_way()) {
            int tmp = INT_MAX;
            for (int v = find_index(stock); way[v] >= 0; v = way[v])
                 tmp = std::min(tmp, graph[way[v]][v] - flows[way[v]][v]);
            for (int v = find_index(stock); way[v] >= 0; v = way[v]) {
                flows[way[v]][v] += tmp;
                flows[v][way[v]] -= tmp;
            }
            max_flow += tmp;
            for (int i = 0; i<size; i++)
                way[i] = -1;
        }
        return max_flow;
    }

    void print(){
        std::sort(edges.begin(), edges.end());
        for(auto i : edges){
            int it1 = find_index(std::get<0>(i));
            int it2 = find_index(std::get<1>(i));
            if(flows[it1][it2] < 0)
                flows[it1][it2] = 0;
            std::cout << nodes[it1] << ' ' << nodes[it2] << ' ' << flows[it1][it2] << std::endl;
        }
    }

    ~Matrix(){
        for (int i = 0; i < size; i++){
            delete [] graph[i];
            delete [] flows[i];
        }
        delete [] graph;
        delete [] flows;
        delete [] is_visited;
    }


};


int main(){

    Matrix A;
    std::cout << A.FF() << std::endl;
    A.print();
    return 0;
}
