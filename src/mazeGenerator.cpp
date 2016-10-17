#include "../include/mazeGenerator.hpp"

mazeGenerator::mazeGenerator():
    data_(0),
    rows_(0),
    cols_(0)
{};

mazeGenerator::~mazeGenerator()
{}

void mazeGenerator::randomize(const uint rows, const uint cols, const double obst, const uint seed)
{
    std::srand(seed==0 ? std::time(nullptr) : seed);
    rows_ = rows;
    cols_ = cols;
    uint obst_n = rows*cols*obst;

    data_.clear();
    data_.resize(rows*cols, false);

    for (uint i=0; i<obst_n; ++i)
    {
        uint pos;
        do
            pos = (std::rand() / double(RAND_MAX)) * double(rows_*cols_);
        while (data_[pos]);
        data_[pos] = true;
    }
}

bool mazeGenerator::getPos(const uint row, const uint col) const
{
    return data_[row*cols_ + col];
}
