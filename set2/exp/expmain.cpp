// expmain.cpp
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with the code in the "app" directory or with any additional libraries
// that are part of the project, outside of the context of the main
// application or Google Test.

#include "ArrayList.hpp"
#include <string>
#include <iostream>

namespace 
{
    template <typename T>
    void swap(T& a, T& b)
    {
        T temp = std::move(a);
        a = std::move(b);
        b = std::move(temp);
    }
} // namespace 


int main()
{
    std::cout << "building a" << std::endl;
    ArrayList a;
    std::cout << "building b" << std::endl;
    ArrayList b;
    a.add("Boo");
    std::cout << a.size() << b.size() << std::endl;

    swap(a, b);

    std::cout << a.size() << b.size() << std::endl;
    return 0;
}

