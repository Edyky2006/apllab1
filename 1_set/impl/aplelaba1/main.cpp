#include <iostream>


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
};
