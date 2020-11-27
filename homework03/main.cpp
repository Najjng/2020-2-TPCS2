//
// Created by Nakyeong Kim on 2020/10/27.
//
// SNU-ID: 2018-15185
//
// Homework 03
//
// This code is Doubly Linked List (though class name is Linked List)
//
// First of all, when divided into header and source files, using templates makes errors,
// which is due to the compiling order
// so I decided to write codes only in this main.cpp file
//
// Second, I referred a lot to the codes Erik provided for the class
// which is https://github.com/esevre/TPCS2_2020/blob/master/LinkedLists/main.cpp
// I had hard time making constructors when I tried to write codes for every case
// but I just found using 'using' look better
// so I deleted my original codes and referred it to him.
//
// However, since it is a homework for me, I tried to write comments about how the lines work
// to show that it is not just a copy.
// I did try another ways when this code was splitted into header and source files
// but unfortunately, they were not really good and caused a lot of errors.
// so while referring to Erik's code, I wrote comments on myself about how I understood them.
//
// I made two dummy nodes, head and tail, for me to understand doubly linked list easier.
// so head and tail here are nodes that don't have any useful information.
// The requested functions dealing with head and tail, for example, set_empty() function,
// were written under comprehending the condition required for head is for head->next
// because head in my code is a dummy node and the real head with data is head->next
// as well as tail->prev
//

#include <iostream> // for output
#include <string>

template <class Type>
struct Node{
public:
    using NodeBase     = Node<Type>;
    using NodePtr      = NodeBase*; // NodePtr instead of *Node
    using ConstNodePtr = const NodePtr;
public:
    // constructor
    Node() = default;
    Node(const Type &value, NodePtr next_node = nullptr, NodePtr prev_node = nullptr)
            : value(value), next(next_node), prev(prev_node)
    {}

    // I didn't write Node destructor
    // under the assumption that destructor of LinkedList works properly

public:
    Type    value; // Node's value as node->value
    NodePtr next = nullptr;
    NodePtr prev = nullptr;
    const bool print_on_delete = false;
};

template <class Type>
class LinkedList {
public:
    using NodeType     = Node<Type>;
    using NodePtr      = NodeType *; // NodePtr instead of *Node
    using ConstNodePtr = const NodePtr;
    using LinkedListType = LinkedList<Type>;
    using LinkedListRef  = LinkedListType &;
public:
    // consturctor
    LinkedList() = default;
    // constructor with initializer list
    LinkedList(const std::initializer_list<Type> &list)
    {
        head = new NodeType(-1); //dummy node with meaningless value
        tail = new NodeType(-1); //dummy node with meaningless value
        tail->prev = head; // link the tail and head
        head->next = tail;
        for (const auto & val : list) {
            push_back(val);
        }
    }
    // deep copy constructor
    LinkedList(const LinkedList &list) {
        head = new NodeType(-1); //dummy node with meaningless value
        tail = new NodeType(-1); //dummy node with meaningless value
        tail->prev = head; // link the tail and head
        head->next = tail;
        NodePtr pos = list.head->next;
        while(pos->next) {
            push_back(pos->value);
            pos = pos->next;
        }
    }
    // destructor
    ~LinkedList() {
        NodePtr p;
        if (head->next != nullptr && head != nullptr) {
            for (NodePtr n = head; n != tail; n = p)
            {
                p = n->next;
                delete n;
            }
            delete p;
        }
    }


    // Do a deep copy for the assignment operator
    // this is the code referred to Erik's github
    LinkedListRef operator=(const LinkedListRef list) {
        // our head will be overwritten with the new list
        delete head;     // delete this list
        head = nullptr;  // make sure our head is pointing to the nullptr
        auto pos = list.first();
        while (pos) {
            push_back(pos->value);
            pos = pos->next;
        }
        return *this;
    }


    // add node to back as new tail
    LinkedListRef push_back(const Type &val)
    {
        if (head->next) { // head is head->next which is the next node of the dummy node
            NodePtr tmp = new NodeType(val); //make new node
            tmp->next = tail; //connecting new node with tail and previous node.
            tmp->prev = tail->prev; //new tail in front of the dummy node
            tail->prev->next = tmp;
            tail->prev = tmp;
        }
        else {
            head->next = new NodeType(val); //if there's no head Node, make a new Node
        }
        return *this;
    }

