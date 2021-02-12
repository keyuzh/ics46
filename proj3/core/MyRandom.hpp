

#ifndef MYRANDOM_HPP
#define MYRANDOM_HPP

#include "OthelloAI.hpp"

namespace keyuz4
{
    class MyRandom : public OthelloAI
    {
    public:
        std::pair<int, int> chooseMove(const OthelloGameState& state) override;
    private:

    };
} // namespace keyuz4

#endif