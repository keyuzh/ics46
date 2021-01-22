// TheThirdOne.cpp
// ICS46 Winter 2021 Project 1
// Name: Keyu Zhang
// ID: 19898090
// UCINetID: keyuz4

// Solves a maze recursively

#include <ics46/factory/DynamicFactory.hpp>

#include <random>
#include <utility>
#include <vector>

#include "Direction.hpp" 
#include "Maze.hpp"
#include "MazeSolution.hpp"
#include "MazeSolver.hpp"
#include "TheThirdOne.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, TheThirdOne, "The 3rd One (Required)");

namespace
{
    bool fromDirection(const MazeSolution& solution, const Direction& dir)
    {
        // returns true if the previous movement comes from the direction
        // example: current cell is (1,1), previous cell is (1,0);
        // we are coming from (1,0) and last movement is DOWN,
        // then calling this function with Direction::up returns true
        const std::vector<Direction>& movements = solution.getMovements();
        if (movements.size() == 0)
        {
            return false;
        }

        switch (dir)
        {
        case Direction::up:
            // true if previous movement is down
            return (solution.getMovements().back() == Direction::down);

        case Direction::down:
            return (solution.getMovements().back() == Direction::up);
        
        case Direction::left:
            return (solution.getMovements().back() == Direction::right);
        
        case Direction::right:
            return (solution.getMovements().back() == Direction::left);
        }
    }


    bool canGo(const Maze& maze, const MazeSolution& solution, Direction dir)
    {
        int x = solution.getCurrentCell().first;
        int y = solution.getCurrentCell().second;

        return !(maze.wallExists(x, y, dir) || fromDirection(solution, dir));
    }
}


void TheThirdOne::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
    // clear the current solution (if any) first
    mazeSolution.restart();
    solve(maze, mazeSolution);
}


bool TheThirdOne::solve(const Maze& maze, MazeSolution& solution)
{
    // base case: done when got to ending cell
    if (solution.isComplete())
    {
        return true;
    }
    
    // The order of vector is important here since the ending cell will
    // most likely be at the bottom right
    std::vector<Direction> directions{
        Direction::down, Direction::right, Direction::up, Direction::left};

    for (auto& dir : directions)
    {
        if (canGo(maze, solution, dir))
        {
            solution.extend(dir);
            if (solve(maze, solution))
            {
                // found a solution, clear the recursive call stack by return
                return true;
            }
            // otherwise backup and try other routes
            solution.backUp();
        }
    }
    // not possible from this cell, backup further
    return false;
}
