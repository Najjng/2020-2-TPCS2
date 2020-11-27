//
// Created by Nakyeong Kim on 2020/10/27.
//

#include <istream>
#include <cstdlib>
#include <cstring>
#include "LinkedList.h"

using namespace std;

Node::Node()
{

}
Node::Node(string st, int dat,Node* ptr)
{
    str = st;
    data = dat;
    next = ptr;
}
void Node::print()
{
    cout  << data << "\t";
}

LinkedList::LinkedList()
{
    L=new Node("dummy",-1);
}

LinkedList::~LinkedList()
{
    Node* p;
    for (Node* n = L; n ; n = p)
    {
        p = n->next;
        delete n;
    }
    delete p;
}

void LinkedList::print()
{
    cout << "In the Linked List...." << endl;
    for (Node *n = L->next; n; n = n->next)
    {
        n->print();
    }
    cout << endl;
}

Node* LinkedList::locate_data(int data)
{
    Node *n;
    for (n = L; n; n = n->next)
    {
        if (n->data == data) //compare function! strcmp
            return n; break;
    }
    if (n == nullptr)
        cout << "There's nothing you want to find in this Linked list" << endl;
}

Node* LinkedList::locate_str(string str)
{
    Node *n;
    for (n = L; n; n = n->next)
    {
        if ((n->str.compare(str)) == 0)
        {
            return n;
        }

    }
    if (n == nullptr)
        return nullptr;
}

void LinkedList::insert_at(string str, int data, Node* p)
{
    Node * tmp = new Node(str, data);

    tmp->next = p->next;
    p->next = tmp;
    delete tmp;
}

void LinkedList::delete_node(Node* p)
{
    for (Node* n = L; n; n = n->next)
    {
        if (n->next == p)
        {
            n->next = p->next;
            delete p;
            break;
        }
    }
}

void LinkedList::push_back(string str, int data)
{
    if (!(L->next))
    {
        L->next = new Node(str, data);
    }
    else
    {
        for (Node* n = L->next; n; n = n->next)
        {
            if (n->next == nullptr)
            {
                n -> next= new Node(str, data);
                break;
            }
        }
    }
}
void LinkedList::push_front(string str, int data)
{
    Node * tmp = new Node(str, data);

    tmp->next = L->next;
    L->next = tmp;
}

void LinkedList::selection_sort(bool isString)
{
    Node* startnode = L->next;
    Node* minnode;
    if (isString)
    {
        while (startnode->next)
        {
            minnode = startnode;
            for (Node* n = startnode->next; n; n = n->next)
            {
                if (minnode->str.compare(n->str)>0)
                {
                    minnode = n;
                }
            }
            int temp; string temp2;
            temp = minnode->data;
            minnode->data = startnode->data;
            startnode->data = temp;
            temp2 = minnode->str;
            minnode->str = startnode->str;
            startnode->str = temp2;
            startnode = startnode->next;
        }
    }
    else
    {
        while (startnode->next)
        {
            minnode = startnode;
            for (Node* n = startnode->next; n; n = n->next)
            {
                if (minnode->data > n->data)
                {
                    minnode = n;
                }
            }
            int temp; string temp2;
            temp = minnode->data;
            minnode->data = startnode->data;
            startnode->data = temp;
            temp2 = minnode->str;
            minnode->str = startnode->str;
            startnode->str = temp2;
            startnode = startnode->next;
        }
    }
    delete startnode;
    delete minnode;
}