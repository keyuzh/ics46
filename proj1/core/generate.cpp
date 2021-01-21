
#include <ics46/factory/DynamicFactory.hpp>


#include "MazeGenerator.hpp"
#include "generate.hpp"
#include "Direction.hpp"
#include "Maze.hpp"

#include <vector>
#include <random>
#include <utility>
#include <iostream>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, myMazeGenerator, "display name");

namespace
{
    bool isVisited(
        std::vector<std::pair<unsigned int, unsigned int>>& visitedNodes, 
        unsigned int x, unsigned int y)
    {
        for (auto& node : visitedNodes)
        {
            if (x == node.first && y == node.second)
            {
                return true;
            }
        }
        return false;
    }

    std::vector<int> shuffleNodes()
    {
        // returns a shuffled vector from {1,2,3,4}
        std::random_device device;
        std::default_random_engine engine{device()};
        std::vector<int> nodes{1,2,3,4};
        std::shuffle(nodes.begin(), nodes.end(), engine);
        return nodes;
    }


}

void myMazeGenerator::generateMaze(Maze& maze)
{
    // start at 0, 0
    unsigned int startRow = 0;
    unsigned int startCol = 0;
    // vector that stores visited cells
    std::vector<std::pair<unsigned int, unsigned int>> visited;
    // since the maze starts empty
    maze.addAllWalls();
    generate(maze, visited, startRow, startCol);

}


void myMazeGenerator::generate(
    Maze& maze, std::vector<std::pair<unsigned int, unsigned int>>& visited, 
    unsigned int x, unsigned int y)
{
    // Base case: if current node is visited do nothing
    // if (isVisited(visited, x, y))
    // {
    //     std::cout << "visited node on " << x << "," << y << std::endl;
    //     return;
    // }

    // add current node to visited nodes
    visited.push_back(std::make_pair(x, y));
    // gets a shuffled vector of adjacent cells
    std::vector<int> adjacent = shuffleNodes();

    for (auto& node : adjacent)
    {
        switch (node)
        {
        case 1: // left
            if (x != 0 && (isVisited(visited, x-1, y)==false) )
            {
                std::cout << "removing left of " << x << "," << y << std::endl;
                maze.removeWall(x, y, Direction::left);
                generate(maze, visited, x-1, y);
            }
            break;
        case 2: // right
            if ((x != maze.getWidth()-1) && (isVisited(visited, x+1, y)==false) )
            {
                std::cout << "removing right of " << x << "," << y << std::endl;
                maze.removeWall(x, y, Direction::right);
                generate(maze, visited, x+1, y);
            }
            break;
        case 3: // up
            if (y != 0 && (isVisited(visited, x, y-1)==false) )
            {
                std::cout << "removing up of " << x << "," << y << std::endl;
                maze.removeWall(x, y, Direction::up);
                generate(maze, visited, x, y-1);
            }
            break;
        case 4: // down
            if ((y != maze.getHeight()-1) && (isVisited(visited, x, y+1)==false) )
            {
                std::cout << "removing down of " << x << "," << y << std::endl;
                maze.removeWall(x, y, Direction::down);
                generate(maze, visited, x, y+1);
            }
            break;
        default:
            break;
        }
    }
}

