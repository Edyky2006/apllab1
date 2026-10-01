#include <iostream>

struct Edge{
    int dest;
    int weight;
    Edge* next;

    Edge(int d, int w = 1){
        dest = d;
        weight = w;
        next = nullptr;
    }
};

class Graph{
protected:
    int numVersh;
    Edge** begList;

public:
    Graph(int n){
        numVersh = n;

        begList = new Edge* [n+1];
        for (int i = 1; i<= n; i++){
            begList[i] = nullptr;
        }
    }

    virtual ~Graph(){}

    virtual void AddEdge(int src, int dest, int weight = 1) = 0;
    virtual void RemoveEdge(int src, int dest) = 0;
    virtual void AddVertex() = 0;
    virtual void RemoveVertex(int v) = 0;
};
