// DoublyLinkedList.hpp
//
// ICS 46 Winter 2021
// Project #2: Time Waits for No One
//
// DoublyLinkedList<ValueType> is a class template that implements a
// doubly-linked list with head and tail pointers, including two kinds
// of iterators: One of them allows viewing and modifying the list's
// contents, while the other allows only viewing them.
//
// Your goal is to implement the entire public interface *exactly* as
// specified below.  Do not modify the signatures of any of the public
// member functions (including the public member functions of the various
// iterator classes) in any way.  We will be running extensive unit
// tests against your implementation, which will not compile unless
// things remain completely unchanged.  As we did in Project #0, we've
// provided you a basic set of unit tests that briefly demonstrate how
// each of the member functions is required to behave; you'll find
// those in the "gtest" directory.
//
// All of the public member functions listed with "noexcept" in their
// signature must be implemented in a way that they never throw exceptions.
// All of the others are expected to make the "strong" exception guarantee,
// which means two things: (1) no memory has leaked, and (2) the contents
// of the list/iterator will not have visibly changed in the event that
// an exception has been thrown.
//
// The entire C++ Standard Library is off-limits in your implementation
// of this class.  DO NOT submit a version of this file (or any file
// that it includes) that includes any C++ Standard Library headers.
// (This includes things like adding a print() member function that
// requires <iostream>.)
//
// As is good custom in class templates, keep the interface separate
// from the implementation.  This means the bodies of member functions
// should not be written in the class declaration, but should appear
// below it.  I've placed "dummy" implementations of every public
// member function, though, of course, most of them don't do the
// right thing; but they will save you some typing and demonstrate
// the structure of what you should be writing.

#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP

#include "EmptyException.hpp"
#include "IteratorException.hpp"


template <typename ValueType>
class DoublyLinkedList
{
    // The forward declarations of these classes allows us to establish
    // that they exist, but delay displaying all of the details until
    // later in the file.
    //
    // (This is generally a good style, with the most important details
    // appearing earlier in the class declaration.  That's the same
    // reason why we're implementing the bodies of the member functions
    // outside of the class declaration.)
public:
    class Iterator;
    class ConstIterator;


private:
    struct Node;


public:
    // Initializes this list to be empty.
    DoublyLinkedList() noexcept;

    // Initializes this list as a copy of an existing one.
    DoublyLinkedList(const DoublyLinkedList& list);

    // Initializes this list from an expiring one.
    DoublyLinkedList(DoublyLinkedList&& list) noexcept;


    // Destroys the contents of this list.
    virtual ~DoublyLinkedList() noexcept;


    // Replaces the contents of this list with a copy of the contents
    // of an existing one.
    DoublyLinkedList& operator=(const DoublyLinkedList& list);

    // Replaces the contents of this list with the contents of an
    // expiring one.
    DoublyLinkedList& operator=(DoublyLinkedList&& list) noexcept;


    // addToStart() adds a value to the start of the list, meaning that
    // it will now be the first value, with all subsequent elements still
    // being in the list (after the new value) in the same order.
    void addToStart(const ValueType& value);

    // addToEnd() adds a value to the end of the list, meaning that
    // it will now be the last value, with all subsequent elements still
    // being in the list (before the new value) in the same order.
    void addToEnd(const ValueType& value);


    // removeFromStart() removes a value from the start of the list, meaning
    // that the list will now contain all of the values *in the same order*
    // that it did before, *except* that the first one will be gone.
    // In the event that the list is empty, an EmptyException will be thrown.
    void removeFromStart();

    // removeFromEnd() removes a value from the end of the list, meaning
    // that the list will now contain all of the values *in the same order*
    // that it did before, *except* that the last one will be gone.
    // In the event that the list is empty, an EmptyException will be thrown.
    void removeFromEnd();


    // first() returns the value at the start of the list.  In the event that
    // the list is empty, an EmptyException will be thrown.  There are two
    // variants of this member function: one for a const DoublyLinkedList and
    // another for a non-const one.
    const ValueType& first() const;
    ValueType& first();


    // last() returns the value at the end of the list.  In the event that
    // the list is empty, an EmptyException will be thrown.  There are two
    // variants of this member function: one for a const DoublyLinkedList and
    // another for a non-const one.
    const ValueType& last() const;
    ValueType& last();


