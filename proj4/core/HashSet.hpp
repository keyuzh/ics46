// HashSet.hpp
//
// ICS 46 Winter 2021
// Project #4: Set the Controls for the Heart of the Sun
//
// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.
//
// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector) to store the information
// in your data structure.  Instead, you'll need to use a dynamically-
// allocated array and your own linked list implemenation; the linked list
// doesn't have to be its own class, though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <functional>
#include <utility>
#include "Set.hpp"



template <typename ElementType>
class HashSet : public Set<ElementType>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction is a function that takes a reference to a const
    // ElementType and returns an unsigned int.
    using HashFunction = std::function<unsigned int(const ElementType&)>;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    explicit HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    ~HashSet() noexcept override;

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Initializes a new HashSet whose contents are moved from an
    // expiring one.
    HashSet(HashSet&& s) noexcept;

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);

    // Assigns an expiring HashSet into another.
    HashSet& operator=(HashSet&& s) noexcept;


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    bool isImplemented() const noexcept override;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8, in which case
    // the new capacity should be determined by this formula:
    //
    //     capacity * 2 + 1
    //
    // In the case where the array is resized, this function runs in linear
    // time (with respect to the number of elements, assuming a good hash
    // function); otherwise, it runs in constant time (again, assuming a good
    // hash function).  The amortized running time is also constant.
    void add(const ElementType& element) override;


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    bool contains(const ElementType& element) const override;


    // size() returns the number of elements in the set.
    unsigned int size() const noexcept override;


    // elementsAtIndex() returns the number of elements that hashed to a
    // particular index in the array.  If the index is out of the boundaries
    // of the array, this function returns 0.
    unsigned int elementsAtIndex(unsigned int index) const;


    // isElementAtIndex() returns true if the given element hashed to a
    // particular index in the array, false otherwise.  If the index is
    // out of the boundaries of the array, this functions returns 0.
    bool isElementAtIndex(const ElementType& element, unsigned int index) const;


private:
    HashFunction hashFunction;

    struct Node
    {
        ElementType value;
        Node* next;
    };

private:
    // pointer to an array of pointers, each points to a linked list
    Node** hashTable;

    // current bucket count
    unsigned int capacity;

    // current count of number of values stored in bucket
    unsigned int currentSize;

    // give a key string, returns the index in bucket
    unsigned int hashKey(const ElementType& key) const;

    // initialize hashTable to be an array of nullptr of size n
    void initializeTable(unsigned int n);

    // double the number of buckets and rehash everything
    void rehash();

    // given a pointer to an hashTable, add all contents in that table
    // into the table of this class, if removeOld == true, then nodes
    // from old table will be deleted after adding to new table
    void mergeTable(
        Node** oldTable, const unsigned int size, bool removeOld = false
    );

    unsigned int sizeAtIndex(unsigned int index) const;

    double loadFactor() const;
    
public:
    // maximum load factor
    static constexpr double MAX_LOAD_FACTOR = 0.8;

    // remove all stored key/value pairs in the HashMap
    void clear();
};



namespace impl_
{
    template <typename ElementType>
    unsigned int HashSet__undefinedHashFunction(const ElementType& element)
    {
        return 0;
    }
}


template <typename ElementType>
HashSet<ElementType>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction},
    hashTable{new Node*[DEFAULT_CAPACITY]},
    capacity{DEFAULT_CAPACITY},
    currentSize{0}
{
    initializeTable(DEFAULT_CAPACITY);
}


template <typename ElementType>
HashSet<ElementType>::~HashSet() noexcept
{
    clear();
    delete[] hashTable;
}


template <typename ElementType>
HashSet<ElementType>::HashSet(const HashSet& s)
    : hashFunction{impl_::HashSet__undefinedHashFunction<ElementType>},
    hashTable{new Node*[s.capacity]},
    capacity{s.capacity},
    currentSize{0}
{
    initializeTable(s.capacity);
    mergeTable(s.hashTable, s.capacity);
}


template <typename ElementType>
HashSet<ElementType>::HashSet(HashSet&& s) noexcept
    : hashFunction{impl_::HashSet__undefinedHashFunction<ElementType>},
    hashTable{nullptr},
    capacity{0},
    currentSize{0}
{
    std::swap(hashTable, s.hashTable);
    std::swap(capacity, s.capacity);
    std::swap(currentSize, s.currentSize);
}


template <typename ElementType>
HashSet<ElementType>& HashSet<ElementType>::operator=(const HashSet& s)
{
    if (this != &s)
    {
        // delete the original table
        clear();
        delete[] hashTable;

        // copy member vaiables from the new object
        hashFunction = s.hashFunction;
        hashTable = new Node*[s.capacity];
        capacity = s.capacity;
        currentSize = 0;

        // copy contents in the table
        initializeTable(s.capacity);
        mergeTable(s.hashTable, s.capacity);
    }
    return *this;
}


template <typename ElementType>
HashSet<ElementType>& HashSet<ElementType>::operator=(HashSet&& s) noexcept
{
    if (this != &s)
    {
        std::swap(hashTable, s.hashTable);
        std::swap(capacity, s.capacity);
        std::swap(currentSize, s.currentSize);
    }
    return *this;
}


