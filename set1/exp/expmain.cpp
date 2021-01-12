// expmain.cpp
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with the code in the "app" directory or with any additional libraries
// that are part of the project, outside of the context of the main
// application or Google Test.

#include "problem3.hpp"
#include <iostream>

int main()
{
    std::vector<unsigned int> weights{1, 2, 3, 4, 5};
    std::vector<unsigned int> frequencies = countRandomFrequencies(1500000, weights);

    for (auto n : frequencies)
    {
        std::cout << n << std::endl;
    }
    
    return 0;
}