    // isEmpty() returns true if the list has no values in it, false
    // otherwise.
    bool isEmpty() const noexcept;


    // size() returns the number of values in the list.
    unsigned int size() const noexcept;



    // There are two kinds of iterators supported: Iterators and
    // ConstIterators.  They have similar characteristics; they both
    // allow you to see what values are in the list and move back and
    // forth between them.  The difference is that ConstIterators allow
    // you to see the elements but not modify them, while Iterators also
    // support modification of the list (both by modifying the elements
    // directly, and also by inserting or removing values at arbitrary
    // locations).
    //
    // At any given time, an iterator refers to a value in the list.
    // There are also two additional places it can refer: "past start"
    // and "past end", which are the positions directly before the
    // first value and directly after the last one, respectively.
    // Except with respect to those boundaries, they can be moved
    // both forward and backward.
    //
    // Note, too, that the reason we have a ConstIterator class instead
    // of just saying "const Iterator" is because a "const Iterator"
    // is something different: It's an Iterator object that you can't
    // modify (i.e., you can't move it around).  What a ConstIterator
    // holds constant isn't the iterator; it's the list that's protected
    // by it.


    // iterator() creates a new Iterator over this list.  It will
    // initially be referring to the first value in the list, unless the
    // list is empty, in which case it will be considered both "past start"
    // and "past end".
    Iterator iterator();


    // constIterator() creates a new ConstIterator over this list.  It will
    // initially be referring to the first value in the list, unless the
    // list is empty, in which case it will be considered both "past start"
    // and "past end".
    ConstIterator constIterator() const;


public:
    // The IteratorBase class is the base class for our two kinds of
    // iterators.  Because there are so many similarities between them,
    // we write those similarities in a base class, then inherit from
    // that base class to specify only the differences.
    class IteratorBase
    {
    public:
        // Initializes a newly-constructed IteratorBase to operate on
        // the given list.  It will initially be referring to the first
        // value in the list, unless the list is empty, in which case
        // it will be considered to be both "past start" and "past end".
        IteratorBase(const DoublyLinkedList& list) noexcept;


        // moveToNext() moves this iterator forward to the next value in
        // the list.  If the iterator is refrering to the last value, it
        // moves to the "past end" position.  If it is already at the
        // "past end" position, an IteratorException will be thrown.
        void moveToNext();


        // moveToPrevious() moves this iterator backward to the previous
        // value in the list.  If the iterator is refrering to the first
        // value, it moves to the "past start" position.  If it is already
        // at the "past start" position, an IteratorException will be thrown.
        void moveToPrevious();


        // isPastStart() returns true if this iterator is in the "past
        // start" position, false otherwise.
        bool isPastStart() const noexcept;


        // isPastEnd() returns true if this iterator is in the "past end"
        // position, false otherwise.
        bool isPastEnd() const noexcept;
    
    protected:
        // You may want protected member variables and member functions,
        // which will be accessible to the derived classes.

        // stores whether the iterator is at pastEnd or pastStart location
        bool pastStart;
        bool pastEnd;
        // pointer to the node that the iterator is at
        Node* current;
        // pointer back to the DDL object
        const DoublyLinkedList<ValueType>* list;
    };


    class ConstIterator : public IteratorBase
    {
    public:
        // Initializes a newly-constructed ConstIterator to operate on
        // the given list.  It will initially be referring to the first
        // value in the list, unless the list is empty, in which case
        // it will be considered to be both "past start" and "past end".
        ConstIterator(const DoublyLinkedList& list) noexcept;


        // value() returns the value that the iterator is currently
        // referring to.  If the iterator is in the "past start" or
        // "past end" positions, an IteratorException will be thrown.
        const ValueType& value() const;

    private:
        // You may want private member variables and member functions.
    };


    class Iterator : public IteratorBase
    {
    public:
        // Initializes a newly-constructed Iterator to operate on the
        // given list.  It will initially be referring to the first
        // value in the list, unless the list is empty, in which case
        // it will be considered to be both "past start" and "past end".
        Iterator(DoublyLinkedList& list) noexcept;


        // value() returns the value that the iterator is currently
        // referring to.  If the iterator is in the "past start" or
        // "past end" positions, an IteratorException will be thrown.
        ValueType& value() const;


