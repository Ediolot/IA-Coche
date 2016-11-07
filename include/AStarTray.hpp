#ifndef ASTARTRAY_HPP
#define ASTARTRAY_HPP
#include "common.hpp"
#include "tile.hpp"
#include <vector>
#include <iostream> // TODO remove

// TODO cpp file

class AStarTray {

    private:
        std::vector<tile*> tray_;
        tile* objective_;

    public:
        AStarTray()
        {}

        AStarTray(tile *expand, tile* objective):
            objective_(objective)
        {
            tray_.push_back(expand);
        }

        AStarTray(const AStarTray& t):
            tray_(t.tray_),
            objective_(t.objective_)
        {}

        AStarTray(const AStarTray& t, tile* expand):
            tray_(t.tray_),
            objective_(t.objective_)
        {
            tray_.push_back(expand);
        }

        tile *getLast() const
        {
            return tray_.back();
        }

        double gScore() const
        {
            return tray_.size();
        }

        double hScore() const
        {
            double dx = std::abs(objective_->getX() - tray_.back()->getX());
            double dy = std::abs(objective_->getY() - tray_.back()->getY());
            return dx + dy;
        }

        double fScore() const // Costo total estimado
        {
            return gScore() + hScore();
        }

        bool operator<(const AStarTray& t2) const
        { return fScore() < t2.fScore(); }

        bool operator==(const AStarTray& t2) const
        { return tray_ == t2.tray_; }

        std::ostream &print(std::ostream &os = std::cout) const
        {
            for (tile* t : tray_)
                std::cout << "(" << t->getX() << "," << t->getY() << ")";
            std::cout << "[" << gScore() << "," << hScore() << "]" << std::endl;
            return os;
        }
};

#endif
