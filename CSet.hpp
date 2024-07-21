#pragma once
/*
* * Counter set, is a set that counts that is all
*/
#include <unordered_map>
#include <set>
template <typename T>
class CSet
{
public:
    CSet();

    void add(T obj);
    int check(T obj);
    bool empty();
    void remove(T obj);
    void clear();
    std::set<T> getSet();
    ~CSet();

private:
    std::unordered_map<T, int> objCounter;
    std::set<T> objPool;
};

template <typename T>
CSet<T>::CSet()
{
    this->objCounter.clear();
    this->objPool.clear();
}

template <typename T>
void CSet<T>::add(T obj)
{
    this->objCounter[obj] += 1;
    this->objPool.emplace(obj);
}

template <typename T>
bool CSet<T>::empty()
{
    return this->objCounter.empty();
}

template <typename T>
int CSet<T>::check(T obj)
{
    return this->objCounter[obj];
}

template <typename T>
void CSet<T>::remove(T obj)
{
    this->objCounter[obj] -= 1;
    if (this->objCounter[obj] <= 0)
    {
        this->objCounter.erase(obj);
        this->objPool.erase(obj);
    }
}

template <typename T>
void CSet<T>::clear()
{
    this->objCounter.clear();
    this->objPool.clear();
}

template <typename T>
std::set<T> CSet<T>::getSet()
{
    return this->objPool;
}

template <typename T>
CSet<T>::~CSet()
{
    this->objCounter.clear();
    this->objPool.clear();
}