    // add node to front as new head
    LinkedListRef push_front(const Type &val)
    {
        if (head->next) { // head is head->next which is the next node of the dummy node
            NodePtr tmp = new NodeType(val); //make new node
            tmp->prev = head; //connecting new node with head and next node.
            tmp->next = head->next; //new head next to the dummy node
            head->next->prev = tmp;
            head->next = tmp;
        }
        else {
            head->next = new NodeType(val); //if there's no head Node, make a new Node
        }
        return *this;
    }

    //remove and return back node
    NodePtr pop_back()
    {
        NodePtr tmp = tail->prev;
        tail->prev = tmp->prev; //deconnecting node with previous and next node
        tmp->prev->next = tail;
        return tmp; //return the NodePtr
    }

    //remove and return front node
    NodePtr pop_front()
    {
        NodePtr tmp = head->next;
        head->next = tmp->next; //deconnecting node with previous and next node
        tmp->next->prev = head;
        return tmp; //return the NodePtr
    }

    //get front node
    Type front()
    {
        return head->next->value; //get the node after dummy node
    }

    //get back node
    Type back()
    {
        return tail->prev->value; //get the node before dummy node
    }


    // create a new node with insert_value after the node with target_value
    // if there's no node with the target value, push_back it
    LinkedListRef insert_at(const Type &insert_value, const Type &target_value)
    {
        int flag = 0; //break keyword didn't work in this code so added flag which works as break
        NodePtr n;
        for (n = head->next; n != tail; n = n->next)
        {
            if (n->value == target_value) {
                NodePtr tmp = new NodeType(insert_value); //new node with insert_value
                tmp->next = n->next; //connect the new node with previous and next nodes
                n->next->prev = tmp;
                n->next = tmp;
                tmp->prev = n;
                flag = 1; //flag=1 means there's target value
            } else if (n->next == tail && flag==0)   {
                push_back(insert_value); //using value instead of Node to avoid memory leak
            }
        }
        return *this;
    }

    // insert the given linked list right after the node with target_value in the original list
    // if there's no node with target_value, just push back the given linked list to the original one
    LinkedListRef insert_at(const LinkedList &list, const Type &target_value)
    {
        NodePtr n;
        int flag = 0; // instead of the keyword break. description above in the different insert function
        for (n = head->next; n != tail; n = n->next)
        {
            if (n->value == target_value) {
                list.tail->prev->next = n->next; // link the node with target value and the given list
                n->next->prev = list.tail->prev;
                n->next = list.head->next;
                list.head->next->prev = n;
                flag = 1;
                list.head->next = nullptr;
                list.tail->prev = nullptr;

            } else if (n->next == tail && flag == 0)   {
                n->next = list.head->next; // push back the given list
                list.head->next->prev = n;
                list.tail->prev->next = this->tail;
                this->tail->prev = list.tail->prev;
                delete list.head;
                delete list.tail;
            }
        }
        return *this;
    }

    // delete_node deletes specific node with the given pointer
    LinkedListRef delete_node(NodePtr p)
    {
        NodePtr tmp = p->prev;
        tmp->next = p->next; // deconnect p with previous and next nodes
        tmp->next->prev = tmp;
        delete p;
    }

    // remove the nodes from the start node to the node right before the stop node
    // !! to be edited !!
    LinkedListRef remove(Node<Type> &start, Node<Type> &stop)
    {
        if (&stop == nullptr){
            NodePtr n;
            for (n=head; n != tail; n=n->next){
                delete n;
            }
        }
        else{
            NodePtr n;
            for (n = &start; n != &stop; n=n->next)
            {
                NodePtr pos = n->prev;
                pos->next = n->next;
                n->next->prev = pos;
                delete n;
            }
        }
        return *this;
    }

    // set_empty() sets the head node to nullptr
    // here the head is head->next, which is the node after the dummy node
    LinkedListRef set_empty()
    {
        head->next = nullptr;
        return *this;
    }

    // get count of the length of the LinkedList
    // to use in different functions
    int getCount()
    {
        int count = 0;// Initialize count
        NodePtr current = head->next; // Initialize current
        while (current->next)
        {
            count++;
            current = current->next;
        }
        return count;
    }

    // find where is node with the value that we want.
    NodePtr locate_value(const Type &target_value)
    {
        NodePtr n;
        for (n = head->next; n != tail; n = n->next)
        {
            if (n->value == target_value) // if the value we want was found
                break;
        }
        return n;
    }

