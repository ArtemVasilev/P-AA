#include <iostream>
#include <vector>
#include <queue>
#include <ctype.h>

using namespace std;


class Graph
{
    vector<vector<double>> m;
    size_t size;
    char start;
    char finish;
    double weight;
    vector<char> path;

public:
    Graph():m(26, vector<double> (26, 0)), path(26, 0){
        size = 26;
    }
    void Init(){
        char vertex1, vertex2;
        cin>>start>>finish;
        bool t = true;
        while(t){
            if(cin>>vertex1 && isalpha(vertex1)){
                cin>>vertex2>>weight;
                m[vertex1-'a'][vertex2-'a'] = weight;
            }
            else {
                t = false;
            }
        }

    }
    void Greedy(){
        int min = 1000;
        int res = 0;
        path[0] = start;
        while(path[res]!=finish){
            min = 1000;
            res++;
            for (int i = 0;i<size;i++)
                if((min>m[(int)path[res-1]-97][i])
                        && (m[(int)path[res-1]-97][i]!=0)){
                    min = m[(int)path[res-1]-97][i];
                    path[res] = char(i+97);
                }
            if(min == 1000){
                m[(int)path[res-2]-97][(int)path[res-1]-97] = 0;
                res-=2;
            }
            else {
                m[(int)path[res-1] - 97][(int)path[res] - 97] = 0;
            }

        }
        for (int i = 0;i<path.size();i++)
        {
            if(isalpha(path[i]))
                    cout<<path[i];
        }
    }

};

int main()
{
    Graph s;
    s.Init();
    s.Greedy();
    return 0;
}