#ifndef IHOPEITDOESNTGOWRONG_HPP
#define IHOPEITDOESNTGOWRONG_HPP

#include "OthelloAI.hpp"

// I hope it does not go wrong
// not for grading, just for fun :)

namespace keyuz4
{
    class HopeItDoesntGoWrong : public OthelloAI
    {
    public:
        std::pair<int, int> chooseMove(const OthelloGameState& state) override;
    };
} // namespace keyuz4

#endif
