#ifndef LINKED_LIST
#define LINKED_LIST

#include <assert.h>
#include <memory>
#include <iostream>

#include "iterator.h"

template <typename T>
struct node{
    node<T>*    m_next;
    T           m_value;
};


template <typename T>
class linked_list{
private:
    node<T> *head, *tail;

public:
    linked_list(){
        head = nullptr;
        tail = nullptr;
        }
    void create_node(T value);
    void print(){
        Iterator<node<T>, T> itr(head);
        while(itr.m_itr != nullptr){
            std::cout << itr.m_value << std::endl;
            ++itr;
        }
    }
};

template <typename T>
void linked_list<T>::create_node(T value){

    node<T>* temp(new node<T>);
    temp->m_value = value;
    temp->m_next  = nullptr;
    if(head == nullptr){
        head = temp;
        tail = temp;
        temp = nullptr;
    }
    else{
        tail->m_next  = temp;
        tail          = temp;
    }
}

#endif
