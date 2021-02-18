#ifndef MOSTLYRANDOM_HPP
#define MOSTLYRANDOM_HPP

#include "OthelloAI.hpp"

// this AI only cares about corners, otherwise it is mostly random

namespace keyuz4
{
    class MostlyRandom : public OthelloAI
    {
    public:
        std::pair<int, int> chooseMove(const OthelloGameState& state) override;
    };
} // namespace keyuz4

#endif
