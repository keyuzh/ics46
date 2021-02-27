// AVLSet.hpp
//
// ICS 46 Winter 2021
// Project #4: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.  The balancing is actually optional,
// with a bool parameter able to be passed to the constructor to explicitly
// turn the balancing on or off (on is default).  If the balancing is off,
// the AVL tree acts like a binary search tree (e.g., it will become
// degenerate if elements are added in ascending order).
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector) to store the information
// in your data structure.  Instead, you'll need to implement your AVL tree
// using your own dynamically-allocated nodes, with pointers connecting them,
// and with your own balancing algorithms used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include <algorithm>
#include <functional>
#include "Set.hpp"



template <typename ElementType>
class AVLSet : public Set<ElementType>
{
public:
    // A VisitFunction is a function that takes a reference to a const
    // ElementType and returns no value.
    using VisitFunction = std::function<void(const ElementType&)>;

public:
    // Initializes an AVLSet to be empty, with or without balancing.
    explicit AVLSet(bool shouldBalance = true);

    // Cleans up the AVLSet so that it leaks no memory.
    ~AVLSet() noexcept override;

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Initializes a new AVLSet whose contents are moved from an
    // expiring one.
    AVLSet(AVLSet&& s) noexcept;

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);

    // Assigns an expiring AVLSet into another.
    AVLSet& operator=(AVLSet&& s) noexcept;


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    bool isImplemented() const noexcept override;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    void add(const ElementType& element) override;


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    bool contains(const ElementType& element) const override;


    // size() returns the number of elements in the set.
    unsigned int size() const noexcept override;


    // height() returns the height of the AVL tree.  Note that, by definition,
    // the height of an empty tree is -1.
    int height() const noexcept;


    // preorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by a preorder traversal of the AVL
    // tree.
    void preorder(VisitFunction visit) const;


    // inorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by an inorder traversal of the AVL
    // tree.
    void inorder(VisitFunction visit) const;


    // postorder() calls the given "visit" function for each of the elements
    // in the set, in the order determined by a postorder traversal of the AVL
    // tree.
    void postorder(VisitFunction visit) const;


private:
    // You'll no doubt want to add member variables and "helper" member
    // functions here.
    struct Node
    {
        ElementType value;
        Node* left;
        Node* right;
        int height; // height of subtree
    };
    Node* root;
    bool shouldBalance;
    
private:
    // recursively search the tree
    bool containsR(Node* n, const ElementType& target) const;
    // find the height of given node recursively
    int findHeightR(Node* n) const;
    // returns the height stored in the node
    int findHeight(Node* n) const;
    // recalculate the height of a given node after rotation
    int reFindHeight(Node* n) const;
    // recursively find the size of the tree
    unsigned int findSizeR(Node* n) const;
    // add a node to the tree
    void addR(Node*& n, const ElementType& element);
    // insert a node at the given position
    void insert(Node*& n, const ElementType& element);
    // recursive preorder traversal
    void preorderR(Node* n, VisitFunction visit) const;
    // recursive inorder traversal
    void inorderR(Node* n, VisitFunction visit) const;
    // recursive postorder traversal
    void postorderR(Node* n, VisitFunction visit) const;
    // recursively determine if the tree is valid AVL tree
    bool isBalancedR(Node* n) const;
    // returns the difference in height of left and right subtree
    int getHeightDiff(Node* n) const;
    // rebalance at given node
    void rebalance(Node*& n, const ElementType& element);
    // make a LL rotation at given root, returns the new root
    Node* rotateLL(Node* n);
    // make a RR rotation at given root, returns the new root
    Node* rotateRR(Node* n);
    // deletes all nodes in the tree
    void clear(Node* n);
    // recursively copy the other AVL tree
    void copyR(Node*& self, const Node* other);
public:
    // returns whether the tree is a valid AVL tree
    bool isBalanced() const;
};


template <typename ElementType>
AVLSet<ElementType>::AVLSet(bool shouldBalance)
    : root{nullptr}, shouldBalance{shouldBalance}
{
}


template <typename ElementType>
AVLSet<ElementType>::~AVLSet() noexcept
{
    clear(root);
}


template <typename ElementType>
AVLSet<ElementType>::AVLSet(const AVLSet& s)
    : root{nullptr}, shouldBalance{s.shouldBalance}
{
    // copy the nodes
    copyR(root, s.root);
}


