#include <random>
#include <utility>
#include <vector>

#include <ics46/factory/DynamicFactory.hpp>

#include "keyuz4Helper.hpp"
#include "MostlyRandom.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, keyuz4::MostlyRandom, "github.com/hakluke/how-to-exit-vim");

std::pair<int, int> keyuz4::MostlyRandom::chooseMove(const OthelloGameState& state)
{
    std::vector<std::pair<int, int>> validMoves = keyuz4::findAllMoves(state);
    if (validMoves.size() == 0)
    {
        // this should not happen normally
        // since this method won't be called when there is no valid moves
        return std::make_pair(0,0);
    }
    // corners are important
    for (auto move : validMoves)
    {
        if (keyuz4::isCorner(state.board(), move.first, move.second))
        {
            // killer move: grab corner
            return move;
        }
    }
    // otherwise choose whatever
    std::random_device device;
    std::default_random_engine engine{device()};
    std::uniform_int_distribution<int> distrib(0, validMoves.size()-1);
    int index = distrib(engine);
    return validMoves.at(index);
}
