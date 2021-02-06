// HowToExitVim.cpp
// ICS46 Winter 2021 Project 3
// Name: Keyu Zhang
// ID: 19898090
// UCINetID: keyuz4    

#include <utility>
#include <vector>

#include <ics46/factory/DynamicFactory.hpp>

#include "HowToExitVim.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, keyuz4::HowToExitVim, "How to exit Vim");


// try doing 1 level search first

std::pair<int, int> evaluation(const OthelloGameState& s)
{
    // for all valid moves
    // find the move that maximizes self score

    // find out which turn it is
    char self;
    if (s.isBlackTurn())
    {
        self = 'b';
    }
    else
    {
        self = 'w';
    }

    //vector of all valid moves
    std::vector<std::pair<int, int>> validMoves;
    for (int x = 0; x < s.board().width(); x++)
    {
        for (int y = 0; y < s.board().height(); y++)
        {
            if (s.isValidMove(x,y))
            {
                validMoves.push_back(std::make_pair(x,y));
            }
        }
    }

    int currentScore;
    if (self == 'b')
    {
        currentScore = s.blackScore();
    }
    else
    {
        currentScore = s.whiteScore();
    }
    
    std::pair<int, int> maxReturnMove;
    int maxReturn{INT32_MIN};

    for (auto move : validMoves)
    {
        std::unique_ptr<OthelloGameState> clone = s.clone();
        clone->makeMove(move.first, move.second);
        int score;
        if (self == 'b')
        {
            score = clone->blackScore() - currentScore;
        }
        else
        {
            score = clone->whiteScore() - currentScore;
        }
        if (score > maxReturn)
        {
            maxReturnMove = move;
            maxReturn = score;
        }
    }
    return maxReturnMove;
}

std::pair<int, int> search(const OthelloGameState& s, int depth)
{
    if (depth == 0)
    {
        return evaluation(s);
    }

    std::vector<std::pair<int, int>> validMoves;
    for (int x = 0; x < s.board().width(); x++)
    {
        for (int y = 0; y < s.board().height(); y++)
        {
            if (s.isValidMove(x,y))
            {
                validMoves.push_back(std::make_pair(x,y));
            }
        }
    }

    int currentScore;
    if (self == 'b')
    {
        currentScore = s.blackScore();
    }
    else
    {
        currentScore = s.whiteScore();
    }
    
    std::pair<int, int> maxReturnMove;
    int maxReturn{INT32_MIN};

    for (auto move : validMoves)
    {
        std::unique_ptr<OthelloGameState> clone = s.clone();
        clone->makeMove(move.first, move.second);
        int score;
        if (self == 'b')
        {
            score = clone->blackScore() - currentScore;
        }
        else
        {
            score = clone->whiteScore() - currentScore;
        }
        if (score > maxReturn)
        {
            maxReturnMove = move;
            maxReturn = score;
        }
    }
}

std::pair<int, int> keyuz4::HowToExitVim::chooseMove(const OthelloGameState& state)
{
    return search(state, 0);
}