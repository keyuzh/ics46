// SkipListSet.hpp
//
// ICS 46 Winter 2021
// Project #4: Set the Controls for the Heart of the Sun
//
// A SkipListSet is an implementation of a Set that is a skip list, implemented
// as we discussed in lecture.  A skip list is a sequence of levels
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector) to store the keys and their
// values.  Instead, you'll need to implement your own dynamically-allocated
// nodes, with pointers connecting them.  You can, however, use other parts of
// the C++ Standard Library -- including <random>, notably.
//
// Each node should contain only two pointers: one to the node that follows it
// on the same level and another to the equivalent node on the level below it.
// Additional pointers use more memory but don't enable any techniques not
// enabled by the other two.
//
// A couple of utilities are included here: SkipListKind and SkipListKey.
// You can feel free to use these as-is and probably will not need to
// modify them, though you can make changes to them, if you'd like.

#ifndef SKIPLISTSET_HPP
#define SKIPLISTSET_HPP

#include <memory>
#include <random>
#include "Set.hpp"




// SkipListKind indicates a kind of key: a normal one, the special key
// -INF, or the special key +INF.  It's necessary for us to implement
// the notion of -INF and +INF separately, since we're building a class
// template and not all types of keys would have a reasonable notion of
// -INF and +INF.

enum class SkipListKind
{
    Normal,
    NegInf,
    PosInf
};




// A SkipListKey represents a single key in a skip list.  It is possible
// to compare these keys using < or == operators (which are overloaded here)
// and those comparisons respect the notion of whether each key is normal,
// -INF, or +INF.

template <typename ElementType>
class SkipListKey
{
public:
    SkipListKey(SkipListKind kind, const ElementType& element);

    bool operator==(const SkipListKey& other) const;
    bool operator<(const SkipListKey& other) const;

    ElementType getElement() {return element;}

private:
    SkipListKind kind;
    ElementType element;
};


template <typename ElementType>
SkipListKey<ElementType>::SkipListKey(SkipListKind kind, const ElementType& element)
    : kind{kind}, element{element}
{
}


template <typename ElementType>
bool SkipListKey<ElementType>::operator==(const SkipListKey& other) const
{
    return kind == other.kind
        && (kind != SkipListKind::Normal || element == other.element);
}


template <typename ElementType>
bool SkipListKey<ElementType>::operator<(const SkipListKey& other) const
{
    switch (kind)
    {
    case SkipListKind::NegInf:
        return other.kind != SkipListKind::NegInf;

    case SkipListKind::PosInf:
        return false;

    default: // SkipListKind::Normal
        return other.kind == SkipListKind::PosInf
            || (other.kind == SkipListKind::Normal && element < other.element);
    }
}



// The SkipListLevelTester class represents the ability to decide whether
// a key placed on one level of the skip list should also occupy the next
// level.  This is the "coin flip," so to speak.  Note that this is an
// abstract base class with one implementation, RandomSkipListLevelTester,
// just below it.  RandomSkipListLevelTester is what it sounds like: It
// makes the decision at random (with a 50/50 chance of deciding whether
// a key should occupy the next level).  However, by setting things up
// this way, we have a way to control things more carefully in our
// testing (as you can, as well).
//
// DO NOT MAKE CHANGES TO THE SIGNATURES OF THE MEMBER FUNCTIONS OF
// THE "level tester" CLASSES.  You can add new member functions or even
// whole new level tester classes, but the ones declared below are part
// of how we test your implementation, so they need to maintain the
// parts of the interface that are declared already.

template <typename ElementType>
class SkipListLevelTester
{
public:
    virtual ~SkipListLevelTester() = default;

    virtual bool shouldOccupyNextLevel(const ElementType& element) = 0;
    virtual std::unique_ptr<SkipListLevelTester<ElementType>> clone() = 0;
};


template <typename ElementType>
class RandomSkipListLevelTester : public SkipListLevelTester<ElementType>
{
public:
    RandomSkipListLevelTester();

    bool shouldOccupyNextLevel(const ElementType& element) override;
    std::unique_ptr<SkipListLevelTester<ElementType>> clone() override;

private:
    std::default_random_engine engine;
    std::bernoulli_distribution distribution;
};


template <typename ElementType>
RandomSkipListLevelTester<ElementType>::RandomSkipListLevelTester()
    : engine{std::random_device{}()}, distribution{0.5}
{
}


template <typename ElementType>
bool RandomSkipListLevelTester<ElementType>::shouldOccupyNextLevel(const ElementType& element)
{
    return distribution(engine);
}


template <typename ElementType>
std::unique_ptr<SkipListLevelTester<ElementType>> RandomSkipListLevelTester<ElementType>::clone()
{
    return std::unique_ptr<SkipListLevelTester<ElementType>>{
        new RandomSkipListLevelTester<ElementType>};
}