    // rotate function prints the output as it is rotated by start, pivot and stop nodes
    // here when I say print node, it means printing the value of the node
    // it prints in the original order til encountering start node
    // between start and stop nodes, function first prints from the pivot node to the node right before the stop node
    // and then print the nodes from the start to the node right before the pivot node
    // after the stop node, the function again prints the nodes in order
    void rotate(Node<Type> &start, Node<Type> &pivot, Node<Type> &stop)
    {
        NodePtr start_ptr = &start;
        NodePtr pivot_ptr = &pivot;
        NodePtr stop_ptr = &stop;

        NodePtr n;
        std::cout << "[";
        for (n = head->next; n != start_ptr; n = n->next) {
            std::cout << n->value << ", ";
        }
        for (n = pivot_ptr; n != stop_ptr->next; n = n->next) {
            std::cout << n->value << ", ";
        }
        for (n = start_ptr; n != pivot_ptr; n = n->next) {
            std::cout << n->value << ", ";
        }
        for (n = stop_ptr->next; n != tail; n = n->next) {
            std::cout << n->value << ", ";
        }
        std::cout << "\b" << "\b" << "] \n"; // to erase the last ',' after tail

    }

    NodePtr      first()       { return head; }
    ConstNodePtr first() const { return head; }

    bool empty() const { return head==nullptr; }

public:
    NodePtr head = nullptr;
    NodePtr tail = nullptr;
private:
    void reset_head(NodePtr node_ptr=nullptr) { head = node_ptr; }

};


//the list will be printed as [1, 2, 3, 4, 5], ['A', 'B', 'C']
template <class Type>
void PrintList(const LinkedList<Type> &list)
{
    typename LinkedList<Type>::NodePtr pos = list.head->next;
    std::cout << '[';
    while (pos->next->next) {
        std::cout << pos->value << ",";
        pos = pos->next;
    }
    std::cout << pos->value <<']' << std::endl;
}

//bubble sort algorithm
template <class Type>
void SortList(LinkedList<Type> &list) {
    int count = list.getCount();
    typename LinkedList<Type>::NodePtr current; // current node for iteration
    int i, j;

    for (i = 1; i < count; i++) {
        current = list.head;
        for (j = 0; j <= count - i; j++) {
            typename LinkedList<Type>::NodePtr before, after; // use before and after to avoid confusion
            if (current->value > current->next->value) { // compare values of two adjacent nodes
                before = current->prev;
                after = current->next;
                if (before != nullptr) {
                    before->next = after;
                } else {
                    // if before pointer is nullptr, it is the head node
                    list.head = after; // if before pointer is nullptr, after pointer should be the new head
                }
                current->next = after->next;
                current->prev = after;

                if (after->next != nullptr) {
                    after->next->prev = current; // prev pointer of after->next set to current
                }

                after->next = current;
                after->prev = before;
            } else {
                current = current->next; // move to the next node if current->value > current->next->value is false
            }
        }
    }
}

// SortedMerge function works as merging two sorted lists
// so it's under the assumption that two given lists are sorted
template <class Type>
LinkedList<Type> SortedMerge(LinkedList<Type> &list1, LinkedList<Type> &list2)
{
    typename LinkedList<Type>::NodePtr n;
    list1.tail->prev->next = list2.head->next; // connect two lists
    list2.head->next->prev = list1.tail->prev->next;
    list2.tail->prev->next = list1.tail;
    list1.tail->prev = list2.tail->prev;

    delete list2.tail;

    SortList(list1); // the output is saved in list1
    list2.set_empty(); // list2 is set empty
    return list1;
}

bool push_back_test() {
    LinkedList<int> list01{1, 2, 3, 4};
    LinkedList<int> list02{1, 2, 3, 4, 5};
    typename LinkedList<int>::NodePtr n;
    typename LinkedList<int>::NodePtr m;
    list01.push_back(5);
    if (list01.getCount() != list02.getCount()){
        return false;
    } else {
        m = list02.head->next;
        for (n=list01.head->next; n != list01.tail; n=n->next){
            if (n->value != m->value){
                return false;
            }
            m = m->next;
        }
    }
    return true;
}