template <typename ElementType>
AVLSet<ElementType>::AVLSet(AVLSet&& s) noexcept
    : root{nullptr}, shouldBalance{false}
{
    std::swap(root, s.root);
    std::swap(shouldBalance, s.shouldBalance);
}


template <typename ElementType>
AVLSet<ElementType>& AVLSet<ElementType>::operator=(const AVLSet& s)
{
    if (this != &s)
    {
        Node* nRoot{nullptr};
        bool nShouldBalance = s.shouldBalance;
        copyR(nRoot, s.root);
        clear(root);
        root = nRoot;
        shouldBalance = nShouldBalance;
    }
    return *this;
}


template <typename ElementType>
AVLSet<ElementType>& AVLSet<ElementType>::operator=(AVLSet&& s) noexcept
{
    if (this != &s)
    {
        std::swap(root, s.root);
        std::swap(shouldBalance, s.shouldBalance);
    }
    return *this;
}


template <typename ElementType>
bool AVLSet<ElementType>::isImplemented() const noexcept
{
    return true;
}


template <typename ElementType>
void AVLSet<ElementType>::add(const ElementType& element)
{
    addR(root, element);
}


template <typename ElementType>
bool AVLSet<ElementType>::contains(const ElementType& element) const
{
    return containsR(root, element);
}


template <typename ElementType>
unsigned int AVLSet<ElementType>::size() const noexcept
{
    
    return findSizeR(root);
}


template <typename ElementType>
int AVLSet<ElementType>::height() const noexcept
{
    return findHeight(root);
}


template <typename ElementType>
void AVLSet<ElementType>::preorder(VisitFunction visit) const
{
    preorderR(root, visit);
}


template <typename ElementType>
void AVLSet<ElementType>::inorder(VisitFunction visit) const
{
    inorderR(root, visit);
}


template <typename ElementType>
void AVLSet<ElementType>::postorder(VisitFunction visit) const
{
    postorderR(root, visit);
}

template <typename ElementType>
bool AVLSet<ElementType>::containsR(Node* n, const ElementType& target) const
{
    if (n == nullptr)
    {
        // searched to a leaf node, the element does not exist
        return false;
    }
    if (n->value == target)
    {
        // found
        return true;
    }
    if (n->value < target)
    {
        // go right
        return containsR(n->right, target);
    }
    // go left
    return containsR(n->left, target);
}

template <typename ElementType>
int AVLSet<ElementType>::findHeightR(Node* n) const
{
    if (n == nullptr)
    {
        // empty tree
        return -1;
    }
    return 1 + std::max(findHeightR(n->left), findHeightR(n->right));
}

template <typename ElementType>
int AVLSet<ElementType>::findHeight(Node* n) const
{
    if (n == nullptr)
    {
        return -1;
    }
    // use the stored value
    return n->height;
}

template <typename ElementType>
int AVLSet<ElementType>::reFindHeight(Node* n) const
{
    return 1 + std::max(findHeight(n->left), findHeight(n->right));
}

template <typename ElementType>
unsigned int AVLSet<ElementType>::findSizeR(Node* n) const
{
    if (n == nullptr)
    {
        // leaf node
        return 0;
    }
    return 1 + findSizeR(n->left) + findSizeR(n->right);
}

template <typename ElementType>
void AVLSet<ElementType>::addR(Node*& n, const ElementType& element)
{
    if (n == nullptr)
    {
        insert(n, element);
        // added as leaf node, no need to update height or balance
        return;
    }
    else if (n->value == element)
    {
        // already contains the node, do nothing
        return;
    }
    else if (n->value < element)
    {
        // search right subtree
        addR(n->right, element);
    }
    else 
    {
        // search left subtree
        addR(n->left, element);
    }
    // update height of current node
    n->height = reFindHeight(n);
    if (shouldBalance)
    {
        // do rotations if needed
        rebalance(n, element);
    }
}

