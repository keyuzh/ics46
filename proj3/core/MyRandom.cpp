#include <utility>
#include <vector>
#include <iostream>

#include <random>
#include <ics46/factory/DynamicFactory.hpp>

#include "MyRandom.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, keyuz4::MyRandom, "Random");

namespace
{
    
std::vector<std::pair<int, int>> findAllMoves(const OthelloGameState& s)
{
    std::vector<std::pair<int, int>> valid;
    for (int x = 0; x < s.board().width(); x++)
    {
        for (int y = 0; y < s.board().height(); y++)
        {
            if (s.isValidMove(x,y))
            {
                valid.push_back(std::make_pair(x,y));
            }
        }
    }
    return valid;
}
} // namespace


std::pair<int, int> keyuz4::MyRandom::chooseMove(const OthelloGameState& state)
{
    std::random_device device;

    std::default_random_engine engine{device()};

    std::vector<std::pair<int, int>> validMoves = findAllMoves(state);

    std::uniform_int_distribution<int> distrib(0, validMoves.size()-1);

    int index = distrib(engine);
    return validMoves.at(index);
}