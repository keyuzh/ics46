#ifndef EVALUATION_HPP
#define EVALUATION_HPP
#include "OthelloAI.hpp"

namespace keyuz4
{
    bool isSelfTurn(const OthelloGameState&s, OthelloCell self);

    bool isCorner(const OthelloBoard& board, int x, int y);

    bool isSide(const OthelloBoard& board, int x, int y);

    bool isSideDanger(const OthelloBoard& board, int x, int y);

    bool isGreaterCorner(const OthelloBoard& board, int x, int y);

    bool isCornerDanger(const OthelloBoard& board, int x, int y);

    double placementScore(const OthelloBoard& board, int x, int y);

    double countCorner(const OthelloGameState& s, OthelloCell self);

    bool isFrontier(const OthelloBoard& board, int x, int y);

    double countFrontier(const OthelloBoard& board, const OthelloCell& self);

    int countSide(const OthelloGameState& s);

    bool isRowFull(const OthelloBoard& board, int y);

    bool isColFull(const OthelloBoard& board, int x);

    bool isDiagonalFull(const OthelloBoard& board, int x, int y);

    int stability(const OthelloGameState& s, OthelloCell self);

    double scoreDifference(const OthelloGameState& s, OthelloCell self);

    int gamePhase(const OthelloGameState& s);
} // namespace keyuz4


#endif

