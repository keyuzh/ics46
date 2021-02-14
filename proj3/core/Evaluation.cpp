#include <utility>
#include <vector>
#include <iostream>

#include "Evaluation.hpp"

bool keyuz4::isSelfTurn(const OthelloGameState&s, OthelloCell self)
{
    if ( (self == OthelloCell::black && s.isBlackTurn()) || (self == OthelloCell::white && s.isWhiteTurn()) )
    {
        return true;
    }
    return false;
}

bool keyuz4::isCorner(const OthelloBoard& board, int x, int y)
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

bool keyuz4::isSide(const OthelloBoard& board, int x, int y)
{
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
    return (isGreaterCorner(board, x, y) && !isCorner(board, x, y));
}

double keyuz4::placementScore(const OthelloBoard& board, int x, int y)
{
    double score = 1;

    if (isCorner(board, x, y))
    {
        score = 10;
    }
    else if (isCornerDanger(board, x, y))
    {
        score = -100;
    }
    else if (isSide(board, x, y))
    {
        score = 50;
    }
    else if (isSideDanger(board, x, y))
    {
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
    double score = double(selfCorner - otherCorner) / double(selfCorner + otherCorner + 1);
    // std::cout << "corner score: " << score << std::endl;
    return score;
}

bool keyuz4::isFrontier(const OthelloBoard& board, int x, int y)
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

double keyuz4::countFrontier(const OthelloBoard& board, const OthelloCell& self)
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
    // std::cout << "myF" << myFrontier << std::endl;
    // std::cout << "otherF" << otherFrontier << std::endl;
    return double(otherFrontier - myFrontier) / double(myFrontier + otherFrontier + 1);
}

int keyuz4::countSide(const OthelloGameState& s)
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

bool keyuz4::isRowFull(const OthelloBoard& board, int y)
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

bool keyuz4::isColFull(const OthelloBoard& board, int x)
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

bool keyuz4::isDiagonalFull(const OthelloBoard& board, int x, int y)
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

int keyuz4::stability(const OthelloGameState& s, OthelloCell self)
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

double keyuz4::scoreDifference(const OthelloGameState& s, OthelloCell self)
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

int keyuz4::gamePhase(const OthelloGameState& s)
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