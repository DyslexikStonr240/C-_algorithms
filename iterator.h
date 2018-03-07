#ifndef ITERATOR
#define ITERATOR

#include <assert.h>
#include <memory>


template <typename T, typename U>

struct Iterator{
    T*      m_itr;
    T*      m_next;
    U       m_value;

    Iterator() : m_itr(nullptr), m_next(nullptr), m_value(nullptr){}
    Iterator(T* head) : m_itr(head), m_next(head->m_next), m_value(head->m_value){}

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
