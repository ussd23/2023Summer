#pragma once
#include "StandardLibrary.h"

template<typename T> class SPTR
{
protected:
    T* ptr;

public:
    static map<T*, int>         m_ReferenceCounts;

public:
    SPTR() : SPTR(nullptr) {}

    SPTR(T* _ptr)
    {
        ptr = _ptr;
        RefUp();
    }

    SPTR(SPTR&& other)
    {
        ptr = other.ptr;
        RefUp();
    }

    SPTR(const SPTR& other)
    {
        ptr = other.ptr;
        RefUp();
    }

    virtual ~SPTR()
    {
        RefDown();
    }

    void operator=(T* _ptr)
    {
        if (ptr != _ptr)
        {
            RefDown();
            ptr = _ptr;
            RefUp();
        }
    }

    bool operator==(T* _ptr)
    {
        if (ptr == _ptr) return true;
        else return false;
    }

    bool operator==(const SPTR& other)
    {
        if (ptr == other->ptr) return true;
        else return false;
    }

    bool operator!=(T* _ptr)
    {
        if (ptr != _ptr) return true;
        else return false;
    }

    bool operator!=(const SPTR& other)
    {
        if (ptr != other->ptr) return true;
        else return false;
    }

    T* operator->()
    {
        return ptr;
    }

    T* operator()()
    {
        return ptr;
    }

    void RefUp()
    {
        if (ptr == nullptr) return;

        if (m_ReferenceCounts.find(ptr) == m_ReferenceCounts.end())
        {
            m_ReferenceCounts.insert(make_pair(ptr, 1));
        }
        else
        {
            m_ReferenceCounts[ptr] += 1;
        }
    }

    void RefDown()
    {
        if (ptr == nullptr) return;

        if (m_ReferenceCounts.find(ptr) != m_ReferenceCounts.end())
        {
            m_ReferenceCounts[ptr] -= 1;
            if (m_ReferenceCounts[ptr] == 0)
            {
                m_ReferenceCounts.erase(m_ReferenceCounts.find(ptr));
                delete ptr;
            }
        }
    }
};

template<typename T> map<T*, int> SPTR<T>::m_ReferenceCounts;