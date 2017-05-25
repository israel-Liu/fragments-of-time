/************************************************************************************
//sample 1
hinata::Aggregate<int> agg;

for (int i = 0; i < 10; ++i) {
	agg.add(i);
}

hinata::Iterator<int, hinata::Aggregate<int> >* it = agg.createIterator();

for(it->first(); !it->isDone(); it->next()) {
	std::cout << *it->current() << std::endl;
}
*************************************************************************************/
#pragma once

#include <iostream>
#include <iterator>
#include <vector>
#include <set>

namespace hinata {

template<typename T, typename U>
    class Iterator
    {
    public:
        typedef typename std::vector<T>::iterator iter_type;

        Iterator(U* pData)
            :  pData_(pData)
        {
            iter_ = pData_->data_.begin();
        }

        void first()
        {
            iter_ = pData_->data_.begin();
        }

        void next()
        {
            iter_++;
        }

        bool isDone()
        {
            return (iter_ == pData_->data_.end());
        }

        iter_type current()
        {
            return iter_;
        }

    private:
        U* pData_;
        iter_type iter_;
    };

// Aggregate
template <typename T>
    class Aggregate
    {
        friend class Iterator<T, Aggregate>;

    public:
        void add(T a)
        {
            data_.push_back(a);
        }

        Iterator<T, Aggregate>* createIterator()
        {
            return new Iterator<T, Aggregate>(this);
        }

    private:
        std::vector<T> data_;
    };

}