template <typename ElementType>
void AVLSet<ElementType>::rebalance(Node*& n, const ElementType& element)
{
    // find the difference in left and right subtree to determine
    // if we need to do re-balancing
    int heightDiff = getHeightDiff(n);
    // left subtree has greater height than right, meaning we need to do L* rotation
    if (heightDiff > 1)
    {
        // element smaller than left subtree value, meaning the element is inserted
        // at left of left subtree -> LL rotation
        if (element < n->left->value)
        {
            n = rotateLL(n);
        }
        // inserted at right of left subtree -> LR rotation
        else if (element > n->left->value)
        {
            // LR rotation is equivalent to a RR rotation at left node,
            // then LL rotation at current node
            n->left = rotateRR(n->left);
            n = rotateLL(n);
        }
    }
    // right subtree has greater height than left, meaning we need to do R* rotation
    else if (heightDiff < -1)
    {
        // greater than right subtree, inserted right of right
        // RR rotation
        if (element > n->right->value)
        {
            n = rotateRR(n);
        }
        // inserted at left of right subtree -> RL rotation
        else if (element < n->right->value)
        {
            // RL rotation is equivalent to a LL rotation at right node,
            // then RR rotation at current node
            n->right = rotateLL(n->right);
            n = rotateRR(n);
        }
    }
}

template <typename ElementType>
void AVLSet<ElementType>::insert(Node*& n, const ElementType& element)
{
    Node* toInsert = new Node{element, nullptr, nullptr, 0};
    n = toInsert;
}

template <typename ElementType>
void AVLSet<ElementType>::preorderR(Node* n, VisitFunction visit) const
{
    if (n == nullptr)
    {
        return;
    }
    // preorder: visit first, then left and right
    visit(n->value);
    preorderR(n->left, visit);
    preorderR(n->right, visit);
}

template <typename ElementType>
void AVLSet<ElementType>::inorderR(Node* n, VisitFunction visit) const
{
    if (n == nullptr)
    {
        return;
    }
    // inorder: left, visit, right
    inorderR(n->left, visit);
    visit(n->value);
    inorderR(n->right, visit);
}

template <typename ElementType>
void AVLSet<ElementType>::postorderR(Node* n, VisitFunction visit) const
{
    if (n == nullptr)
    {
        return;
    }
    // postorder: left, right, visit
    postorderR(n->left, visit);
    postorderR(n->right, visit);
    visit(n->value);
}

template <typename ElementType>
bool AVLSet<ElementType>::isBalanced() const
{
    return isBalancedR(root);
}

template <typename ElementType>
bool AVLSet<ElementType>::isBalancedR(Node* n) const
{
    if (n == nullptr)
    {
        return true;
    }
    int heightDiff = getHeightDiff(n);
    // difference in left and right subtree height must between -1 and 1
    // and each subtree need to have the same property
    return (-1 <= heightDiff) && (heightDiff <= 1) && isBalancedR(n->left) && isBalancedR(n->right);
}

template <typename ElementType>
int AVLSet<ElementType>::getHeightDiff(Node* n) const
{
    return findHeight(n->left) - findHeight(n->right);
}

template <typename ElementType>
typename AVLSet<ElementType>::Node* AVLSet<ElementType>::rotateLL(Node* n)
{
    // diagram is in the lecture notes
    // A is the left subtree of n
    Node* a = n->left;
    // T2 subtree is the right subtree of A
    Node* t2 = a->right;
    a->right = n;
    n->left = t2;
    // update height in moved nodes (a and n)
    // the T nodes has the same height as before
    n->height = reFindHeight(n);
    a->height = reFindHeight(a);
    // return new root node
    return a;
}

template <typename ElementType>
typename AVLSet<ElementType>::Node* AVLSet<ElementType>::rotateRR(Node* n)
{
    // diagram is in the lecture notes
    // B is the right subtree of n
    Node* b = n->right;
    // T2 subtree is the left subtree of B
    Node* t2 = b->left;
    b->left = n;
    n->right = t2;
    // update height in moved nodes (b and n)
    // the T nodes has the same height as before
    n->height = reFindHeight(n);
    b->height = reFindHeight(b);
    // return new root node
    return b;
}

template <typename ElementType>
void AVLSet<ElementType>::clear(Node* n)
{
    if (n == nullptr)
    {
        return;
    }
    // delete child node first, so we dont need to preserve pointers
    clear(n->left);
    clear(n->right);
    delete n;
}

template <typename ElementType>
void AVLSet<ElementType>::copyR(Node*& self, const Node* other)
{
    if (other == nullptr)
    {
        // end of a branch
        self = nullptr;
        return;
    }
    // make a new node
    Node* n = new Node{other->value, nullptr, nullptr, other->height};
    // updpate left and right pointer
    copyR(n->left, other->left);
    copyR(n->right, other->right);
    self = n;
}

#endif // AVLSET_HPP

