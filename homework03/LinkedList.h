//
// Created by Nakyeong Kim on 2020/10/27.
//

#ifndef HOMEWORK02_LINKEDLIST_H
#define HOMEWORK02_LINKEDLIST_H

#include <iostream>
#include <string>

using namespace std;

struct Node{
public:
    string str;
    int data;
    Node* next;

    Node(string str, int data, Node* ptr = nullptr);
    void print();
    Node();
};

//<template class Type>
class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    void insert_at(string str, int data, Node* p);
    void delete_node(Node* p);
    Node* locate_str(string str);
    Node* locate_data(int data);

    void push_back(string str, int data);
    void push_front(string str, int data);
    void selection_sort(bool isString);
    void print();

    Node* L;
};

#endif //HOMEWORK02_LINKEDLIST_H
