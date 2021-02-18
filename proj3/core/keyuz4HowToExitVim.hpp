// keyuz4HowToExitVim.hpp
// ICS46 Winter 2021 Project 3
// Name: Keyu Zhang
// ID: 19898090
// UCINetID: keyuz4    

// header for the required othello ai for this project

#ifndef KEYUZ4_HOWTOEXITVIM_HPP
#define KEYUZ4_HOWTOEXITVIM_HPP

#include "OthelloAI.hpp"

namespace keyuz4
{
    class HowToExitVim : public OthelloAI
    {
    public:
        // the required choose move function
        std::pair<int, int> chooseMove(const OthelloGameState& state) override;
    private:
        // evaluates current board
        double evaluation(const OthelloGameState& s, const OthelloCell& self);

        // heuristic search
        double search(const OthelloGameState& s, int depth, const OthelloCell& self);
    };
} // namespace keyuz4

#endif
