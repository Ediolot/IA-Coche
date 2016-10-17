#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "common.hpp"

class mazeGenerator {

   private:
        int rows_;
        int cols_;
        double obs_;
        std::vector< std::vector<bool> > maze_;

    public:
        mazeGenerator();
        virtual ~mazeGenerator();

        uint getRows() const;
        uint getCols() const;
        double getObs() const;

        const std::vector< std::vector<bool> >& getMaze() const;
        const std::vector< std::vector<bool> >& randomize(const uint rows, const uint cols, const double obs, const uint seed=0);

        bool getPos(const uint row, const uint col) const;
        void show() const;
};

#endif
