//
// Created by Nakyeong Kim on 2020/10/27.
//

#include "dLinkedList.h"

dNode::dNode(int data, dNode* n_ptr, dNode* p_ptr) //constructor of dNode class
{
    this->data = data;
    next = n_ptr;
    prev = p_ptr;
}

dLinkedList::dLinkedList() //constructor of dLinkedList
{
    Head = new dNode(-1); //making dummy node. this is front dummy node
    Tail = new dNode(-1); //and this is rear dummy node
    Head->next = Tail; //connecting two dummy node
    Tail->prev = Head;
}

dLinkedList::~dLinkedList() //destructor
{
    dNode* p;
    for (dNode* n = Head; n = Tail; n = p)
    {
        p = n->next;
        delete n;
    }
    delete p;
}

dLinkedList::dLinkedList(const dNode &node
){
    *Head = node;
    Tail = new dNode(-1);
    Head->next = Tail;
    Tail->prev = Head;
}

dLinkedList::dLinkedList(const dLinkedList &list)
{
    if ( list.Head == nullptr)
        Head = Tail = nullptr;                       // if "otherList" is empty the new list is empty too.
    else
    {
        Head = new dNode(list.Head);      // allocate head and copy data
        dNode* tmp_other = list.Head->next;
        dNode* tmp = Head;
        while (tmp_other != nullptr )
        {
            tmp->next = new dNode(tmp_other); // allocate next element and copy data ( predecessor is "tmp" )
            tmp = tmp->next;                                      // temp refers to last element of list
            tmp_other = tmp_other->next;                            // step one forward
        }
        Tail = tmp;
    }
}

void dLinkedList::push_front(int data) //push data at right behind to Head
{
    dNode* tmp = new dNode(data); //make new node
    tmp->prev = Head; //connecting new node with head and next node.
    tmp->next = Head->next;
    Head->next->prev = tmp;
    Head->next = tmp;
}

void dLinkedList::push_back(int data)//push data at right in front of Tail
{
    dNode* tmp = new dNode(data); //make new node
    tmp->next = Tail; //connecting new node with tail and previous node.
    tmp->prev = Tail->prev;
    Tail->prev->next = tmp;
    Tail->prev = tmp;
}

void dLinkedList::pop_front() //delete node that is right behind to Head.
{
    dNode* tmp = Head->next;
    Head->next = tmp->next; //deconnecting node with previous and next node
    tmp->next->prev = Head;
    delete tmp;
}

void dLinkedList::pop_back() //delete node that is right in front of Tail.
{
    dNode* tmp = Tail->prev;
    Tail->prev = tmp->prev; //deconnecting node with previous and next node
    tmp->prev->next = Tail;
    delete tmp;
}

dNode dLinkedList::front() //get front node
{
    return *Head;
}

dNode dLinkedList::back()
{
    return *Tail;
}

void dLinkedList::insert(int data, dNode* p)
{
    dNode* tmp = new dNode(data); //making new node
    tmp->next = p->next; //connectig node with p and p->next
    tmp->prev = p;
    p->next->prev = tmp;
    p->next = tmp;
}

void dLinkedList::delete_node(dNode* p)
{
    dNode* tmp = p->prev;
    tmp->next = p->next; //deconnecting p with p->prev, p->next
    p->next->prev = tmp;
    delete p;
}

void dLinkedList::remove(dNode &start, dNode *stop)
{
    if (stop == nullptr){
        dNode* n;
        for (n=Head; n == Tail; n=n->next){
            delete_node(n);
        }
    }
    else{
        dNode* n;
        for (n = Head->next; n != stop; n=n->next)
        {
            delete_node(n);
        }
    }
}

dNode* dLinkedList::locate_data(int data)// find where is data that we want.
{
    dNode* n;
    for (n = Head->next; n != Tail; n = n->next)
    {
        if (n->data == data)
            break;
    }
    return n;
}

void dLinkedList::print()
{
    cout << "In the Doubly Linked List..." << endl;
    for (dNode* n = Head->next; n != Tail; n = n->next)
    {
        cout << n->data << "\t";
    }
    cout << endl;
}

void dLinkedList::set_empty()
{
    Head = nullptr;
}

bool dLinkedList::IsEmpty()
{
    if ((Head->next == Tail) && (Tail->prev == Head))
        return true;
    else
        return false;
}
