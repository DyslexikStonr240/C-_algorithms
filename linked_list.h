#ifndef LINKED_LIST
#define LINKED_LIST

#include <assert.h>
#include <iostream>
#include <iterator>
#include <memory>


// Each node in the linked_list must have a pointer to the next node and a value for itself.
// The node's own pointer will be used by the previous node to connect the two.
template <typename T>
struct node{
    node<T>*    m_next;
    T           m_value;
    node(){};
    node(const T& value) : m_value(value){};
};

template <typename T>
class forward_iterator : public std::iterator<std::forward_iterator_tag, node<T>*>{
protected:
    node<T>* m_itr;

public:
    forward_iterator (node<T>* tmp) : m_itr(tmp) {}
    forward_iterator& operator++(){//pre increment
        assert(m_itr != nullptr && "Cannot increment past the end of a list");
        m_itr = m_itr->m_next;
        return *this;
    }

    const forward_iterator operator++(int){//post increment
        assert(m_itr != nullptr && "Cannot increment past the end of a list");
        forward_iterator<T> tmp(*this);
        m_itr = m_itr->m_next;
        return tmp;
    }

    bool operator== (const forward_iterator<T>& rhs){
        return m_itr == rhs.m_itr;
    }

    bool operator!= (const forward_iterator<T>& rhs){
        return m_itr != rhs.m_itr;
    }

    T& operator*(){
        assert(m_itr != nullptr && "Cannot deference a nullptr in node<T> forward_iterator");
        return m_itr->m_value;
    }

    void insert(T value){
        node<T>* tmp = new node<T>(value);
        tmp->m_next = m_itr->m_next;
        m_itr->m_next = tmp;
        tmp = nullptr;
    }
    void remove(){
        assert(m_itr != nullptr && "Can't delete a nullptr");
        delete m_itr;
    }
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
    node<T> *m_head, *m_tail, *m_end;
    int m_size;

public:
    linked_list(){
        m_head = nullptr;
        m_tail = nullptr;
        m_end  = nullptr;
        m_size = 0;
        }
    ~linked_list();
    void create_node(const T& value);
    void insert_node(const T& value, int position);
    void print();
    forward_iterator<T> begin(){return forward_iterator<T>(m_head);}
    forward_iterator<T> end(){return forward_iterator<T>(m_end);}

};

template <typename T>
linked_list<T>::~linked_list(){
    forward_iterator<T> itr = this->begin();
    while(itr != this->end()){
        forward_iterator<T> tmp(itr++);
        tmp.remove();
    }
}

template <typename T>
void linked_list<T>::create_node(const T& value){

    node<T>* tmp = new node<T>;
    tmp->m_value = value;
    tmp->m_next  = nullptr;
    if(m_head == nullptr){
        m_head = tmp;
        m_tail = tmp;
        tmp = nullptr;
    }
    else{
        m_tail->m_next  = tmp;
        m_tail          = tmp;
    }
    m_size++;
}

template <typename T>
void linked_list<T>::insert_node(const T& value, int position){

    assert(m_size > position && "Cannot insert element into list if the to-be inserted element position is greater than the size of the list.");

    forward_iterator<T> itr(m_head);
    for(int i = 0; i < position; i++){
        ++itr;
    }
    itr.insert(value);
    m_size++;
}

template <typename T>
void linked_list<T>::print(){

    forward_iterator<T> itr(this->begin());

    while(itr != this->end()){
        std::cout << *itr << std::endl;
        itr++;
    }
}
#endif