bool push_front_test() {
    LinkedList<int> list01{2, 3, 4, 5};
    LinkedList<int> list02{1, 2, 3, 4, 5};
    typename LinkedList<int>::NodePtr n;
    typename LinkedList<int>::NodePtr m;
    list01.push_front(1);
    if (list01.getCount() != list02.getCount()){
        return false;
    } else {
        m = list02.head->next;
        for (n=list01.head->next; n != list01.tail; n=n->next){
            if (n->value != m->value){
                return false;
            }
            m = m->next;
        }
    }
    return true;
}

bool pop_back_test() {
    LinkedList<int> list01{1, 2, 3, 4, 5};
    LinkedList<char> list02{'A', 'B', 'C', 'D'};
    if (list01.tail->prev != list01.pop_back()){
        return false;
    }
    if (list02.tail->prev != list02.pop_back()){
        return false;
    }
    return true;
}

bool pop_front_test() {
    LinkedList<int> list01{1, 2, 3, 4, 5};
    LinkedList<char> list02{'A', 'B', 'C', 'D'};
    if (list01.head->next != list01.pop_front()){
        return false;
    }
    if (list02.head->next != list02.pop_front()){
        return false;
    }
    return true;
}

bool remove_test() {
    LinkedList<int> list01{1, 2, 3, 4, 5};
    LinkedList<int> list02{1, 4, 5};
    typename LinkedList<int>::NodePtr n;
    typename LinkedList<int>::NodePtr m;
    list01.remove(*list01.locate_value(2), *list01.locate_value(4));
    if (list01.getCount() != list02.getCount()){
        return false;
    } else {
        m = list02.head->next;
        for (n=list01.head->next; n != list01.tail; n=n->next){
            if (n->value != m->value){
                return false;
            }
            m = m->next;
        }
    }
    return true;
}

bool insert_test_1() {
    LinkedList<int> list01{1, 2, 3, 4, 5};
    LinkedList<int> list02{1, 2, 6, 3, 4, 5};
    list01.insert_at(6, 2);
    typename LinkedList<int>::NodePtr n;
    typename LinkedList<int>::NodePtr m;
    if (list01.getCount() != list02.getCount()){
        return false;
    } else {
        m = list02.head->next;
        for (n=list01.head->next; n != list01.tail; n=n->next){
            if (n->value != m->value){
                return false;
            }
            m = m->next;
        }
    }
    return true;
}

bool insert_test_2() {
    LinkedList<int> list01{1, 2, 3, 4, 5};
    LinkedList<int> list02{1, 2};
    LinkedList<int> list03{1, 2, 3, 1, 2, 4, 5};
    list01.insert_at(list02, 3);

    typename LinkedList<int>::NodePtr n;
    typename LinkedList<int>::NodePtr m;
    if (list01.getCount() != list03.getCount()){
        return false;
    } else {
        m = list03.head->next;
        for (n=list01.head->next; n != list01.tail; n=n->next){
            if (n->value != m->value){
                return false;
            }
            m = m->next;
        }
    }
    return true;
}

bool SortedMerge_test() {
    LinkedList<int> list01{1, 3, 5};
    LinkedList<int> list02{2, 4};
    LinkedList<int> list03 = SortedMerge(list01, list02);
    LinkedList<int> list04{1, 2, 3, 4, 5};
    typename LinkedList<int>::NodePtr n;
    typename LinkedList<int>::NodePtr m;

    if (list03.getCount() != list04.getCount()){
        return false;
    } else {
        m = list04.head->next;
        for (n=list03.head->next; n != list03.tail; n=n->next){
            if (n->value != m->value){
                return false;
            }
            m = m->next;
        }
    }
    return true;
}

template <class TestFunction>
void run_test(TestFunction test_function, const std::string& test_name) {
    if (test_function()){
        std::cout << "SUCCESS: " << test_name << "\n";
    }
    else{
        std::cout << "FAILURE: " << test_name << "\n";
    }
}

int main() {

    run_test(push_back_test, "push_back test");
    run_test(push_front_test, "push_front test");
    run_test(pop_back_test, "pop_back test");
    run_test(pop_front_test, "pop_front test");
    run_test(remove_test, "remove test");
    run_test(insert_test_1, "insert_at test with value");
    run_test(insert_test_2, "insert_at test with linked list");
    run_test(SortedMerge_test, "SortedMerge test");

    std::cout << "Below is the result of function rotate \n";
    LinkedList<int> list01{1, 2, 3, 4, 5, 6, 7};
    LinkedList<int> list02(list01);
    list01.rotate(*list01.locate_value(2), *list01.locate_value(3), *list01.locate_value(5));

}

