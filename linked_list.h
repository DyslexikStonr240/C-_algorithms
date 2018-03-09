#ifndef LINKED_LIST
#define LINKED_LIST

#include <assert.h>
#include <memory>
#include <iostream>

#include "iterator.h"

// Each node in the linked_list must have a pointer to the next node and a value for itself.
// The node's own pointer will be used by the previous node to connect the two.
template <typename T>
struct node{
    node<T>*    m_next;
    T           m_value;
};

// The linked_list contains two pointer to node objects, these are the head and tail nodes.
// At initialisation these pointers are null and therefore the list doesn't contain any values.
// When create_node is called it creates a temporary node pointer with a given value and then,
// depending on the state of the list it does one of two things. If the list contains no elements
// then create_node will set both the head and tail equal to the temporary node. Otherwise it will
// set the tail equal to the temporary node, essentially adding a node to the end of the list.
//
// insert_node works similarly except it removes the links between two nodes at a specified position
// and then links them to the temporary node.
//
// The destructor iterates through the linked list to delete all of the nodes. This assures no memory
// leaks occur.
template <typename T>
class linked_list{
private:
    node<T> *m_head, *m_tail;
    int m_size;

public:
    linked_list(){
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;
        }
    ~linked_list();
    void create_node(const T& value);
    void insert_node(const T& value, int position);
    void print();

};

template <typename T>
linked_list<T>::~linked_list(){

    Iterator<node<T>, T> itr(m_head);
    /*while(itr.m_itr != nullptr){
        delete itr.m_itr;
        ++itr;
    }*/
    for(int i = 0; i < m_size; i++){
        delete itr.m_itr;
        ++itr;
    }
}

template <typename T>
void linked_list<T>::create_node(const T& value){

    node<T>* temp(new node<T>);
    temp->m_value = value;
    temp->m_next  = nullptr;
    if(m_head == nullptr){
        m_head = temp;
        m_tail = temp;
        temp = nullptr;
    }
    else{
        m_tail->m_next  = temp;
        m_tail          = temp;
    }
    m_size++;
}

template <typename T>
void linked_list<T>::insert_node(const T& value, int position){

    assert(m_size > position && "Cannot insert element into list if the to-be inserted element position is greater than the size of the list.");

    node<T>* temp(new node<T>);
    temp->m_value = value;
    Iterator<node<T>, T> itr(m_head);
    for(int i = 0; i < position - 1; i++){
        ++itr;
    }
    temp->m_next = itr.m_next;
    itr.m_itr->m_next = temp;

    m_size++;
}

template <typename T>
void linked_list<T>::print(){

    Iterator<node<T>, T> itr(m_head);
    while(itr.m_itr != nullptr){
        std::cout << itr.m_value << std::endl;
        ++itr;
    }
}
#endif
