#include <iostream>
#include <chrono>
#include <cstdlib>


using namespace std;

template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    Node(T val){
        data = val;
        prev = nullptr;
        next = nullptr;
    }
};

template <typename T>
struct MyList{
    Node<T>* head;
    Node<T>* tail;

    MyList(){
        head = nullptr;
        tail = nullptr;
    }


    bool Search(T el){
        Node<T>* current = head;
        while(current != nullptr){

            if (current->data == el){
                return true;
            }

            current = current->next;
        }

        return false;
    }



    void Insert (T el){
        if (Search(el) == true){
            return;
        }

        Node<T>* newNode = new Node<T>(el);

        if (head == nullptr){
            head = newNode;
            tail = newNode;
        }

        else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

    }

    void Delete (T el){
        Node<T>* nodeToDelete = head;
        while (nodeToDelete != nullptr && nodeToDelete->data != el){
            nodeToDelete = nodeToDelete->next;
        }

        if (nodeToDelete == nullptr){
            cout << "There's no such element." << endl;
            return;
        }

        if (nodeToDelete == head && nodeToDelete == tail){
            head = nullptr;
            tail = nullptr;
        }

        else if (nodeToDelete == head) {
            head = head->next;
            head->prev = nullptr;
        }

        else if (nodeToDelete == tail){
            tail = tail->prev;
            tail->next = nullptr;
        }

        else {
            nodeToDelete->prev->next=nodeToDelete->next;
            nodeToDelete->next->prev = nodeToDelete->prev;
        }

        delete nodeToDelete;
    }

     void Clear() {
        Node<T>* current = head;

        while (current != nullptr) {
            Node<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }

        head = nullptr;
        tail = nullptr;
    }

    ~MyList() {
        Clear();
    }


    void Print(){
        if (head == nullptr){
            cout << "Hell no" << endl;
            return;
        }

        Node<T>* current = head;
        cout << "{ ";

        while (current != nullptr){
            cout << current->data << " ";
            current = current->next;
        }

        cout << "}" << endl;
    }


    MyList<T> Union(MyList<T>& otherSet) {
        MyList<T> resultSet;

        Node<T>* current = head;
        while (current != nullptr){
            resultSet.Insert(current->data);
            current = current->next;
        }
        Node<T>* currentOther = otherSet.head;
        while (currentOther != nullptr){
            resultSet.Insert(currentOther->data);
            currentOther = currentOther->next;

        }

        return resultSet;
    }

    MyList<T> Intersection(MyList<T>& otherSet){
        MyList<T> resultSet;
        Node<T>* current = head;

        while (current != nullptr){
            if (otherSet.Search(current->data) == true){
                resultSet.Insert(current->data);
                current = current->next;
            }

            else{
                current = current->next;
            }
        }

        return resultSet;
    }

    MyList<T> Difference(MyList<T>& otherSet){
        MyList<T> resultSet;
        Node<T>* current = head;

        while (current != nullptr){
            if (otherSet.Search(current->data) == true){
                current = current->next;
            }

            else{
                resultSet.Insert(current->data);
                current = current->next;
            }
        }

        return resultSet;
    }

    bool IsSubset (MyList<T>& otherSet){
        Node<T>* currentOther = otherSet.head;

        while (currentOther != nullptr){
            if (Search(currentOther->data) == false){
                return false;
            }

            currentOther = currentOther->next;
        }

        return true;
    }

    MyList<T> SymmetricDifference (MyList<T>& otherSet){
        MyList<T> d1 = Difference(otherSet);
        MyList<T> d2 = otherSet.Difference(*this);
        return d1.Union(d2);
    }
};

int main() {
    MyList<int> setA;
    setA.Insert(10);
    setA.Insert(20);
    setA.Insert(30);
    setA.Insert(40);

    MyList<int> setB;
    setB.Insert(30);
    setB.Insert(40);
    setB.Insert(50);
    setB.Insert(60);

    cout << "Set A: "; setA.Print();
    cout << "Set B: "; setB.Print();
    cout << "-----------------------\n";

    cout << "Union (A U B): ";
    MyList<int> u = setA.Union(setB);
    u.Print();

    cout << "Intersection (A & B): ";
    MyList<int> inter = setA.Intersection(setB);
    inter.Print();

    cout << "Difference (A \ B): ";
    MyList<int> diff = setA.Difference(setB);
    diff.Print();

    cout << "Symmetric Diff (A △ B): ";
    MyList<int> symDiff = setA.SymmetricDifference(setB);
    symDiff.Print();

    cout << "-----------------------\n";

    MyList<int> subSet;
    subSet.Insert(50);
    subSet.Insert(30);
    cout << "Set subSet: "; subSet.Print();

    cout << "Is subSet a subset of A? : " << (setA.IsSubset(subSet) ? "Yes" : "No") << endl;
    cout << "Is B a subset of A?      : " << (setA.IsSubset(setB) ? "Yes" : "No") << endl;

     cout << "|________________________________|" << endl;

    int setSize = 2500;
    int experimentsCount = 1000;

    long long totalDuration = 0;

    for (int i = 0; i < experimentsCount; i++){
        MyList<int> setA;
        MyList<int> setB;

        for (int j = 0; j < setSize; j++){
            setA.Insert(rand() % 10000);
            setB.Insert(rand() % 10000);
        }

        auto start = chrono::high_resolution_clock::now();

        MyList<int> result = setA.Union(setB);

        auto end = chrono::high_resolution_clock::now();

        totalDuration += chrono::duration_cast<chrono::microseconds>(end - start).count();
    }

    long long averageTime = totalDuration / experimentsCount;
    cout << "--- Time Test: Union (Size: " << setSize << ") ---" << endl;
    cout << averageTime << " microseconds" << endl;



    cout << "|________________________________|" << endl;
    int setSize1 = 2500;
    int experimentsCount1 = 1000;

    long long totalTimeFound = 0;
    long long totalTimeNotFound = 0;

    for (int i = 0; i < experimentsCount1; i++) {
        MyList<int> mySet;
        int targetFound = -1;
        int targetNotFound = -999;

        for (int j = 0; j < setSize1; j++) {
            int randomValue = rand() % 10000;
            mySet.Insert(randomValue);

            if (j == setSize1 / 2) {
                targetFound = randomValue;
            }
        }

        auto start1 = chrono::high_resolution_clock::now();

        bool dummy1;
        for(int k = 0; k < 1000; k++) {
            dummy1 = mySet.Search(targetFound);
        }

        auto end1 = chrono::high_resolution_clock::now();
        totalTimeFound += chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count();

        auto start2 = chrono::high_resolution_clock::now();

        bool dummy2;
        for(int k = 0; k < 1000; k++) {
            dummy2 = mySet.Search(targetNotFound);
        }

        auto end2 = chrono::high_resolution_clock::now();
        totalTimeNotFound += chrono::duration_cast<chrono::nanoseconds>(end2 - start2).count();
    }

    long long averageFound = totalTimeFound / (experimentsCount * 1000);
    long long averageNotFound = totalTimeNotFound / (experimentsCount * 1000);

    cout << "--- Time Test: SEARCH (Size: " << setSize1 << ") ---" << endl;
    cout << "Average time (Element FOUND)     : " << averageFound << " ns." << endl;
    cout << "Average time (Element NOT FOUND) : " << averageNotFound << " ns." << endl;

    return 0;
}
