// expmain.cpp
//
// ICS 46 Winter 2021
// Project #1: Dark at the End of the Tunnel
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with the given classes in the darkmaze library, or with your own
// algorithm implementations, outside of the context of the GUI or
// Google Test.

#include <memory>
#include "Maze.hpp"
#include "TheFourthGenerator.hpp"
#include "MazeFactory.hpp"
#include <iostream>
#include "TheThirdOne.hpp"
#include "MazeSolution.hpp"

int main()
{
    
    std::unique_ptr<Maze> maze;
    MazeFactory factory;
    maze = factory.createMaze(200, 200);

    TheFourthGenerator generator;
    generator.generateMaze(*maze);

    std::cout << "finished creation" << std::endl;

    // TheThirdOne solver;

//    solver.solveMaze(*maze, solver);

//    std::cout << "finished solving" << std::endl;

    return 0;
}

