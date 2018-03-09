#ifndef ITERATOR
#define ITERATOR

#include <assert.h>
#include <memory>

// We have a template for T and U because we want to be able to have iterators of the form:
// Iterator< T<U> >. This means we can implement it for many types, e.g node<T>.
// A better way to do this woud be to have the class using Iterator to inherit from iterator.h
// and create it's own iterator that can be called. This could be achieved via recurring template
// patterns or via mixin classes.
template <typename T, typename U>

// Each iterator must store a pointer to the current object, a pointer to the next obect, and the value
// of the current object. However, if implemeted by RTP or mixins then the iterator itself could be
// a pointer of type the needed object and then it could simply access that objects value and pointer to the
// next object.

struct Iterator{
    T*      m_itr;
    T*      m_next;
    U       m_value;

    Iterator() : m_itr(nullptr), m_next(nullptr), m_value(nullptr){}
    Iterator(T* head) : m_itr(head), m_next(head->m_next), m_value(head->m_value){}
    ~Iterator(){m_itr = nullptr; m_next = nullptr;}

    Iterator& operator++ (){ // Pre-increment i.e itr++
        assert(m_itr != nullptr && "Out-of-bounds Iterator increment!");
        m_itr   = m_next;
        if(m_itr == nullptr){return *this;}
        m_next  = m_itr->m_next;
        m_value = m_itr->m_value;
        return *this;
    }

    Iterator operator++ (int){ // Post-increment i.e ++itr
        assert(m_itr != nullptr && "Out-of-bounds Iterator increment!");
        Iterator tmp(*this);
        m_itr   = m_next;
        if(m_itr == nullptr){return tmp;}
        m_next  = m_itr->m_next;
        m_value = m_itr->m_value;
        return tmp;
    }
};


#endif