template <typename ElementType>
bool HashSet<ElementType>::isImplemented() const noexcept
{
    return true;
}


template <typename ElementType>
void HashSet<ElementType>::add(const ElementType& element)
{
    // if key already exists do nothing
    if (contains(element))
    {
        return;
    }
    
    // get the index in hashTable to add
    unsigned int hashedValue = hashKey(element);

    if (hashTable[hashedValue] == nullptr)  // target bucket is empty
    {
        // make a new linked list
        hashTable[hashedValue] = new Node{element, nullptr};
    }
    else  // collision, add to end of existing linked list
    {
        Node* pointer = hashTable[hashedValue];

        while (pointer->next != nullptr)  // iterate to the end
        {
            pointer = pointer->next;
        }
        
        pointer->next = new Node{element, nullptr};  // add to the end
    }
    // increment the number of key/value pairs stored in the hashmap
    currentSize++;

    // check load factor to see if rehash is needed
    if (loadFactor() > MAX_LOAD_FACTOR)
    {
        rehash();
    }
}


template <typename ElementType>
bool HashSet<ElementType>::contains(const ElementType& element) const
{
    // go to the correct bucket
    Node* pointer = hashTable[hashKey(element)];

    // go through the linked list and check each key
    while (pointer != nullptr)
    {
        // check node->key
        if (pointer->value == element)  // found match
        {
            return true;
        }
        pointer = pointer->next;
    }
    return false;  // no match
}


template <typename ElementType>
unsigned int HashSet<ElementType>::size() const noexcept
{
    return currentSize;
}


template <typename ElementType>
unsigned int HashSet<ElementType>::elementsAtIndex(unsigned int index) const
{
    if (index >= capacity)
    {
        return 0;
    }
    return sizeAtIndex(index);
}


template <typename ElementType>
bool HashSet<ElementType>::isElementAtIndex(const ElementType& element, unsigned int index) const
{
    if (index >= capacity)
    {
        return false;
    }

    Node* pointer = hashTable[index];

    // go through the linked list and check each key
    while (pointer != nullptr)
    {
        // check node->key
        if (pointer->value == element)  // found match
        {
            return true;
        }
        pointer = pointer->next;
    }
    return false;  // no match
}

template <typename ElementType>
void HashSet<ElementType>::initializeTable(unsigned int n)
{
    // make every cell in the array a nullptr
    for (unsigned int i = 0; i < n; i++)
    {
        hashTable[i] = nullptr;
    }
}

template <typename ElementType>
void HashSet<ElementType>::clear()
{
    // delete all linked list stored in the hashmap
    for (unsigned int i = 0; i < capacity; i++)
    {
        if (hashTable[i] != nullptr)  // linked list found, now delete it
        {
            Node* pointer = hashTable[i];
            // iterate through the list and delete each node
            while (pointer != nullptr)
            {
                Node* toRemove = pointer;
                pointer = pointer->next;
                delete toRemove;
                currentSize--;
            }
            hashTable[i] = nullptr;  // restore the cell in array to be nullptr
        }
    }
}


template <typename ElementType>
unsigned int HashSet<ElementType>::hashKey(const ElementType& key) const
{
    // find the right bucket for the given key
    return (hashFunction(key) % capacity);
}


template <typename ElementType>
void HashSet<ElementType>::rehash()
{
    // increase the size of hashmap and rehash everything
    unsigned int oldSize = capacity;
    unsigned int newSize = (capacity * 2) + 1;

    Node** oldTable = hashTable;     // make a pointer to point to the old table
    hashTable = new Node*[newSize];  // make a new table of bigger size

    // set properties of new table
    capacity = newSize;
    currentSize = 0;
    initializeTable(newSize);

    // add contents from old table to new table, also delete all nodes
    mergeTable(oldTable, oldSize, true);
    delete[] oldTable;
}


template <typename ElementType>
void HashSet<ElementType>::mergeTable(
    Node** oldTable, const unsigned int size, bool removeOld
)
    // given a pointer to an hashTable, add all contents in that table
    // into the table of this class, if removeOld == true, then nodes
    // from old table will be deleted after adding to new table
{
    // loop through the old table and re-add everything
    for (unsigned int i = 0; i < size; i++)
    {
        if (oldTable[i] != nullptr)
        {
            // add the values to new array (then delete the old node if needed)
            Node* pointer = oldTable[i];

            while (pointer != nullptr)
            {
                add(pointer->value);

                Node* toRemove = pointer;
                pointer = pointer->next;

                if (removeOld == true)  // delete old node if needed
                {
                    delete toRemove;
                }
            }
        }
    }
}

template <typename ElementType>
unsigned int HashSet<ElementType>::sizeAtIndex(unsigned int index) const
{
    unsigned int sz{0};
    if (hashTable[index] != nullptr)  // there is a linked list at the bucket
        {
            Node* pointer = hashTable[index];
            do  // iterate through the end of linked list
            {
                sz++;
                pointer = pointer->next;
            } while (pointer != nullptr);
        }
    return sz;
}

template <typename ElementType>
double HashSet<ElementType>::loadFactor() const
{
    return double(currentSize) / double(capacity);
}

#endif // HASHSET_HPP

