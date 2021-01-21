

#ifndef GENERATE_HPP
#define GENERATE_HPP

#include "MazeGenerator.hpp"
#include <vector>


class myMazeGenerator : public MazeGenerator
{
private:
    /* data */
    void generate(
        Maze& maze, std::vector<std::pair<unsigned int, unsigned int>>& visited, 
        unsigned int row, unsigned int column);

public:
    // myMazeGenerator(/* args */);
    // ~myMazeGenerator();

    void generateMaze(Maze& maze) override;



};

// myMazeGenerator::myMazeGenerator(/* args */)
// {
// }

// myMazeGenerator::~myMazeGenerator()
// {
// }


#endif