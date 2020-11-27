//
// Created by Nakyeong Kim on 2020/10/27.
//

#ifndef HOMEWORK02_DLINKEDLIST_H
#define HOMEWORK02_DLINKEDLIST_H

#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

struct dNode : public Node
{
public:
    dNode* next;
    dNode* prev;
    dNode(int data, dNode* n_ptr = nullptr, dNode* p_ptr = nullptr);
};

//template <class DataType>
class dLinkedList : public LinkedList
{
public:
    dLinkedList();
    ~dLinkedList();
    dLinkedList(const dNode &node);
    dLinkedList(const dLinkedList &list);
//    dLinkedList(const initializer_list<DataType> &list);

    void push_front(int data);
    void push_back(int data);
    void pop_front();
    void pop_back();
    dNode front();
    dNode back();
    void insert(int data, dNode* p); //original insert funciton that I made to test if what I thought works well
    // insert_at(const DataType &insert_value, const DataType &target_value);
    //insert_at(const LinkedList &list, const DataType &target_value);
    void delete_node(dNode* p);
    void remove(dNode &start, dNode *stop);
    dNode* locate_data(int data);
    void print();
    void set_empty();
    bool IsEmpty();

private:
    dNode * Head, *Tail;
};


#endif //HOMEWORK02_DLINKEDLIST_H
