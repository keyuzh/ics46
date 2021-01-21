
#include <ics46/factory/DynamicFactory.hpp>

#include "solve.hpp"
#include "MazeSolver.hpp"
#include "Maze.hpp"
#include "MazeSolution.hpp"
#include "Direction.hpp" 
#include <vector>
#include <random>
#include <utility>
#include <iostream>



ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, myMazeSolver, "display name");


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

        // switch (dir)
        // {
        // case Direction::up:
            // cant go if wall exists there or last movement is going down
        return !(maze.wallExists(x, y, dir) || fromDirection(solution, dir));

        // case Direction::down:
        //     // cant go if last movement is going up or at lowest cell
        //     if (fromDirection(solution, Direction::down) || y == solution.getHeight()-1)
        //     {
        //         return false;
        //     }
        //     break;
        
        // case Direction::left:
        //     // cant go if last movement is going right or at leftmost cell
        //     if (fromDirection(solution, Direction::left)  || x == 0)
        //     {
        //         return false;
        //     }
        //     break;
        
        // case Direction::right:
        //     // cant go if last movement is going left or at rightmost cell
        //     if (fromDirection(solution, Direction::right) || x == solution.getWidth()-1)
        //     {
        //         return false;
        //     }
        //     break;
        
        // }
        // return true;
    }
    bool solve(const Maze& maze, MazeSolution& solution)
    {
        // base case: done when got to ending cell
        if (solution.isComplete())
        {
            return true;
        }
        
        // now try going into other cells
        std::vector<Direction> directions {Direction::down, Direction::right, Direction::up, Direction::left};
        for (auto& dir : directions)
        {
            if (canGo(maze, solution, dir))
            {
                solution.extend(dir);
                if (solve(maze, solution))
                {
                    return true;
                }
                std::cout << "backing up at " << solution.getCurrentCell().first << "," << solution.getCurrentCell().second << std::endl;
                solution.backUp();
            }
        }
        std::cout << "not possible at " << solution.getCurrentCell().first << "," << solution.getCurrentCell().second << std::endl; 
        return false;
    }

}


void myMazeSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
    // std::pair start = mazeSolution.getStartingCell();
    mazeSolution.restart();
    solve(maze, mazeSolution);

}


