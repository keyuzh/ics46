#include "ArrayList.hpp"
#include <algorithm>


// move constructor
// complexity: Θ(1) - constant
//     initializing a nullptr and two int takes little time - Θ(1)
//     std::swap - Θ(1)
//     deallocating an empty ArrayList also takes little time - Θ(1)
//     result: Θ(1)
ArrayList::ArrayList(ArrayList&& a)
    : items{nullptr}, sz{0}, cap{0}
{
    std::swap(items, a.items);
    std::swap(sz, a.sz);
    std::swap(cap, a.cap);
}


// move assignment operator
// complexity: Θ(1) - constant
//     std::swap - Θ(1)
//     deallocating the current ArrayList takes some time but is still constant - Θ(1)
//     result: Θ(1)
ArrayList& ArrayList::operator=(ArrayList&& a)
{
    std::swap(items, a.items);
    std::swap(sz, a.sz);
    std::swap(cap, a.cap);
    return *this;
}
