#ifndef SOLVE_HPP
#define SOLVE_HPP

#include "MazeSolver.hpp"
#include <vector>


class myMazeSolver : public MazeSolver
{
private:

public:
    void solveMaze(const Maze& maze, MazeSolution& mazeSolution) override;


};

#endif