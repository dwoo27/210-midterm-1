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
            cout << "Position must be >= 0." << endl; //prints message
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
            //prints message
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

        Node* temp = head; //temp ptr to start from head of list

        while (temp && temp->data != value) //runs while temp isn't null and target isn't found
            temp = temp->next; //moves temp along list

        if (!temp) return; //if temp null, return

        if (temp->prev) //checks if temp has previous 
            temp->prev->next = temp->next; //sets temp prev's next to temp next 
                                           //to account for incoming gap
        else //if temp prev is null, temp is head 
            head = temp->next; //head moves to next node

        if (temp->next) //checks if temp has next
            temp->next->prev = temp->prev; //sets temp's next prev to temp prev
                                           //to account for incoming gap
        else //if temp next is null, temp is tail
            tail = temp->prev; //til moves to prev node

        delete temp; //delete temp node, node searched for
    }
    //deletes node at given pos
    void delete_pos(int pos) {
        if (!head) { //checks for empty list
            cout << "List is empty." << endl; //print empty list
            return; //nothing to be deleted, return to main
        }

        if (pos == 1) { //if pos is 1, first node
            pop_front(); //call pop_front() 
            return; //return to main
        }

        Node* temp = head; //temp ptr to start from head of list

        for (int i = 1; i < pos; i++) { //runs until pos is reached, starts at 1
                                        //already covered by prev if statement
            if (!temp) { //checks if temp is null
                cout << "Position doesn't exist." << endl; //print message
                return; //return to main 
            }
            else //moves temp up the list
                temp = temp->next;
        }
        if (!temp) { //checks if temp is null
            cout << "Position doesn't exist." << endl; //print message
            return; //pos still invalid, return to main
        }

        if (!temp->next) { //if temp next is null, temp is tail
            pop_back(); //call pop_back()
            return; //return to main 
        }

        //case if pos is found and valid
        Node* tempPrev = temp->prev; //ptr for temp prev node
        tempPrev->next = temp->next; //prev node set to next, skips
        temp->next->prev = tempPrev; //temps next node's prev is set to node before temp
        delete temp; //delete temp node
    }

    //adds new node to end of list, takes in data val
    void push_back(int v) { 
        Node* newNode = new Node(v); //new node declared to be added
        if (!tail) //if tail is null, list empty
            head = tail = newNode; //head/tail set to newNOde
        else { //list is populated
            tail->next = newNode; //newNode assigned after tail
            newNode->prev = tail; //newNode prev set to tail
            tail = newNode; //tail resassigned to newNode
        }
    }

    //adds new node to front of list, takes in data val
    void push_front(int v) {
        Node* newNode = new Node(v); //new node declared to be added
        if (!head) //if head is null, list empty
            head = tail = newNode; //head/tail set to newNode
        else { //list is populated
            newNode->next = head; //newNode assigned before head
            head->prev = newNode; //head node prev set to newNode
            head = newNode; //head reassigned to newNode
        }
    }

    //removes first node
    void pop_front() {

        if (!head) { //checks if head is null, list empty
            cout << "List is empty." << endl; //print message
            return; //return to main
        }

        Node* temp = head; //temp stores node to be removed

        if (head->next) { //checks if more than one node in list
            head = head->next; //head set to next in list
            head->prev = nullptr; //head prev set to null
        }
        else //only one node in list
            head = tail = nullptr; //both head/tail set to null, now empty
        delete temp; //delete temp node
    }

    //removes last node
    void pop_back() {
        if (!tail) { //checks if tail is null, list empty
            cout << "List is empty." << endl; //print message
            return; //return to main
        }
        Node* temp = tail; //ptr to hold node to be deleted

        if (tail->prev) { //if more than one node
            tail = tail->prev; //tail reassigned to second to last node
            tail->next = nullptr; //tail next set to null
        }
        else //only one node in list
            head = tail = nullptr; //both head/tail,set to null, now empty
        delete temp; //delete temp node
    }

    //destructor, runs when DoublyLinkedlist obj is destroyed
    ~DoublyLinkedList() {
        while (head) { //while head is not null 
            Node* temp = head; //ptr to node to be deleted, start at head
            head = head->next; //sets head to next node in list
            delete temp; //deletes node 
        }
    }
    void print() { //prints list
        Node* current = head; //ptr to node to be deleted, starting at head
        if (!current) { //if current is null, list empty
            cout << "List is empty." << endl; //print messaged
            return; //return to main
        }
        while (current) { //while current not null
            cout << current->data << " "; //print data of current node
            current = current->next; //moves current allong list
        }
        cout << endl; //print blank line
    }

    void print_reverse() { //prints list in reverse
        Node* current = tail; //ptr to node to be printed, starting at tail
        if (!current) { //if current is null, list is empty
            cout << "List is empty." << endl; //print message
            return; //return to main
        }
        while (current) { //runs while current is not null 
            cout << current->data << " "; //print current node data
            current = current->prev; //moves current down list
        }
        cout << endl; //prints blank line
    }

    void every_other_element() { //prints every other element in list
        Node* current = head; //ptr to node to be printed, starting at head
        if (!current) { //if current is null, list is empty
            cout << "List is empty." << endl; //print message
            return; //return to main
        }
        while (current) { //runs while current is not null 
            cout << current->data << " "; //print current node data

            if (current->next) { //must check if next node exists to keep within bounds of list
                current = current->next->next; //moves current up list twice, rather than once
            }
            else { //if bounds reached
                current = nullptr; //current set to null 
            }

        }
        cout << endl; //prints blank line
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning, prints 4 global consts

    DoublyLinkedList; //creates obj and runs default constructor
                      //head/tail set to null, empty list


    return 0;
}