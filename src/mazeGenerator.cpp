#include "../include/mazeGenerator.hpp"

mazeGenerator::mazeGenerator():
    rows_(0),
    cols_(0),
    obs_(0),
    maze_()
{}

mazeGenerator::~mazeGenerator()
{}

uint mazeGenerator::getRows() const
{
  return rows_;
}

uint mazeGenerator::getCols() const
{
  return cols_;
}

double mazeGenerator::getObs() const
{
    return obs_;
}

const std::vector< std::vector<bool> >& mazeGenerator::randomize(const uint rows, const uint cols, const double obs, const uint seed)
{
    rows_ = rows;
    cols_ = cols;
    obs_  = obs;

    std::srand(seed ? seed : time(NULL));

    maze_.clear();
    maze_.resize(rows, std::vector<bool>(cols, false));

    uint obs_n = obs_>1 ? 1 : rows_*cols_*obs_;

    for(uint i=0; i<obs_n ; ++i)
    {
        uint rand_i = std::rand() % rows_;
        uint rand_j = std::rand() % cols_;

        if (maze_[rand_i][rand_j])
            i--;
        else
            maze_[rand_i][rand_j] = true;
    }

    return maze_;
}

const std::vector< std::vector<bool> >& mazeGenerator::getMaze() const
{
    return maze_;
}

void mazeGenerator::show() const
{
    for (const std::vector<bool> &row : maze_)
    {
        for (bool p : row) std::cout << p;
        std::cout << std::endl;
    }
}

bool mazeGenerator::getPos(const uint row, const uint col) const
{
    return maze_[row][col];
}
