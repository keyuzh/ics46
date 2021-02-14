// HowToExitVim.cpp
// ICS46 Winter 2021 Project 3
// Name: Keyu Zhang
// ID: 19898090
// UCINetID: keyuz4    

#include <utility>
#include <vector>
#include <iostream>

#include <ics46/factory/DynamicFactory.hpp>

#include "HowToExitVim.hpp"
#include "Evaluation.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, keyuz4::HowToExitVim, "How to exit Vim");

using namespace keyuz4;

double evaluation(const OthelloGameState& s)
{
    // done
    // Corner Grab (Measures if the current player can take a corner with its next move, 
    // Weighted highly at all times.)

    // need fix
    // Stability (Measures the number of discs that cannot be flipped for the rest of the 
    // game. Weighted highly at all times.)

    // Mobility (Measures the number of moves the player is currently able to make. Has 
    // significant weight in the opening game, but diminishes to zero weight towards the endgame.)

    // Placment (piece placement score of the current player minus the piece placement 
    // score of the opponent.)

    // done
    // Frontier Discs (number of spaces adjacent to opponent pieces minus the the number 
    // of spaces adjacent to the current player's pieces.)

    // done
    // Disc difference (Measures the difference in the number of discs on the board. Has 
    // zero weight in the opening, but increases to a moderate weight in the midgame, and to 
    // a significant weight in the endgame.)

    // Parity (Measures who is expected to make the last move of the game. Has zero weight 
    // in the opening, but increases to a very large weight in the midgame and endgame.) 
    // (currently unused feature)

    double score{0};
    OthelloCell self = (s.isBlackTurn()) ? OthelloCell::black : OthelloCell::white; 
    int phase = gamePhase(s);
    switch (phase)
    {
    case 0:
        // early game
        // score += -500 * countFrontier(s.board(), self);
        score += 20 * scoreDifference(s, self);
        break;
    case 1:
        // mid game
        score += 50 * scoreDifference(s, self);
        score += 50 * countFrontier(s.board(), self);
        break;
    case 2:
        // end game
        score += 500 * scoreDifference(s, self);
        break;
    }

    score += 50 * stability(s, self);
    score += 1000 * countCorner(s, self);



    // std::cout << "evaluation: " << score << std::endl;
    return score;

}

std::vector<std::pair<int, int>> findAllMoves(const OthelloGameState& s)
{
    std::vector<std::pair<int, int>> valid;
    for (int x = 0; x < s.board().width(); x++)
    {
        for (int y = 0; y < s.board().height(); y++)
        {
            if (s.isValidMove(x,y))
            {
                valid.push_back(std::make_pair(x,y));
            }
        }
    }
    return valid;
}

struct Outcome
{
    int eval;
    int x;
    int y;
};

int boardSize(const OthelloGameState& s)
{
    return s.board().width() * s.board().height();
}

int boardSize(const OthelloBoard& b)
{
    return b.width() * b.height();
}


double search(const OthelloGameState& s, int depth, OthelloCell self)
{
    if (depth == 0)
    {
        return evaluation(s);
    }

    std::vector<std::pair<int, int>> validMoves = findAllMoves(s);
    // Outcome bestResult;
    // double bestScore = (isSelfTurn(s, self)) ? -999999999 : 9999999999;
    // bestResult.eval = (self == 'b') ? INT32_MIN : INT32_MAX;

    // bool firstIteration{true};
    double bestScore;
    if (isSelfTurn(s, self))
    {
        bestScore = -99999999;
        for (auto move : validMoves)
        {
            // find maximum
            std::unique_ptr<OthelloGameState> clone = s.clone();
            clone->makeMove(move.first, move.second);
            double result = search(*clone, depth-1, self);
            // result *= mobilityScore;
            // std::cout << result << std::endl;
            if (result > bestScore)
            {
                bestScore = result;
            }
        }
    }
    else
    {
        bestScore = 99999999;
        for (auto move : validMoves)
        {
            // find minimum
            std::unique_ptr<OthelloGameState> clone = s.clone();
            clone->makeMove(move.first, move.second);
            double result = search(*clone, depth-1, self);
            // result *= mobilityScore;
            if (result < bestScore)
            {
                bestScore = result;
            }
        }
    }
    return bestScore;
}

std::pair<int, int> keyuz4::HowToExitVim::chooseMove(const OthelloGameState& state)
{
    OthelloCell self = (state.isBlackTurn()) ? OthelloCell::black : OthelloCell::white; 

    std::vector<std::pair<int, int>> validMoves = findAllMoves(state);
    // TODO: if we can block the opponent next move
    double mobilityScore = double(validMoves.size()) / double(boardSize(state));
    double bestScore{-99999999};
    std::pair<int, int> bestMove = validMoves.at(0);
    for (auto move : validMoves)
    {
        if (isCorner(state.board(), move.first, move.second))
        {
            // if we can grab a corner, dont search the tree
            return move;
        }
        // find maximum
        std::unique_ptr<OthelloGameState> clone = state.clone();
        clone->makeMove(move.first, move.second);
        double result = search(*clone, 4, self);
        result *= mobilityScore;
        double ps = placementScore(state.board(), move.first, move.second);
        result += ps;
        std::cout << "placement score: " << ps << std::endl;
        std::cout << "result: " << result << std::endl;

        if (result > bestScore)
        {
            bestScore = result;
            bestMove = move;
        }
    }
    return bestMove;
}