// TheFourthGenerator.hpp
// ICS46 Winter 2021 Project 1
// Name: Keyu Zhang
// ID: 19898090
// UCINetID: keyuz4

// Generate a perfect maze with a recursive algorithm

#ifndef THEFOURTHGENERATOR_HPP 
#define THEFOURTHGENERATOR_HPP

#include <random>
#include <vector>

#include "MazeGenerator.hpp"

class TheFourthGenerator : public MazeGenerator
{
private:
    void generate(
        Maze& maze, std::vector<std::pair<int, int>>& visited, 
        std::pair<int, int> currentCell, std::default_random_engine& engine);

public:
    void generateMaze(Maze& maze) override;
};

#endif
