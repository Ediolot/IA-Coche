#ifndef ASTARTRAY_HPP
#define ASTARTRAY_HPP
#include "common.hpp"
#include "tile.hpp"
#include <vector>
#include <iostream> // TODO remove

// TODO cpp file

class AStarTray {

    private:
        const AStarTray* tray_;
        tile* current_;
        tile* objective_;

        uint gScore_;

    public:
        AStarTray()
        {}

        AStarTray(tile *expand, tile* objective):
            tray_(nullptr),
            current_(expand),
            objective_(objective),
            gScore_(0)
        {}

        AStarTray(const AStarTray* t):
            tray_(t->tray_),
            current_(t->current_),
            objective_(t->objective_),
            gScore_(t->gScore_)
        {}

        AStarTray(const AStarTray* t, tile* expand):
            tray_(t),
            current_(expand),
            objective_(t->objective_),
            gScore_(t->gScore_+1)
        {}

        tile *getLast() const
        {
            return current_;
        }

        double gScore() const
        {
            return gScore_;
        }

        double hScore() const
        {
            double dx = std::abs(objective_->getX() - current_->getX());
            double dy = std::abs(objective_->getY() - current_->getY());
            return dx + dy;
        }

        double fScore() const // Costo total estimado
        {
            return gScore() + hScore();
        }

        bool operator<(const AStarTray& t2) const
        { return fScore() < t2.fScore(); }

        bool operator==(const AStarTray& t2) const
        {
            return current_ == t2.current_;
        }

        std::ostream &print(std::ostream &os = std::cout) const
        {
            // TODO
            return os;
        }

        void paint() const
        {
            current_->tint(al_map_rgb(255,0,255));
            if (tray_) tray_->paint();
        }
};

#endif
