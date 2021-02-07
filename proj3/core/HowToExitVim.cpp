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

bool isTurn(const OthelloGameState&s, char self)
{
    bool turn{false};
    if ( (self == 'b' && s.isBlackTurn()) || (self == 'w' && s.isWhiteTurn()) )
    {
        turn = true;
    }
    return turn;
}

std::map<int, std::pair<int, int>> evaluation(const OthelloGameState& s, char self)
{
    // for all valid moves
    // find the move that maximizes self score or minimized opponent score
    // find out which turn it is
    bool isSelfTurn{isTurn(s, self)};

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
    int maxReturn{INT32_MAX};
    int scoreDiff;
    if (isSelfTurn)
    {
        maxReturn = INT32_MIN;
    }

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
        if (isSelfTurn && score > maxReturn)
        {
            maxReturnMove = move;
            maxReturn = score;
            scoreDiff = score;
        }
        else if (!isSelfTurn && score < maxReturn)
        {
            maxReturnMove = move;
            maxReturn = score;
            scoreDiff = score;
        }
    }
    // std::map<int, std::pair<int, int>> m {{scoreDiff, maxReturnMove}};
    // return m;
    return std::map<int, std::pair<int, int>>{{scoreDiff, maxReturnMove}};
}

std::map<int, std::pair<int, int>> search(const OthelloGameState& s, int depth, char self)
{
    if (depth == 0)
    {
        return evaluation(s, self);
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

    std::map<int, std::pair<int, int>> possibility;
    for (auto move : validMoves)
    {
        std::unique_ptr<OthelloGameState> clone = s.clone();
        clone->makeMove(move.first, move.second);
        possibility.merge(search(*clone, depth-1, self));
    }

    int maxReturn{INT32_MAX};
    bool
    if (isTurn(s, self))
    {
        maxReturn = INT32_MIN;
    }

    for (auto move : possibility)
    {
        if (move.first)
        {
            /* code */
        }
        
    }
    

}

std::pair<int, int> keyuz4::HowToExitVim::chooseMove(const OthelloGameState& state)
{
    char self{'w'};
    if (state.isBlackTurn())
    {
        self = 'b';
    }
    
    return search(state, 0, self);
}