        // insertBefore() inserts a new value into the list before
        // the one to which the iterator currently refers.  If the
        // iterator is in the "past start" position, an IteratorException
        // is thrown.
        void insertBefore(const ValueType& value);


        // insertAfter() inserts a new value into the list after
        // the one to which the iterator currently refers.  If the
        // iterator is in the "past end" position, an IteratorException
        // is thrown.
        void insertAfter(const ValueType& value);


        // remove() removes the value to which this iterator refers,
        // moving the iterator to refer to either the value after it
        // (if moveToNextAfterward is true) or before it (if
        // moveToNextAfterward is false).  If the iterator is in the
        // "past start" or "past end" position, an IteratorException
        // is thrown.
        void remove(bool moveToNextAfterward = true);

    private:
        // You may want private member variables and member functions.
        DoublyLinkedList<ValueType>* list;
    };


private:
    // A structure that contains the vital parts of a Node in a
    // doubly-linked list, the value and two pointers: one pointing
    // to the previous node (or nullptr if there isn't one) and
    // one pointing to the next node (or nullptr if there isn't
    // one).
    struct Node
    {
        ValueType value;
        Node* prev;
        Node* next;
    };


    // You can feel free to add private member variables and member
    // functions here; there's a pretty good chance you'll need some.

    // pointers to the head and tail node
    Node* head;
    Node* tail;

    // size of linked list
    unsigned int sz;

    // used for copying a linked list
    struct LinkedListParameters
    {
        Node* head;
        Node* tail;
        unsigned int size;
    };

    // HELPER MEMBER FUNCTIONS
    // increment current size
    void incrementSize();
    
    // decrement current size
    void decrementSize();

    // insert a new node between the given two nodes
    void insertBetween(Node* first, Node* second, const ValueType& value);

    // remove the given node from linked list
    void remove(Node* node);

    // given a head to a linked list, delete all its nodes
    void deleteLinkedList(Node* removeHead);

    // given a head to another linked list, copy the contents from that list,
    // returns the new pointers and new sizes
    LinkedListParameters copyLinkedList(Node* otherHead);
};

