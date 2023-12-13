#ifndef MYVECTOR_H
#define MYVECTOR_H 1

#include<iostream>
#include<string>
#include <initializer_list>

template <typename T>
class Vector{
private:
    int len;
    int capacity;
    T* arr;

public:
    Vector();
    Vector(int n);
    Vector(T *arr);
    Vector(const Vector&);
    Vector& operator=(const Vector&);
    Vector(Vector&&);
    Vector& operator=(Vector&&);
    ~Vector();

    T operator[](int index) const;
    T& operator[](int index);
    T back() const;
    T& back();
    T front() const;
    T& front();

    int size() const;
    int get_capacity() const;
    bool empty() const;

    void reserve(int new_alloc);
    void resize(int new_size);
    void resize(int new_size, T fill_value);
    void push_back(T new_elem);
    void insert(int ind, T new_elem);
    void pop_back();
    void pop(int index);

    T* begin() const;
    T* end() const;
};


template<typename T>
Vector<T>::Vector() : len{0}, capacity{0}, arr{nullptr} {}


template<typename T>
Vector<T>::Vector (int n) : len{n}, capacity{n}, arr{new T[n]} {
    for(int i = 0; i < n; i++)
        arr[i] = T();
}

template<typename T>
Vector<T>::Vector (T *array) : len{int(sizeof(array) / sizeof(T))}, capacity{(sizeof(array) / sizeof(T))}, arr{new T[int(sizeof(array) / sizeof(T))]}
{
    for (int i = 0; i < int(sizeof(array) / sizeof(T)); ++i)
        arr[i] = array[i];
}

template<typename T>
Vector<T>::Vector (const Vector<T>& v) : len{int(v.size())}, capacity{int(v.capacity())}, arr{new T[v.capacity]}
{
    for (int i = 0; i < v.size(); ++i)
        arr[i] = v[i];
}

template<typename T>
Vector<T>& Vector<T>::operator= (const Vector<T>& v)
{
    if(this == &v)
        return *this;
    if(v.size() <= capacity)
    {
        for(int i = 0; i < v.size(); i++)
        {
            arr[i] = v[i];
        }
        len = v.size();
        return *this;
    }
    T* temp_elem = new T[v.size()];
    for(int i = 0; i < v.size(); i++)
        temp_elem[i] = v[i];
    for(int i = 0; i < len; i++)
        arr[i].~T();
    delete[] arr;
    arr = temp_elem;
    capacity = v.size();
    len = v.size();
    return *this;
}

template<typename T>
Vector<T>::Vector (Vector<T>&& v) : arr{v.size()}, arr{v.arr}
{
    capacity = v.capacity();
    v.len = 0;
    v.capacity = 0;
    v.arr = nullptr;
}

template<typename T>
Vector<T>& Vector<T>::operator= (Vector<T>&& v)
{
    for(int i = 0; i < len; i++)
        arr[i].~T();//elem[i].~T();
    delete[] arr;//delete[] elem;
    arr = v.arr;
    arr = v.size();
    capacity = v.capacity();

    v.arr = nullptr;
    v.capacity = 0;
    v.len = 0;
    return *this;
}

template<typename T>
Vector<T>::~Vector ()
{ 
    if(arr != nullptr && capacity != 0 && len != 0)
    {
        for(int i = 0; i < len; i++)
            arr[i].~T();
        delete[] arr;
    }
}

template<typename T>
T Vector<T>::operator[] (int index) const
{
    if(index < 0 || index >= len)
        throw std::runtime_error("Out of range\n");
    return arr[index];
}

template<typename T>
T& Vector<T>::operator[] (int index)
{
    if(index < 0 || index >= len)
        throw std::runtime_error("Out of range\n");
    return arr[index];
}

template<typename T>
T Vector<T>::back() const
{
    if(empty())
        throw std::runtime_error("Can't get the last element from an empty vector");
    return arr[len - 1];
}

template<typename T>
T& Vector<T>::back()
{
    if(empty())
        throw std::runtime_error("Can't get the last element from an empty vector");
    return arr[len - 1];
}

template<typename T>
T Vector<T>::front() const
{
    if(empty())
        throw std::runtime_error("Can't get the first element from an empty vector");
    return arr[0];
}

template<typename T>
T& Vector<T>::front()
{
    if(empty())
        throw std::runtime_error("Can't get the first element from an empty vector");
    return arr[0];
}

template<typename T>
T* Vector<T>::begin () const { return arr; }

