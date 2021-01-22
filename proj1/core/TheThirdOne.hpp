// TheThirdOne.hpp
// ICS46 Winter 2021 Project 1
// Name: Keyu Zhang
// ID: 19898090
// UCINetID: keyuz4

// Solves a maze recursively

#ifndef THETHIRDONE_HPP
#define THETHIRDONE_HPP

#include <vector>

#include "MazeSolver.hpp"

class TheThirdOne : public MazeSolver
{
private:
    bool solve(const Maze& maze, MazeSolution& solution);

public:
    void solveMaze(const Maze& maze, MazeSolution& mazeSolution) override;
};

#endif
