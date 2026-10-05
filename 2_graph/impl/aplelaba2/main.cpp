#include <iostream>

using namespace std;

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

        void RemoveNode(int from, int target) {
        Edge* current = begList[from];
        Edge* prev = nullptr;

        while (current != nullptr && current->dest != target) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            return;
        }

        if (prev == nullptr) {
            begList[from] = current->next;
        }
        else {
            prev->next = current->next;
        }

        delete current;
    }


public:
    Graph(int n){
        numVersh = n;

        begList = new Edge* [n+1];
        for (int i = 1; i<= n; i++){
            begList[i] = nullptr;
        }
    }



    virtual ~Graph() {
        for (int i = 1; i <= numVersh; i++) {
            Edge* current = begList[i];

            while (current != nullptr) {
                Edge* nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }

        delete[] begList;
    }


    void Print() {
        for (int i = 1; i <= numVersh; i++) {
            cout << "Vertex " << i << ": ";
            Edge* current = begList[i];
            while (current != nullptr) {
                cout << "-> " << current->dest << " (weight " << current->weight << ") ";
                current = current->next;
            }
            cout << endl;
        }
    }

    virtual void AddEdge(int src, int dest, int weight = 1) = 0;
    virtual void RemoveEdge(int src, int dest) = 0;
    virtual void AddVertex() = 0;
    virtual void RemoveVertex(int v) = 0;
};

class UndirectedGraph : public Graph {
public:
    UndirectedGraph(int n) : Graph(n) {}

    void AddEdge(int src, int dest, int weight = 1) override {
        if (src < 1 || src > numVersh || dest < 1 || dest > numVersh) {
            cout << "Wrong vertex number" << endl;
            return;
        }

        Edge* newEdge1 = new Edge(dest, weight);
        newEdge1->next = begList[src];
        begList[src] = newEdge1;

        Edge* newEdge2 = new Edge(src, weight);
        newEdge2->next = begList[dest];
        begList[dest] = newEdge2;
    }

    void RemoveEdge(int src, int dest) override{
        if (src < 1 || src > numVersh || dest < 1 || dest > numVersh) {
            cout << "Wrong vertex number" << endl;
            return;
        }
        RemoveNode(src, dest);
        RemoveNode(dest, src);
    }

    void AddVertex() override{
            numVersh++;

            Edge** newList = new Edge*[numVersh + 1];

            for (int i = 1; i < numVersh; i++) {
                newList[i] = begList[i];
            }

            newList[numVersh] = nullptr;

            delete[] begList;

            begList = newList;
        }

    void RemoveVertex(int v) override {
        if (v < 1 || v > numVersh) {
            cout << "Wrong vertex number" << endl;
            return;
        }

        Edge* current = begList[v];
        while (current != nullptr) {
            Edge* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        begList[v] = nullptr;

        for (int i = 1; i <= numVersh; i++) {
            if (i != v) {
                RemoveNode(i, v);
            }
        }

        for (int i = 1; i <= numVersh; i++) {
            Edge* temp = begList[i];
            while (temp != nullptr) {
                if (temp->dest > v) {
                    temp->dest--;
                }
                temp = temp->next;
            }
        }

        numVersh--;
        Edge** newList = new Edge*[numVersh + 1];

        for (int i = 1, j = 1; i <= numVersh + 1; i++) {
            if (i == v) continue;
            newList[j] = begList[i];
            j++;
        }

        delete[] begList;
        begList = newList;
    }

};

class DirectedGraph : public Graph {
public:
    DirectedGraph(int n) : Graph(n) {}

    void AddEdge(int src, int dest, int weight = 1) override {
        if (src < 1 || src > numVersh || dest < 1 || dest > numVersh) {
            cout << "Wrong vertex number" << endl;
            return;
        }

        Edge* newEdge = new Edge(dest, weight);
        newEdge->next = begList[src];
        begList[src] = newEdge;
    }

    void RemoveEdge(int src, int dest) override {
        if (src < 1 || src > numVersh || dest < 1 || dest > numVersh) {
            cout << "Wrong vertex number" << endl;
            return;
        }
        RemoveNode(src, dest);
    }

        void AddVertex() override{
            numVersh++;

            Edge** newList = new Edge*[numVersh + 1];

            for (int i = 1; i < numVersh; i++) {
                newList[i] = begList[i];
            }

            newList[numVersh] = nullptr;

            delete[] begList;

            begList = newList;
        }

    void RemoveVertex(int v) override {
        if (v < 1 || v > numVersh) {
            cout << "Wrong vertex number" << endl;
            return;
        }

        Edge* current = begList[v];
        while (current != nullptr) {
            Edge* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        begList[v] = nullptr;

        for (int i = 1; i <= numVersh; i++) {
            if (i != v) {
                RemoveNode(i, v);
            }
        }

        for (int i = 1; i <= numVersh; i++) {
            Edge* temp = begList[i];
            while (temp != nullptr) {
                if (temp->dest > v) {
                    temp->dest--;
                }
                temp = temp->next;
            }
        }

        numVersh--;
        Edge** newList = new Edge*[numVersh + 1];

        for (int i = 1, j = 1; i <= numVersh + 1; i++) {
            if (i == v) continue;
            newList[j] = begList[i];
            j++;
        }

        delete[] begList;
        begList = newList;
    }
};

int main() {
    DirectedGraph drg(4);
    cout << "--- Graph without edges ---" << endl;
    drg.Print();
    drg.AddEdge(1, 2);
    drg.AddEdge(1, 3);
    drg.AddEdge(2, 4);
    cout << "--- Directed graph after adding edges ---" << endl;
    drg.Print();

    UndirectedGraph g(4);
    g.AddEdge(1, 2);
    g.AddEdge(1, 3, 5);
    g.AddEdge(2, 4);

    cout << "--- Graph after adding edges ---" << endl;
    g.Print();

    cout << "\n--- Deleting edge between 1 and 2 ---" << endl;
    g.RemoveEdge(1, 2);
    g.Print();

    cout << "\n--- Adding a new vertex and then adding a new edge between 5 and 1 ---" << endl;
    g.AddVertex();
    g.AddEdge(5, 1);
    g.Print();

    cout << "\n--- Deleting Vertex 5 ---" << endl;
    g.RemoveVertex(5);
    g.Print();

    return 0;
}
