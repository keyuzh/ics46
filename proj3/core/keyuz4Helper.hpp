// keyuz4Helper.hpp
// ICS46 Winter 2021 Project 3
// Name: Keyu Zhang
// ID: 19898090
// UCINetID: keyuz4    

// header file for my helper functions

#ifndef KEYUZ4_HELPER_HPP
#define KEYUZ4_HELPER_HPP

#include "OthelloAI.hpp"
#include <vector>

namespace keyuz4
{
    // find all valid moves
    std::vector<std::pair<int, int>> findAllMoves(const OthelloGameState& s);

    // determine if the given game state is our turn
    bool isSelfTurn(const OthelloGameState&s, OthelloCell self);

    // returns whether the given cell is a corner cell
    bool isCorner(const OthelloBoard& board, int x, int y);

    // returns whether the given cell is a side cell
    bool isSide(const OthelloBoard& board, int x, int y);

    // returns whether the given cell is a next-to-side cell
    bool isSideDanger(const OthelloBoard& board, int x, int y);

    // returns whether the given cell is in a 2x2 corner region
    bool isGreaterCorner(const OthelloBoard& board, int x, int y);

    // returns whether the given cell is a next-to-corner cell
    bool isCornerDanger(const OthelloBoard& board, int x, int y);

    // returns how good this placement is
    double placementScore(const OthelloBoard& board, int x, int y);

    // returns the percentage of corner cells that my side holds
    double countCorner(const OthelloGameState& s, OthelloCell self);

    // returns whether the cell is a frontier cell
    bool isFrontier(const OthelloBoard& board, int x, int y);

    // returns the percentage of frontier cells that my side holds
    double countFrontier(const OthelloBoard& board, const OthelloCell& self);

    // returns the percentage of side cells that my side holds
    int countSide(const OthelloGameState& s, const OthelloCell& self);

    // returns the score difference between me and opponent
    double scoreDifference(const OthelloGameState& s, OthelloCell self);

    // returns which game phrase the game is in
    int gamePhase(const OthelloGameState& s);
} // namespace keyuz4


#endif