template <typename ElementType>
class SkipListSet : public Set<ElementType>
{
public:
    // Initializes an SkipListSet to be empty, with or without a
    // "level tester" object that will decide, whenever a "coin flip"
    // is needed, whether a key should occupy the next level above.
    SkipListSet();
    explicit SkipListSet(std::unique_ptr<SkipListLevelTester<ElementType>> levelTester);

    // Cleans up the SkipListSet so that it leaks no memory.
    ~SkipListSet() noexcept override;

    // Initializes a new SkipListSet to be a copy of an existing one.
    SkipListSet(const SkipListSet& s);

    // Initializes a new SkipListSet whose contents are moved from an
    // expiring one.
    SkipListSet(SkipListSet&& s) noexcept;

    // Assigns an existing SkipListSet into another.
    SkipListSet& operator=(const SkipListSet& s);

    // Assigns an expiring SkipListSet into another.
    SkipListSet& operator=(SkipListSet&& s) noexcept;


    // isImplemented() should be modified to return true if you've
    // decided to implement a SkipListSet, false otherwise.
    bool isImplemented() const noexcept override;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function runs in an expected time
    // of O(log n) (i.e., over the long run, we expect the average to be
    // O(log n)) with very high probability.
    void add(const ElementType& element) override;


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in an expected time of O(log n)
    // (i.e., over the long run, we expect the average to be O(log n))
    // with very high probability.
    bool contains(const ElementType& element) const override;


    // size() returns the number of elements in the set.
    unsigned int size() const noexcept override;


    // levelCount() returns the number of levels in the skip list.
    unsigned int levelCount() const noexcept;


    // elementsOnLevel() returns the number of elements that are stored
    // on the given level of the skip list.  Level 0 is the bottom level;
    // level 1 is the one above level 0; and so on.  If the given level
    // doesn't exist, this function returns 0.  (Note that the -INF
    // and +INF shouldn't be counted.)
    unsigned int elementsOnLevel(unsigned int level) const noexcept;


    // isElementOnLevel() returns true if the given element is on the
    // given level, false otherwise.  Level 0 is the bottom level; level 1
    // is the one above level 0; and so on.  If the given level doesn't
    // exist, this function returns false.
    bool isElementOnLevel(const ElementType& element, unsigned int level) const;


private:
    struct Node
    {
        SkipListKey<ElementType> value;
        Node* down;
        Node* next;
    };
    
    std::unique_ptr<SkipListLevelTester<ElementType>> levelTester;
    
    // capacity of the array
    unsigned int capacity;
    // array of pointers pointing at the head of each level's linked list
    Node** levels;
    // size of set
    unsigned int sz;
    // level count
    unsigned int lvlCount;

public:
    // default number of levels in the array
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

private:
    // initiate the given level of skip list (-INF and +INF nodes)
    void initiateLevel(unsigned int level);
    // recursively add a node to the set
    Node* addr(Node* current, const ElementType& element);
    // returns whether the given node is on level 0
    bool atLevelZero(const Node* current);
    // returns a pointer to the +INF node of that level
    Node* findPosInf(unsigned int level) const;
    // insert the node after the given node
    void insertAfter(Node* n, Node* toInsert);
    // double the capacity of the array of pointers
    void increaseCapacity();
    // remove all nodes in the set
    void clear();
    // remove all nodes in a given level
    void clearLevel(unsigned int level);
    // copy the contents from the other skip list
    void copySkipList(const SkipListSet& s);
};



template <typename ElementType>
SkipListSet<ElementType>::SkipListSet()
    : SkipListSet{std::make_unique<RandomSkipListLevelTester<ElementType>>()}
{
}


template <typename ElementType>
SkipListSet<ElementType>::SkipListSet(std::unique_ptr<SkipListLevelTester<ElementType>> levelTester)
    : levelTester{std::move(levelTester)},
    capacity{DEFAULT_CAPACITY},
    levels{new Node*[DEFAULT_CAPACITY]},
    sz{0},
    lvlCount{0}
{
    initiateLevel(0);
}


template <typename ElementType>
SkipListSet<ElementType>::~SkipListSet() noexcept
{
    // delete the nodes
    clear();
    // then delete the array
    delete[] levels;
}

template <typename ElementType>
SkipListSet<ElementType>::SkipListSet(const SkipListSet& s)
    : levelTester{s.levelTester->clone()},
    capacity{s.capacity},
    levels{new Node*[s.capacity]},
    sz{s.size()},
    lvlCount{0}
{
    copySkipList(s);
}


