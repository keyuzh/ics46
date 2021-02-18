#include <random>
#include <vector>

#include <ics46/factory/DynamicFactory.hpp>

#include "keyuz4Helper.hpp"
#include "IHopeItDoesntGoWrong.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, keyuz4::HopeItDoesntGoWrong, ":( Segmentation fault core dumped");

namespace
{
    void RussianRoulette(std::default_random_engine eng)
    {
        // this is just for fun :)
        std::bernoulli_distribution d(0.001);
        bool result = d(eng);
        if (result)
        {
            int* a = nullptr;
            int b = a[0];
            b++;
        }
    }
} // namespace

std::pair<int, int> keyuz4::HopeItDoesntGoWrong::chooseMove(const OthelloGameState& state)
{
    std::vector<std::pair<int, int>> validMoves = keyuz4::findAllMoves(state);
    std::random_device device;
    std::default_random_engine engine{device()};
    RussianRoulette(engine);
    std::uniform_int_distribution<int> distrib(0, validMoves.size()-1);
    int index = distrib(engine);
    return validMoves.at(index);
}
