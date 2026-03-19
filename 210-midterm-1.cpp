#include <iostream> //gives access to use cout/endl
using namespace std; //for cout

//global const values 
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20; 


class DoublyLinkedList { //class declaration
private: 
    struct Node {//struct as attribute to serve as node in class for dbl linked list
        int data; //holds data
        Node* prev; //holds pointer to prev node
        Node* next; //holds pointer to next node
        
        //parameter constructor can take in int for data value and pointers for prev/next
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };

    Node* head; //pointer for head, first node in list
    Node* tail; //pointer for tail, last pointer in list

public:
    //deafault constructor, asssigns in null for head/tail
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    //function inserts new node with value after node with position
    void insert_after(int value, int position) {
        if (position < 0) { //checks for invalid position
            cout << "Position must be >= 0." << endl;
            return; //exit function if invalid pos recieved
        }

        Node* newNode = new Node(value); //creates new node with value as data and null prev/next
        if (!head) { //checks if list is empty
            head = tail = newNode; //lets new node become head/tail
            return; //exit function after
        }

        Node* temp = head; //temp ptr to start from head of list
        for (int i = 0; i < position && temp; ++i) //runs until it reaches pos and temp not null
            temp = temp->next; //moves temp forward along list 

        if (!temp) { //check if temp null
            cout << "Position exceeds list size. Node not inserted.\n"; //means pos is out of bounds for list
            delete newNode; //delete node to insert to prevent memory leak
            return; // exit funciton
        }

        //after position found
        newNode->next = temp->next;  //set next for newNode to what temp's next is
        newNode->prev = temp; //set newNode prev to temp because it's inserted after temp
        if (temp->next) //check if temp has next
            temp->next->prev = newNode; //update so node points to newNode, npt temp
        else //if temp has no next node (tail)
            tail = newNode; //set tail to newNode
        temp->next = newNode; //temp points to newNode,finally inserted after
    }

    //find first node that has value and delete
    void delete_val(int value) {
        if (!head) return; //if list empty, return and exit

        Node* temp = head; ////temp ptr to start from head of list

        while (temp && temp->data != value) //runs while temp isn't null and target isn't found
            temp = temp->next; //moves temp along list

        if (!temp) return; //if temp null, return

        if (temp->prev) //
            temp->prev->next = temp->next;
        else
            head = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        if (pos == 1) {
            pop_front();
            return;
        }

        Node* temp = head;

        for (int i = 1; i < pos; i++) {
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp->next) {
            pop_back();
            return;
        }

        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning


    return 0;
}