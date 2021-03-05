#ifndef PROBLEM4_HPP
#define PROBLEM4_HPP

#include <initializer_list>

#include <map>
#include <vector>

template <typename T>
class DisjointSetForest
{
public:
    DisjointSetForest(std::initializer_list<T> elements);

    template <typename Iterator>
    DisjointSetForest(Iterator begin, Iterator end);

    const T& at(std::size_t index) const;
    std::size_t indexOf(const T& element) const;

    std::size_t weightOf(std::size_t index);
    std::size_t weightOf(const T& element);

    std::size_t findRoot(std::size_t index);
    std::size_t findRoot(const T& element);

    bool unionSets(std::size_t index1, std::size_t index2);
    bool unionSets(const T& element1, const T& element2);

    std::size_t elementCount() const;
    std::size_t setCount() const;

private:
    std::size_t getParent(std::size_t index);
    void changeParent(std::size_t index, std::size_t newParent);

    struct Node
    {
        T value;
        std::size_t parent;
        std::size_t weight;
    };

    std::vector<Node> array;
    std::map<T, std::size_t> map;
    std::size_t setCnt;
};



template <typename T>
DisjointSetForest<T>::DisjointSetForest(std::initializer_list<T> elements)
    : setCnt{0}
{
    size_t i = 0;
    for(auto& e : elements)
    {
        array.push_back(Node{e, i, 1});
        map[e] = i;
        i++;
        setCnt++;
    }
}


template <typename T>
template <typename Iterator>
DisjointSetForest<T>::DisjointSetForest(Iterator begin, Iterator end)
    : setCnt{0}
{
    size_t ind = 0;
    for (auto i = begin; i != end; i++)
    {
        array.push_back(Node{*i, ind, 1});
        map[*i] = ind;
        ind++;
        setCnt++;
    }
}


template <typename T>
const T& DisjointSetForest<T>::at(std::size_t index) const
{
    return array.at(index).value;
}


template <typename T>
std::size_t DisjointSetForest<T>::indexOf(const T& element) const
{
    return map.at(element);
}


template <typename T>
std::size_t DisjointSetForest<T>::weightOf(std::size_t index)
{
    return array.at(findRoot(index)).weight;
}


template <typename T>
std::size_t DisjointSetForest<T>::weightOf(const T& element)
{
    return weightOf(indexOf(element));
}

template <typename T>
std::size_t DisjointSetForest<T>::getParent(std::size_t index)
{
    return array.at(index).parent;
}

template <typename T>
void DisjointSetForest<T>::changeParent(std::size_t index, std::size_t newParent)
{
    array.at(index).parent = newParent;
}

template <typename T>
std::size_t DisjointSetForest<T>::findRoot(std::size_t index)
{
    std::size_t parent = getParent(index);
    if (parent == index)
    {
        return index;
    }
    // path compression
    std::size_t root = findRoot(parent);
    changeParent(index, root);
    return root;
}


template <typename T>
std::size_t DisjointSetForest<T>::findRoot(const T& element)
{
    return findRoot(indexOf(element));
}


template <typename T>
bool DisjointSetForest<T>::unionSets(std::size_t index1, std::size_t index2)
{
    std::size_t root1 = findRoot(index1);
    std::size_t root2 = findRoot(index2);
    if (root1 == root2)
    {
        // already the same set
        return false;
    }
    std::size_t weight1 = weightOf(index1);
    std::size_t weight2 = weightOf(index2);
    // weighted union
    if (weight1 < weight2)
    {
        // make weight2 be the root
        changeParent(root1, index2);
        array.at(index2).weight += weight1;
    }
    else
    {
        // make weight1 be the root
        changeParent(root2, index1);
        array.at(index1).weight += weight2;
    }
    setCnt--;
    return true;
}


template <typename T>
bool DisjointSetForest<T>::unionSets(const T& element1, const T& element2)
{
    return unionSets(indexOf(element1), indexOf(element2));
}


template <typename T>
std::size_t DisjointSetForest<T>::elementCount() const
{
    return array.size();
}


template <typename T>
std::size_t DisjointSetForest<T>::setCount() const
{
    return setCnt;
}



#endif

