#ifndef Iterator_h
#define Iterator_h


#include <iostream>
#include <memory>
#include <ctime>

#include "IteratorBase.h"
#include "Errors.h"


template<class DataType>
class Vector;

template <typename DataType>
class Iterator : public IteratorBase
{
private:
      std::weak_ptr<DataType> ptr;

public:
	Iterator(const Iterator<DataType>& iter);
    Iterator(const Vector<DataType>& vec, size_t index = 0);

	DataType& operator*();
    const DataType& operator*() const;
    DataType* operator->();
    const DataType* operator->() const;

    Iterator<DataType>& operator=(const Iterator<DataType>& iter);
    Iterator<DataType>& operator++();
    Iterator<DataType> operator++(int);
    Iterator<DataType>& operator--();
    Iterator<DataType> operator--(int);

    operator bool() const;

    bool operator<=(const Iterator<DataType>& b) const;
    bool operator<(const Iterator<DataType>& b) const;
    bool operator>=(const Iterator<DataType>& b) const;
    bool operator>(const Iterator<DataType>& b) const;
    bool operator==(const Iterator<DataType>& b) const;
    bool operator!=(const Iterator<DataType>& b) const;

    bool control(int string) const;
};

template <typename DataType>
Iterator<DataType>::Iterator(const Vector<DataType>& vec, size_t index)
{
    num_elem = vec.size();
    ptr = vec.coords;
    position = index;
}

template <typename DataType>
Iterator<DataType>::Iterator(const Iterator<DataType>& iter)
{
    ptr = iter.ptr;
    position = iter.position;
    num_elem = iter.num_elem;
}

template <typename DataType>
DataType& Iterator<DataType>::operator*()
{
    control(__LINE__);
	auto thisPtr = this->ptr.lock();

	DataType *rawData = thisPtr.get();
	DataType *pointedData = rawData + this->position;
	return *(pointedData);
}

template <typename DataType>
const DataType& Iterator<DataType>::operator*() const
{
    control(__LINE__);
	auto thisPtr = this->ptr.lock();

	DataType *rawData = thisPtr.get();
	DataType *pointedData = rawData + this->position;
	return *(pointedData);
}

template <typename DataType>
DataType* Iterator<DataType>::operator->()
{
    control(__LINE__);
	auto thisPtr = this->ptr.lock();

	DataType *rawData = thisPtr.get();
	DataType *pointedData = rawData + this->position;
	return pointedData;
}

template <typename DataType>
const DataType* Iterator<DataType>::operator->() const
{
    control(__LINE__);
	auto thisPtr = this->ptr.lock();

	DataType *rawData = thisPtr.get();
	DataType *pointedData = rawData + this->position;
	return pointedData;
}

template <typename DataType>
Iterator<DataType>& Iterator<DataType>::operator=(const Iterator<DataType>& iter)
{
    control(__LINE__);

    ptr = iter.ptr;
    position = iter.position;
    num_elem = iter.num_elem;
    return *this;
}

template <typename DataType>
Iterator<DataType>& Iterator<DataType>::operator++()
{
    control(__LINE__);

    ++position;
    return *this;
}

template <typename DataType>
Iterator<DataType> Iterator<DataType>::operator++(int)
{
    control(__LINE__);

    Iterator<DataType> tmp(*this);
    this->operator++();
    return tmp;
}

template <typename DataType>
Iterator<DataType>& Iterator<DataType>::operator--()
{
    control(__LINE__);

    --position;
    return *this;
}

template <typename DataType>
Iterator<DataType> Iterator<DataType>::operator--(int)
{
    control(__LINE__);

    Iterator<DataType> tmp(*this);
    this->operator--();
    return tmp;
}

template <typename DataType>
Iterator<DataType>::operator bool() const
{
    control(__LINE__);

    if (position >= num_elem || position < 0 || (num_elem == 0))
        return false;
    else
        return true;
}

template <typename DataType>
bool Iterator<DataType>::operator<=(const Iterator<DataType>& b) const
{
    control(__LINE__);

    return ptr <= b.ptr;
}

template <typename DataType>
bool Iterator<DataType>::operator<(const Iterator<DataType>& b) const
{
    control(__LINE__);

    return ptr < b.ptr;
}

template <typename DataType>
bool Iterator<DataType>::operator>=(const Iterator<DataType>& b) const
{
    control(__LINE__);

    return ptr >= b.ptr;
}

template <typename DataType>
bool Iterator<DataType>::operator>(const Iterator<DataType>& b) const
{
    control(__LINE__);

    return ptr > b.ptr;
}

template <typename DataType>
bool Iterator<DataType>::operator==(const Iterator<DataType>& b) const
{
    control(__LINE__);

    auto thisPtr = ptr.lock();
    auto iterPtr = b.ptr.lock();

    return (thisPtr.get() == iterPtr.get()) && (position == b.position);
}

template <typename DataType>
bool Iterator<DataType>::operator!=(const Iterator<DataType>& b) const
{
    control(__LINE__);

    return !(*this == b);
}

template <typename DataType>
bool Iterator<DataType>::control(int string) const
{
    if (!ptr.expired())
        return true;

    time_t t_time = time(NULL);
    throw DeletedObj(__FILE__, string, ctime(&t_time));
    return false;
}

#endif /* Iterator_h */
