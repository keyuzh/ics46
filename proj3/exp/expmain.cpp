// expmain.cpp
//
// ICS 46 Winter 2021
// Project #3: Black and White
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with the given classes in the othellogame library, or with your own
// algorithm implementations, outside of the context of the GUI or
// Google Test.

#include "keyuz4HowToExitVim.hpp"
#include "OthelloGameStateFactory.hpp"
#include <utility>
#include <iostream>

int main()
{
    keyuz4::HowToExitVim ai;
    std::unique_ptr<OthelloGameState> state = OthelloGameStateFactory{}.makeNewGameState(8, 8); 

    while (!state->isGameOver())
    {
        std::pair<int, int> move = ai.chooseMove(*state);
        std::cout << move.first << " " << move.second << std::endl;
        state->makeMove(move.first, move.second);
    }
    return 0;
}

