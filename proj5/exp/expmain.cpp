// expmain.cpp
//
// ICS 46 Winter 2021
// Project #5: Rock and Roll Stops the Traffic
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with your code, outside of the context of the broader program or Google
// Test.

#include <iostream>
#include <queue>
using namespace std;

int main()
{

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, 
                        std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(10, 200)); 
    pq.push(std::make_pair(20, 100)); 
    pq.push(std::make_pair(15, 400)); 
    while (!pq.empty())
    {
        pair<int, int> top = pq.top(); 
        cout << top.first << " " << top.second << endl; 
        pq.pop();
    }
    
    return 0;
}