template <typename ElementType>
SkipListSet<ElementType>::SkipListSet(SkipListSet&& s) noexcept
    : levelTester{nullptr},
    capacity{0},
    levels{nullptr},
    sz{0},
    lvlCount{0}
{
    std::swap(levelTester, s.levelTester);
    std::swap(capacity, s.capacity);
    std::swap(levels, s.levels);
    std::swap(sz, s.sz);
    std::swap(lvlCount, s.lvlCount);
}


template <typename ElementType>
SkipListSet<ElementType>& SkipListSet<ElementType>::operator=(const SkipListSet& s)
{
    if (this != &s)
    {
        // first delete current set
        clear();
        delete[] levels;
        // copy data from the other set
        levelTester = s.levelTester->clone();
        capacity = s.capacity;
        levels = new Node*[s.capacity];
        sz = s.size();
        // copy content from the other set
        lvlCount = 0;
        copySkipList(s);
    }
    return *this;
}


template <typename ElementType>
SkipListSet<ElementType>& SkipListSet<ElementType>::operator=(SkipListSet&& s) noexcept
{
    if (this != &s)
    {
        std::swap(levelTester, s.levelTester);
        std::swap(capacity, s.capacity);
        std::swap(levels, s.levels);
        std::swap(sz, s.sz);
        std::swap(lvlCount, s.lvlCount);
    }
    return *this;
}


template <typename ElementType>
bool SkipListSet<ElementType>::isImplemented() const noexcept
{
    return true;
}


template <typename ElementType>
void SkipListSet<ElementType>::add(const ElementType& element)
{
    // do similar thing as contain, but recursively
    if (contains(element))
    {
        // already contains the node
        return;
    }
    // head node of top level
    Node* current = levels[levelCount()-1];
    // addr returns nullptr if the element dont need to occupy another level
    // otherwise we need to create a new level
    Node* result = addr(current, element);
    if (result != nullptr)
    {
        // should add another level
        unsigned int topLevel = lvlCount;
        initiateLevel(topLevel);
        Node* topNegInf = levels[topLevel];
        Node* topNode = new Node{SkipListKey<ElementType>{SkipListKind::Normal, element}, result, topNegInf->next};
        topNegInf->next = topNode;
    }
    // increment size
    sz++;
}

template <typename ElementType>
typename SkipListSet<ElementType>::Node* SkipListSet<ElementType>::addr(Node* current, const ElementType& element)
{
    SkipListKey<ElementType> key{SkipListKind::Normal, element};
    if (atLevelZero(current))
    {
        if (current->next == nullptr || key < current->next->value)
        {
            // we are at the positive infinity in level 0 or the next node has
            // greater value than the key; add current key to current->next
            Node* next = current->next;
            Node* added = new Node{key, nullptr, next};
            current->next = added;
            if (levelTester->shouldOccupyNextLevel(element))
            {
                // add to upper level
                return added;
            }
            // don't add to upper level
            return nullptr;
        }
        // keep going down the linked list in this level
        return addr(current->next, element);
    }
    if (key < current->next->value)
    {
        // go down a level
        Node* below = addr(current->down, element);
        if (below != nullptr)
        {
            // need to add the node to this level
            // according to the recursive stack
            Node* next = current->next;
            Node* added = new Node{key, below, next};
            current->next = added;
            if (levelTester->shouldOccupyNextLevel(element))
            {
                // need to add to upper level
                return added;
            }
        }
        // don't add to upper level
        return nullptr;
    }
    // go down the linked list
    return addr(current->next, element);
}

template <typename ElementType>
bool SkipListSet<ElementType>::atLevelZero(const Node* current)
{
    return (current->down == nullptr);
}


template <typename ElementType>
bool SkipListSet<ElementType>::contains(const ElementType& element) const
{
    // head node of top level
    Node* current = levels[lvlCount-1];
    SkipListKey<ElementType> key{SkipListKind::Normal, element};
    while (current->next != nullptr)
    {
        // if the current node's key is the one we're looking for
        if (current->value == key)
        {
            return true;
        }
        //  else if the next node's key is larger than the key we're looking for:
        else if (key < current->next->value)
        {
            // move down one level (terminating the search if we're already on the bottom level)
            current = current->down;
            if (current == nullptr)
            {
                return false;
            }
        }
        else
        {
            // move forward to the next node on this level
            current = current->next;
        }
    }
    return false;
}


template <typename ElementType>
unsigned int SkipListSet<ElementType>::size() const noexcept
{
    return sz;
}


template <typename ElementType>
unsigned int SkipListSet<ElementType>::levelCount() const noexcept
{
    return lvlCount;
}


template <typename ElementType>
unsigned int SkipListSet<ElementType>::elementsOnLevel(unsigned int level) const noexcept
{
    if (level >= lvlCount)
    {
        // not a valid level
        return 0;
    }
    Node* current = levels[level];
    unsigned int count{0};
    while (true)
    {
        if (current->next == nullptr)
        {
            // since we counted positive infinity, minus one
            return count - 1;
        }
        current = current->next;
        count++;
    }
}


