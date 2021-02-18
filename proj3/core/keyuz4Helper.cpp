// keyuz4Helper.cpp
// ICS46 Winter 2021 Project 3
// Name: Keyu Zhang
// ID: 19898090
// UCINetID: keyuz4    

// source file for my helper functions

#include <vector>
#include <utility>

#include "keyuz4Helper.hpp"

std::vector<std::pair<int, int>> keyuz4::findAllMoves(const OthelloGameState& s)
{
    // find all valid moves
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

bool keyuz4::isSelfTurn(const OthelloGameState&s, OthelloCell self)
{
    // determine if the given game state is our turn
    if ( (self == OthelloCell::black && s.isBlackTurn()) || (self == OthelloCell::white && s.isWhiteTurn()) )
    {
        return true;
    }
    return false;
}

bool keyuz4::isCorner(const OthelloBoard& board, int x, int y)
{
    // returns whether the given cell is a corner cell
    if (x == 0 || x == board.width() - 1)
    {
        if (y == 0 || y == board.height() - 1)
        {
            return true;
        }
    }
    return false;
}

bool keyuz4::isSide(const OthelloBoard& board, int x, int y)
{
    // returns whether the given cell is a side cell
    if (x == 0 || x == board.width()-1)
    {
        if (y > 1 && y < board.height()-2)
        {
            return true;
        }
    }
    if (y == 0 || y == board.height()-1)
    {
        if (x > 1 && x < board.width()-2)
        {
            return true;
        }
    }
    return false;
}

bool keyuz4::isSideDanger(const OthelloBoard& board, int x, int y)
{
    // returns whether the given cell is a next-to-side cell
    if (x == 1 || x == board.width()-2)
    {
        if (y > 1 && y < board.height()-2)
        {
            return true;
        }
    }
    if (y == 1 || y == board.height()-2)
    {
        if (x > 1 && x < board.width()-2)
        {
            return true;
        }
    }
    return false;
}

bool keyuz4::isGreaterCorner(const OthelloBoard& board, int x, int y)
{
    // returns whether the given cell is in a 2x2 corner region
    if (x < 2 || x > board.width() - 3)
    {
        if (y < 2 || y > board.height() - 3)
        {
            return true;
        }
    }
    return false;
}

bool keyuz4::isCornerDanger(const OthelloBoard& board, int x, int y)
{
    // returns whether the given cell is a next-to-corner cell
    return (keyuz4::isGreaterCorner(board, x, y) && !keyuz4::isCorner(board, x, y));
}

double keyuz4::placementScore(const OthelloBoard& board, int x, int y)
{
    // returns how good this placement is
    // default to 1
    double score = 1;

    if (keyuz4::isCorner(board, x, y))
    {
        // corner cells are the best
        score = 100;
    }
    else if (keyuz4::isCornerDanger(board, x, y))
    {
        // cells next to corners are worst
        score = -100;
    }
    else if (keyuz4::isSide(board, x, y))
    {
        // side cells are good
        score = 50;
    }
    else if (keyuz4::isSideDanger(board, x, y))
    {
        // cells next to side cells are not good
        score = -50;
    }
    return score;
}


double keyuz4::countCorner(const OthelloGameState& s, OthelloCell self)
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
    return double(selfCorner - otherCorner) / double(selfCorner + otherCorner + 1) + 1;
}

bool keyuz4::isFrontier(const OthelloBoard& board, int x, int y)
{
    // returns whether the cell is a frontier cell
    if (board.cellAt(x,y) == OthelloCell::empty)
    {
        // empty cells does not count
        return false;
    }
    // search the 3x3 area around this cell, if any of them is empty, then
    // this cell is a frontier
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

double keyuz4::countFrontier(const OthelloBoard& board, const OthelloCell& self)
{
    // count the number of cells that is next to empty cell
    // side cells are excluded
    int myFrontier{0};
    int otherFrontier{0};
    for (int x = 1; x < board.width()-1; x++)
    {
        for (int y = 1; y < board.height()-1; y++)
        {
            if (keyuz4::isFrontier(board, x, y))
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
    return double(otherFrontier - myFrontier) / double(myFrontier + otherFrontier + 1) + 1;
}

int keyuz4::countSide(const OthelloGameState& s, const OthelloCell& self)
{
    // returns the percentage of side cells that my ai holds
    int mySide{0};
    int otherSide{0};

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
        if (cell == OthelloCell::empty)
        {
            // dont count empty cells
            continue;
        }
        else if (cell == self)
        {
            mySide++;
        }
        else
        {
            otherSide++;
        }
    }
    return double(mySide - otherSide) / double(mySide + otherSide + 1) + 1;
}

double keyuz4::scoreDifference(const OthelloGameState& s, OthelloCell self)
{
    // returns the score difference between me and opponent
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
    double score = double(myCell - opponentCell) / double(myCell + opponentCell) + 1;
    return score;
}

int keyuz4::gamePhase(const OthelloGameState& s)
{
    // returns which game phrase the game is in
    int totalCells = s.board().width() * s.board().height();
    int currentCells = s.blackScore() + s.whiteScore();
    double percentFilled = double(currentCells) / double(totalCells);

    if (percentFilled < 0.3)
    {
        // early game
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
