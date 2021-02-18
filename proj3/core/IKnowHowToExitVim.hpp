#ifndef KEYUZ4_IKNOWHOWTOEXITVIM_HPP
#define KEYUZ4_IKNOWHOWTOEXITVIM_HPP

#include "OthelloAI.hpp"

// This is a more straight forward type of my required ai,
// instead of doing a complex evaluation function,
// this version only cares about having corner and side cells and nothing more

namespace keyuz4
{
    class IKnowHowToExitVim : public OthelloAI
    {
    public:
        std::pair<int, int> chooseMove(const OthelloGameState& state) override;
    private:
        double evaluation(const OthelloGameState& s, const OthelloCell& self);
        double search(const OthelloGameState& s, int depth, const OthelloCell& self);
    };
} // namespace keyuz4

#endif