namespace
{
    // implement the swap function
    template <typename T>
    void swap(T& a, T& b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

}

template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList() noexcept
    : head{nullptr}, tail{nullptr}, sz{0}
{
}


template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList(const DoublyLinkedList& list)
    : head{nullptr}, tail{nullptr}, sz{0}
{
    // copy construction
    LinkedListParameters newParam = copyLinkedList(list.head);
    head = newParam.head;
    tail = newParam.tail;
    sz = newParam.size;
}


template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList(DoublyLinkedList&& list) noexcept
    : head{nullptr}, tail{nullptr}, sz{0}
{
    // move construction
    swap(head, list.head);
    swap(tail, list.tail);
    swap(sz, list.sz);
}


template <typename ValueType>
DoublyLinkedList<ValueType>::~DoublyLinkedList() noexcept
{
    // clear();
    deleteLinkedList(head);
}


// TODO: try make a copy of new list before delete
template <typename ValueType>
DoublyLinkedList<ValueType>& DoublyLinkedList<ValueType>::operator=(const DoublyLinkedList& list)
{
    if (this != &list)
    {
        // copy first, then delete current content and update
        LinkedListParameters newParam = copyLinkedList(list.head);
        // clear();
        deleteLinkedList(head);
        head = newParam.head;
        tail = newParam.tail;
        sz = newParam.size;
    }
    return *this;
}


template <typename ValueType>
DoublyLinkedList<ValueType>& DoublyLinkedList<ValueType>::operator=(DoublyLinkedList&& list) noexcept
{
    swap(head, list.head);
    swap(tail, list.tail);
    swap(sz, list.sz);
    return *this;
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::addToStart(const ValueType& value)
{
    // create a new node
    Node* newHead = new Node;
    newHead->value = value;
    newHead->prev = nullptr;
    newHead->next = head;

    if (isEmpty())
    {
        tail = newHead;
    }
    else
    {
        // point first node's prev to new node
        head->prev = newHead;
    }
    // update head and size
    head = newHead;
    incrementSize();
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::addToEnd(const ValueType& value)
{
    Node* newTail = new Node;
    newTail->value = value;
    newTail->prev = tail;
    newTail->next = nullptr;

    if (isEmpty())
    {
        head = newTail;
    }
    else
    {
        // point last node's next to new node
        tail->next = newTail;
    }
    // update tail and size
    tail = newTail;
    incrementSize();
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::removeFromStart()
{
    if (isEmpty())
    {
        throw EmptyException{};
    }
    Node* toRemove = head;
    // point head to the second node
    head = head->next;
    if (head == nullptr)
    {
        // empty list now
        tail = nullptr;
    }
    else
    {
        head->prev = nullptr;
    }
    // delete the old node and update size
    delete toRemove;
    decrementSize();
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::removeFromEnd()
{
    if (isEmpty())
    {
        throw EmptyException{};
    }
    Node* toRemove = tail;
    // point tail to second-to-last node
    tail = tail->prev;
    if (tail == nullptr)
    {
        // empty now
        head = nullptr;
    }
    else
    {
        tail->next = nullptr;
    }
    // delete the old node and update size
    delete toRemove;
    decrementSize();
}


template <typename ValueType>
const ValueType& DoublyLinkedList<ValueType>::first() const
{
    if (isEmpty())
    {
        throw EmptyException{};
    }
    return head->value;
}


template <typename ValueType>
ValueType& DoublyLinkedList<ValueType>::first()
{
    if (isEmpty())
    {
        throw EmptyException{};
    }
    return head->value;
}


template <typename ValueType>
const ValueType& DoublyLinkedList<ValueType>::last() const
{
    if (isEmpty())
    {
        throw EmptyException{};
    }
    return tail->value;
}


template <typename ValueType>
ValueType& DoublyLinkedList<ValueType>::last()
{
    if (isEmpty())
    {
        throw EmptyException{};
    }
    return tail->value;
}


template <typename ValueType>
unsigned int DoublyLinkedList<ValueType>::size() const noexcept
{
    return sz;
}


template <typename ValueType>
bool DoublyLinkedList<ValueType>::isEmpty() const noexcept
{
    if (size() == 0)
    {
        return true;
    }
    return false;
}


template <typename ValueType>
typename DoublyLinkedList<ValueType>::Iterator DoublyLinkedList<ValueType>::iterator()
{
    return Iterator{*this};
}


template <typename ValueType>
typename DoublyLinkedList<ValueType>::ConstIterator DoublyLinkedList<ValueType>::constIterator() const
{
    return ConstIterator{*this};
}


template <typename ValueType>
DoublyLinkedList<ValueType>::IteratorBase::IteratorBase(const DoublyLinkedList& list) noexcept
    : pastStart{true}, pastEnd{true}, current{nullptr}, list{&list}
{
    if (list.isEmpty())
    {
        // if empty, what we have initialized is correct
        return;
    }
    // update member variables
    current = list.head;
    pastStart = false;
    pastEnd = false;    
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::IteratorBase::moveToNext()
{
    if (pastEnd)
    {
        // can't move to next
        throw IteratorException{};
    }
    if (pastStart)
    {
        // now moved back to head
        current = list->head;
        pastStart = false;
        return;
    }
    current = current->next;
    if (current == nullptr)
    {
        // moved past end
        pastEnd = true;
    }
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::IteratorBase::moveToPrevious()
{
    if (pastStart)
    {
        throw IteratorException{};
    }
    if (pastEnd)
    {
        // now moved back to tail
        current = list->tail;
        pastEnd = false;
        return;
    }
    current = current->prev;
    if (current == nullptr)
    {
        // passed start
        pastStart = true;
    }
}


template <typename ValueType>
bool DoublyLinkedList<ValueType>::IteratorBase::isPastStart() const noexcept
{
    return pastStart;
}


template <typename ValueType>
bool DoublyLinkedList<ValueType>::IteratorBase::isPastEnd() const noexcept
{
    return pastEnd;
}


template <typename ValueType>
DoublyLinkedList<ValueType>::ConstIterator::ConstIterator(const DoublyLinkedList& list) noexcept
    : IteratorBase{list}
{
}


template <typename ValueType>
const ValueType& DoublyLinkedList<ValueType>::ConstIterator::value() const
{
    if (this->isPastStart() || this->isPastEnd())
    {
        // cannot be past start or past end
        throw IteratorException{};
    }
    return this->current->value;
}


template <typename ValueType>
DoublyLinkedList<ValueType>::Iterator::Iterator(DoublyLinkedList& list) noexcept
    : IteratorBase{list}, list{&list}
{
}


template <typename ValueType>
ValueType& DoublyLinkedList<ValueType>::Iterator::value() const
{
    if (this->isPastStart() || this->isPastEnd())
    {
        // cannot be past start or past end
        throw IteratorException{};
    }
    return this->current->value;
}
    
template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::insertBefore(const ValueType& value)
{
    if (this->isPastStart())
    {
        throw IteratorException{};
    }
    if (this->current == list->head)
    {
        // inserting before the first value
        list->addToStart(value);
    }
    else
    {
        // insert between current node and the node before
        list->insertBetween(this->current->prev, this->current, value);
    }
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::insertAfter(const ValueType& value)
{
    if (this->isPastEnd())
    {
        throw IteratorException{};
    }
    if (this->current == list->tail)
    {
        // inserting after the last node
        list->addToEnd(value);
    }
    else
    {
        // insert between current node and the node after this
        list->insertBetween(this->current, this->current->next, value);
    }
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::remove(bool moveToNextAfterward)
{
    if (this->isPastStart() || this->isPastEnd())
    {
        throw IteratorException{};
    }
    // it may not be the best way to solve this, but moving the current pointer
    // before deleting the node can use other member functions and much easier
    // to implement
    Node* toRemove = this->current;
    if (moveToNextAfterward)
    {
        this->moveToNext();
    }
    else
    {
        this->moveToPrevious();
    }
    list->remove(toRemove);
}

// increment current size
template <typename ValueType>
void DoublyLinkedList<ValueType>::incrementSize()
{
    sz++;
}

// decrement current size
template <typename ValueType>
void DoublyLinkedList<ValueType>::decrementSize()
{
    sz--;
}

// insert a new node between the given two nodes
template <typename ValueType>
void DoublyLinkedList<ValueType>::insertBetween(Node* first, Node* second, const ValueType& value)
{
    Node* newNode = new Node;
    newNode->value = value;
    newNode->prev = first;
    newNode->next = second;

    // redirect pointers
    first->next = newNode;
    second->prev = newNode;
    incrementSize();
}

// remove the given node from linked list
template <typename ValueType>
void DoublyLinkedList<ValueType>::remove(Node* node)
{
    // if removing from head or tail, the public member functions will work
    if (head == node)
    {
        removeFromStart();
    }
    else if (tail == node)
    {
        removeFromEnd();
    }
    else
    {
        // redirect the pointers in prev and next node
        Node* prevNode = node->prev;
        Node* nextNode = node->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
        // clean up memory
        delete node;
        decrementSize();
    }
}

// deletes all nodes inside the linked list
template <typename ValueType>
void DoublyLinkedList<ValueType>::deleteLinkedList(Node* removeHead)
{
    Node* current = removeHead;
    while (current != nullptr)
    {
        Node* toRemove = current;
        current = current->next;
        delete toRemove;
    }
}

// given a head to another linked list, copy the contents from that list,
// returns the new pointers and new sizes
template <typename ValueType>
typename DoublyLinkedList<ValueType>::LinkedListParameters DoublyLinkedList<ValueType>::copyLinkedList(Node* otherHead)
{
    Node* current = otherHead;
    // initiates pointers to the new list
    Node* newHead = nullptr;
    Node* newTail = nullptr;
    unsigned int newSize = 0;
    try
    {
        // start copying
        bool firstIteration{true};
        while (current != nullptr)
        {
            ValueType newValue = current->value;

            // make a new node and copy value
            Node* newNode = new Node;
            newNode->value = newValue;
            newNode->prev = newTail;
            newNode->next = nullptr;

            if (firstIteration)
            {
                // first time, point the node as the head
                newHead = newNode;
                firstIteration = false;
            }
            else
            {
                // point last node's next to new node
                newTail->next = newNode;
            }
            // point tail to new node and adjust size
            newTail = newNode;
            current = current->next;
            newSize++;
        }
    }
    catch(...)
    {
        // if anything fails, delete everything copied so far and re throw
        deleteLinkedList(newHead);
        throw;
    }
    return LinkedListParameters{newHead, newTail, newSize};
}

#endif