template <typename ElementType>
bool SkipListSet<ElementType>::isElementOnLevel(const ElementType& element, unsigned int level) const
{
    if (level >= lvlCount)
    {
        // not valid 
        return false;
    }
    Node* current = levels[level];
    SkipListKey<ElementType> key {SkipListKind::Normal, element};
    while (current->next != nullptr)
    {
        if (current->value == key)
        {
            // found
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename ElementType>
void SkipListSet<ElementType>::initiateLevel(unsigned int level)
{
    if (level >= capacity)
    {
        // need to increase capacity
        increaseCapacity();
    }
    // create the -inf and +inf nodes and link them together
    SkipListKey<ElementType> neg {SkipListKind::NegInf, ElementType{}};
    SkipListKey<ElementType> pos {SkipListKind::PosInf, ElementType{}};
    Node* first = new Node{neg, nullptr, nullptr};
    Node* last = new Node{pos, nullptr, nullptr};
    // link the two nodes together
    first->next = last;
    levels[level] = first;
    // on upper levels, also link the infinity nodes with the lower level
    if (level != 0)
    {
        Node* belowPosInf = findPosInf(level-1);
        Node* belowNegInf = levels[level-1];
        first->down = belowNegInf;
        last->down = belowPosInf;
    }
    // increment count
    lvlCount++;
}

template <typename ElementType>
typename SkipListSet<ElementType>::Node* SkipListSet<ElementType>::findPosInf(unsigned int level) const
{
    Node* current = levels[level];
    while (true)
    {
        if (current->next == nullptr)
        {
            // at the end of linked list
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template <typename ElementType>
void SkipListSet<ElementType>::clear()
{
    for (unsigned int i = 0; i < levelCount(); i++)
    {
        clearLevel(i);
    }
}

template <typename ElementType>
void SkipListSet<ElementType>::clearLevel(unsigned int level)
{
    Node* current = levels[level];
    while (current != nullptr)
    {
        // delete each node as we traverse the linked list
        Node* toRemove = current;
        current = current->next;
        delete toRemove;
    }
}

template <typename ElementType>
void SkipListSet<ElementType>::increaseCapacity()
{
    // make a new array with twice the capacity, then copy the pointers
    unsigned int newCapacity = capacity * 2 + 1;
    Node** newLevels = new Node*[newCapacity];
    for (unsigned int i = 0; i < capacity; i++)
    {
        newLevels[i] = levels[i];
    }
    delete[] levels;
    levels = newLevels;
    capacity = newCapacity;
}

template <typename ElementType>
void SkipListSet<ElementType>::copySkipList(const SkipListSet& s)
{
    // initiate every level first
    for (unsigned int i = 0; i < s.levelCount(); i++)
    {
        initiateLevel(i);
    }
    // temporary array of pointers to mark where to insert the nodes
    // pointer to the last node in each level, points at negative infinity first
    // we add each node after those nodes
    Node** levelsCopy = new Node*[lvlCount];
    for (unsigned int i = 0; i < lvlCount; i++)
    {
        levelsCopy[i] = levels[i];
    }
    // pointer to negative inf node in bottom level of s
    Node* nextToCopy = s.levels[0];
    // go to the first node (skip negative infinity)
    nextToCopy = nextToCopy->next;
    // traverse level 0 of the other skip list, copying each node
    // after that check if the node is also present in other levels,
    // if so, copy that as well
    while (nextToCopy->next != nullptr)
    {
        // get the element and make a node from it
        ElementType element = nextToCopy->value.getElement();
        SkipListKey<ElementType> key{SkipListKind::Normal, element};
        Node* toInsert = new Node{key, nullptr, nullptr};
        // insert to level 0 first
        insertAfter(levelsCopy[0], toInsert);
        // point the pointer to newly inserted node, so that the next node
        // insert after this one
        levelsCopy[0] = levelsCopy[0]->next;
        // check if the node is also present in other levels
        for (unsigned int i = 1; i < lvlCount; i++)
        {
            if (isElementOnLevel(element, i))
            {
                // the node is on level i, insert that into my level i
                Node* insert = new Node{key, levelsCopy[i-1], nullptr};
                insertAfter(levelsCopy[i], insert);
                levelsCopy[i] = levelsCopy[i]->next;
            }
        }
        // copy next node
        nextToCopy = nextToCopy->next;
    }
    // get rid of the temporary array
    delete[] levelsCopy;
}

template<typename ElementType>
void SkipListSet<ElementType>::insertAfter(Node* n, Node* toInsert)
{
    Node* after = n->next;
    n->next = toInsert;
    toInsert->next = after;
}


#endif // SKIPLISTSET_HPP

