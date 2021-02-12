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

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, keyuz4::HowToExitVim, "How to exit Vim");



bool isSelfTurn(const OthelloGameState&s, OthelloCell self)
{
    if ( (self == OthelloCell::black && s.isBlackTurn()) || (self == OthelloCell::white && s.isWhiteTurn()) )
    {
        return true;
    }
    return false;
}

bool isCorner(const OthelloBoard& board, int x, int y)
{
    if (x == 0 || x == board.width() - 1)
    {
        if (y == 0 || y == board.height() - 1)
        {
            return true;
        }
    }
    return false;
}

double countCorner(const OthelloGameState& s, OthelloCell self)
{
    int selfCorner{0};
    int otherCorner{0};
    
    // find the edge of board
    int max_x{s.board().width() - 1};
    int max_y{s.board().height() - 1};

    std::vector<OthelloCell> corner {
        s.board().cellAt(0,     0), s.board().cellAt(0,     max_y),
        s.board().cellAt(max_x, 0), s.board().cellAt(max_x, max_y)
    };
    
    for (OthelloCell cell : corner)
    {
        if (cell == OthelloCell::empty)
        {
            continue;
        }
        else if (cell == self)
        {
            selfCorner++;
        }
        else
        {
            otherCorner++;
        }
    }
    // find the fraction of corners grabbed between my color and opponent
    // plus one in the end to avoid divide by zero
    double score = double(selfCorner - otherCorner) / double(selfCorner + otherCorner + 1);
    // std::cout << "corner score: " << score << std::endl;
    return score;
}

bool isFrontier(const OthelloBoard& board, int x, int y)
{
    if (board.cellAt(x,y) == OthelloCell::empty)
    {
        return false;
    }
    
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (board.isValidCell(x+i, y+j) && board.cellAt(x+i, y+j) == OthelloCell::empty)
            {
                return true;
            }
        }
    }
    return false;
}

double countFrontier(const OthelloBoard& board, const OthelloCell& self)
{
    // smaller is better
    // count the number of cells that is next to empty cell
    int myFrontier{0};
    int otherFrontier{0};
    // side cells are excluded
    for (int x = 1; x < board.width()-1; x++)
    {
        for (int y = 1; y < board.height()-1; y++)
        {
            if (isFrontier(board, x, y))
            {
                if (board.cellAt(x,y) == self)
                {
                    myFrontier++;
                }
                else
                {
                    otherFrontier++;
                }
            }
        }
    }
    std::cout << "myF" << myFrontier << std::endl;
    std::cout << "otherF" << otherFrontier << std::endl;
    return double(myFrontier - otherFrontier) / double(myFrontier + otherFrontier + 1);
}

int countSide(const OthelloGameState& s)
{
    int score{0};
    int max_x{s.board().width() - 1};
    int max_y{s.board().height() - 1};
    std::vector<OthelloCell> side;
    for (int x = 0; x <= max_x; x++)
    {
        side.push_back(s.board().cellAt(x, 0));
    }
    for (int x = 0; x <= max_x; x++)
    {
        side.push_back(s.board().cellAt(x, max_y));
    }
    for (int y = 0; y <= max_y; y++)
    {
        side.push_back(s.board().cellAt(max_x, y));
    }
    for (int y = 0; y <= max_x; y++)
    {
        side.push_back(s.board().cellAt(0, y));
    }
    
    for (OthelloCell cell : side)
    {
        switch (cell)
        {
        case OthelloCell::black:
            score++;
            break;
        case OthelloCell::white:
            score--;
            break;
        default:
            break;
        }
    }
    return score;
}

bool isRowFull(const OthelloBoard& board, int y)
{
    for (int x = 0; x < board.width(); x++)
    {
        if (board.cellAt(x, y) == OthelloCell::empty)
        {
            return false;
        }
    }
    return true;
}

bool isColFull(const OthelloBoard& board, int x)
{
    for (int y = 0; y < board.height(); y++)
    {
        if (board.cellAt(x, y) == OthelloCell::empty)
        {
            return false;
        }
    }
    return true;
}

bool isDiagonalFull(const OthelloBoard& board, int x, int y)
{
    int check = std::max({x, y, board.width() - x, board.width() - y});
    for (int i = 1; i < check; i++)
    {
        // check the four diagonals
        if (board.isValidCell(x + i, y + i) && board.cellAt(x + i, y + i) == OthelloCell::empty)
        {
            return false;
        }
        if (board.isValidCell(x + i, y - i) && board.cellAt(x + i, y - i) == OthelloCell::empty)
        {
            return false;
        }
        if (board.isValidCell(x - i, y + i) && board.cellAt(x - i, y + i) == OthelloCell::empty)
        {
            return false;
        }
        if (board.isValidCell(x - i, y - i) && board.cellAt(x - i, y - i) == OthelloCell::empty)
        {
            return false;
        }
    }
    return true;
}

int stability(const OthelloGameState& s, OthelloCell self)
{
    int stable{0};
    // cells that cannot be flipped are safe
    // first find rows (y) that is full
    std::vector<int> fullY;
    for (int row = 0; row < s.board().height(); row++)
    {
        if (isRowFull(s.board(), row))
        {
            fullY.push_back(row);
        }
    }
    // then find full col (x)
    std::vector<int> fullX;
    for (int col = 0; col < s.board().width(); col++)
    {
        if (isColFull(s.board(), col))
        {
            fullX.push_back(col);
        }
    }
    // for every (x, y) that is full, check if it is self color
    for (auto x : fullX)
    {
        for (auto y: fullY)
        {
            if (s.board().cellAt(x, y) == self && isDiagonalFull(s.board(), x, y))
            {
                stable++;
            }
        }
    }
    // std::cout << "stability score: " << stable << std::endl;
    return stable;
}

double scoreDifference(const OthelloGameState& s, OthelloCell self)
{
    int myCell;
    int opponentCell;

    if (self == OthelloCell::black)
    {
        myCell = s.blackScore();
        opponentCell = s.whiteScore();
    }
    else
    {
        myCell = s.whiteScore();
        opponentCell = s.blackScore();
    }

    // find difference in similar way as corner cells, except the number of
    // cells is guaranteed to be greater than zero
    double score = double(myCell - opponentCell) / double(myCell + opponentCell);
    // std::cout << "score: " << score << std::endl;
    return score;
}

int gamePhase(const OthelloGameState& s)
{
    int totalCells = s.board().width() * s.board().height();
    int currentCells = s.blackScore() + s.whiteScore();
    double percentFilled = double(currentCells) / double(totalCells);

    if (percentFilled < 0.3)
    {
        // early
        return 0;
    }
    if (percentFilled < 0.8)
    {
        // mid-game
        return 1;
    }
    // late game
    return 2;
}

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
        score += -5 * scoreDifference(s, self);
        break;
    case 1:
        // mid game
        score += 5 * scoreDifference(s, self);
        score += -20 * countFrontier(s.board(), self);
        break;
    case 2:
        // end game
        score += 20 * scoreDifference(s, self);
        break;
    }

    score += 10 * stability(s, self);
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
        double result = search(*clone, 0, self);
        if (result > bestScore)
        {
            bestScore = result;
            bestMove = move;
        }
    }
    // std::cout << "best score: " << bestScore << std::endl;
    // std::cout << "at " << bestMove.first << " " << bestMove.second << std::endl;
    return bestMove;
}