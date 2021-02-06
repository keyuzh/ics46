// HowToExitVim.hpp
// ICS46 Winter 2021 Project 3
// Name: Keyu Zhang
// ID: 19898090
// UCINetID: keyuz4    

#include "OthelloAI.hpp"

namespace keyuz4
{
    class HowToExitVim : public OthelloAI
    {
    public:
        std::pair<int, int> chooseMove(const OthelloGameState& state) override;
    private:

    };
} // namespace keyuz4
