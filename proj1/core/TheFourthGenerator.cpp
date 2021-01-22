// TheFourthGenerator.cpp
// ICS46 Winter 2021 Project 1
// Name: Keyu Zhang
// ID: 19898090
// UCINetID: keyuz4

// Generate a perfect maze with a recursive algorithm

#include <ics46/factory/DynamicFactory.hpp>

#include <random>
#include <utility>
#include <vector>

#include "Direction.hpp"
#include "Maze.hpp"
#include "MazeGenerator.hpp"
#include "TheFourthGenerator.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, TheFourthGenerator, "The 4th Generator (Required)");

namespace
{
    bool canGo(
        std::vector<std::pair<int, int>>& visitedCells, 
        std::pair<int, int> cell,
        std::pair<int, int> mazeSize)
    {
        // given a vector of visited cells, a pair of (x,y) coordinate, and
        // the size of maze; returns true if the given cell can be visited
        // i.e. not in visitedCells and a legal maze coordinate
        if (cell.first < 0 || cell.second < 0 
            || cell.first >= mazeSize.first || cell.second >= mazeSize.second)
        {
            // not a legal coordinate
            return false;
        }
        for (auto& visited: visitedCells)
        {
            if (cell == visited)
            {
                // coordinate found the visitedCells
                return false;
            }
        }
        return true;
    }

    std::vector<Direction> shuffleDirection(std::default_random_engine& engine)
    {
        // returns a shuffled vector from {Direction::left, right, up, down}
        // requires random engine as parameter to avoid using multiple engines
        std::vector<Direction> cell{
            Direction::left, Direction::right, Direction::up, Direction::down
            };
        std::shuffle(cell.begin(), cell.end(), engine);
        return cell;
    }
}

void TheFourthGenerator::generateMaze(Maze& maze)
{
    // start at 0, 0;
    // we can simply use int as coordiates because public member functions
    // in "Maze.hpp" use int, implying that size of maze will be comatiple
    // with int; it also make some conditional statments easier
    int x = 0;
    int y = 0;
    // vector that stores visited cells
    std::vector<std::pair<int, int>> visited;
    // make sure the maze is in the currect state
    maze.addAllWalls();
    // start a random device
    std::random_device device;
    std::default_random_engine engine{device()};

    generate(maze, visited, std::make_pair(x, y), engine);
}


void TheFourthGenerator::generate(
    Maze& maze, 
    std::vector<std::pair<int, int>>& visited, 
    std::pair<int, int> current, 
    std::default_random_engine& engine)
{
    // add current node to visited nodes
    visited.push_back(current);
    // gets a shuffled vector of directions
    std::vector<Direction> directions = shuffleDirection(engine);
    // iterate through the vector; make recursive calls to generate the maze
    for (auto& dir : directions)
    {
        // the adjacent coordinate that we will go next
        std::pair<int, int> adjacent = std::make_pair(current.first, current.second);
        switch (dir)
        {
        case Direction::left:
            adjacent.first--;
            break;
        case Direction::right:
            adjacent.first++;
            break;
        case Direction::up:
            adjacent.second--;
            break;
        case Direction::down:
            adjacent.second++;
            break;
        }
        // recursive call with the adjacent cell if that cell is not visited
        if (canGo(visited, adjacent, std::make_pair(maze.getWidth(), maze.getHeight())))
        {
            maze.removeWall(current.first, current.second, dir);
            generate(maze, visited, adjacent, engine);
        }
    }
}
