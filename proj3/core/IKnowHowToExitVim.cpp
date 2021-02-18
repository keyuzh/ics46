#include <utility>
#include <vector>

#include <ics46/factory/DynamicFactory.hpp>

#include "keyuz4Helper.hpp"
#include "IKnowHowToExitVim.hpp"

using keyuz4::IKnowHowToExitVim;

// answer to my required ai :)
ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, keyuz4::IKnowHowToExitVim, ":!grep -P \"PPid:\\t(\\d+)\" /proc/$$/status | cut -f2 | xargs kill -9");

double keyuz4::IKnowHowToExitVim::evaluation(const OthelloGameState& s, const OthelloCell& self)
{
    double score{0};
    score += 1000 * keyuz4::countCorner(s, self);
    score += 200  * keyuz4::countSide(s, self);
    return score;
}


double keyuz4::IKnowHowToExitVim::search(const OthelloGameState& s, int depth, const OthelloCell& self)
{
    // search depth reached, evaluate current game board
    if (depth == 0)
    {
        return evaluation(s, self);
    }
    std::vector<std::pair<int, int>> validMoves = keyuz4::findAllMoves(s);
    double bestScore;

    if (keyuz4::isSelfTurn(s, self))
    {
        // need to find maximum, so initialize to an arbitary small number
        bestScore = -99999999;
        for (auto move : validMoves)
        {
            std::unique_ptr<OthelloGameState> clone = s.clone();
            clone->makeMove(move.first, move.second);

            double result = search(*clone, depth-1, self);
            if (result > bestScore)
            {
                bestScore = result;
            }
        }
    }
    else
    {
        // need to find minimum, so initialize to an arbitary large number
        bestScore = 99999999;
        for (auto move : validMoves)
        {
            std::unique_ptr<OthelloGameState> clone = s.clone();
            clone->makeMove(move.first, move.second);

            double result = search(*clone, depth-1, self);
            if (result < bestScore)
            {
                bestScore = result;
            }
        }
    }
    return bestScore;
}


std::pair<int, int> keyuz4::IKnowHowToExitVim::chooseMove(const OthelloGameState& state)
{
    // initiates variables
    OthelloCell self = (state.isBlackTurn()) ? OthelloCell::black : OthelloCell::white; 
    std::vector<std::pair<int, int>> validMoves = keyuz4::findAllMoves(state);

    if (validMoves.size() == 0)
    {
        // this should not happen normally
        // since this method won't be called when there is no valid moves
        return std::make_pair(0,0);
    }
    // initialize as some super small number
    double bestScore{-99999999};
    std::pair<int, int> bestMove = validMoves.at(0);

    for (auto move : validMoves)
    {
        if (keyuz4::isCorner(state.board(), move.first, move.second))
        {
            // killer move: grab corner
            return move;
        }
        std::unique_ptr<OthelloGameState> clone = state.clone();
        clone->makeMove(move.first, move.second);

        if (keyuz4::isSelfTurn(*clone, self))
        {
            // killer move: block the opponent
            return move;
        }
        // search the game tree
        double result = search(*clone, 3, self);
        // find maximum here
        if (result > bestScore)
        {
            bestScore = result;
            bestMove = move;
        }
    }
    return bestMove;
}