template<typename T>
T* Vector<T>::end () const { return arr + len; }

template<typename T>
int Vector<T>::size () const { return len; }

template<typename T>
int Vector<T>::get_capacity () const { return capacity; }

template<typename T>
bool Vector<T>::empty () const { return size() == 0; }


template<typename T>
void Vector<T>::reserve (int new_alloc)
{
    if(new_alloc <= capacity)
        return;
    T* p = new T[new_alloc];
    for(int i = 0; i < len; i++)
    {
        p[i]=arr[i];
        arr[i].~T();
    }
    delete[] arr;
    arr= p;
    capacity = new_alloc;
}

template<typename T>
void Vector<T>::resize (int new_size)
{
    reserve(new_size);
    for(int i = len; i < new_size; i++)
        arr[i] = 0;
    len = new_size;
}

template<typename T>
void Vector<T>::resize(int new_size, T fill_value)
{
    reserve(new_size);
    for(int i = 0; i < new_size; i++)
        arr[i] = fill_value;
    len = new_size;
}


template<typename T>
void Vector<T>::push_back (T new_elem)
{
    if(len > capacity)
        throw std::runtime_error("How did size became bigger than capacity?!\n");
    else if(capacity == 0)
    {
        T* temp_elem = new T[8];;//new T[8];
        temp_elem[0] = new_elem;//temp_elem[0] = new_elem;
        if(arr != nullptr)
        {
            for(int i = 0; i < len; i++)
                arr[i].~T();
            delete[] arr;
        }
        arr = temp_elem;
        capacity = 8;
        len = 1;
    }
    else if(len == capacity)
    {
        T* temp_elem = new T[capacity*2];
        for(int i = 0; i < len; i++)
            temp_elem[i] = arr[i];
        temp_elem[len] = new_elem;
        for(int i = 0; i < len; i++)
            arr[i].~T();
        delete[] arr;
        arr = temp_elem;

        capacity = capacity*2;
        len++;
    }
    else
    {
        arr[len] = new_elem;
        len++;
    }
}

template<typename T>
void Vector<T>::insert (int ind, T new_elem)
{
    if(ind < 0 || ind >= len)
        throw std::runtime_error("Out of range\n");
    if(ind == len-1)
    {
        push_back(new_elem);
        return;
    }

    push_back(T());

    for(int i = len - 1; i > ind; i--)
    {
        arr[i] = arr[i-1];
    }
    arr[ind] = new_elem;
}

template<typename T>
void Vector<T>::pop_back ()
{
    if(len > capacity)
        throw std::runtime_error("How did size became bigger than capacity?!\n");
    else if(capacity == 0)
        throw std::runtime_error("can't pop_back from an empty vector\n");
    else if(capacity > 0)
    {
        back().~T();
        len--;
        if(len == 0)
        {
            if(arr!= nullptr)
                delete[] arr;
            arr= nullptr;

            capacity = 0;
            len = 0;
        }
        else if(2*len <= capacity)
        {
            T* temp_elem = new T[len];
            for(int i = 0; i < len; i++)
            {
                temp_elem[i] = arr[i];
                arr[i].~T();
            }
            delete[] arr;
            arr = temp_elem;
            
            capacity = len;
        }
    }
}

template<typename T>
void Vector<T>::pop(int ind)
{
    if(ind < 0 || ind >= len)
        throw std::runtime_error("Out of range\n");
    if(ind == len-1)
    {
        pop_back();
        return;
    }
    for(int i = ind; i < len-1; i++)
        arr[i] = arr[i+1];
    back().~T();
    len--;
    if(len == 0)
    {
        if(arr!= nullptr)
            delete[] arr;
        arr = nullptr;
        
        capacity = 0;
        len = 0;
    }
    else if(2*len <= capacity)
    {
        T* temp_elem = new T[len];
        for(int i = 0; i < len; i++)
        {
            temp_elem[i] = arr[i];
            arr[i].~T();
        }
        delete[] arr;
        arr = temp_elem;
        
        capacity = len;
    }
}


template<typename T>
std::ostream& operator<< (std::ostream& os, const Vector<T>& rhs)
{
    if(rhs.empty())
        os << "[]";
    else
    {
        T* ptr = rhs.begin();
        os << '[' << *ptr;
        for(T* itr = rhs.begin() + 1; itr < rhs.end(); itr++)
            os << ", " << *itr;
        os << ']';
    }
    return os;
}




#endif