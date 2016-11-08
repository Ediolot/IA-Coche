#include "../include/player.hpp"

player::player():
    player(nullptr, nullptr)
{}

player::player(tile* position, tile *chest):
    pos_(position),
    chest_(chest),
    AStar_init_(false)
{}

player::~player()
{
    for (auto i : open_set_) delete i;
    for (auto i : closed_set_) delete i;
}

void player::setPlayer(tile* x, tile *chest)
{
    if (chest) chest_ = chest;
    move(x);

    if (pos_)   std::cout << "Player at: " << pos_->getX() << "," << pos_->getY() << std::endl; // TODO remove
    if (chest_) std::cout << "Chest at: " << chest_->getX() << "," << chest_->getY() << std::endl;
}

void player::move(tile *next_pos)
{
    if (next_pos)
    {
        if (pos_) pos_->containsPlayer(false);
        next_pos->containsPlayer(true);
        pos_=next_pos;
    }
}

uint player::AStarStep()
{
    if (pos_==chest_) return 2; // Encontrado

    /* Open list: Todas las casillas que están siendo consideradas para encontrar el camino */
    /* Closed list: Todas las casillas que no hay que reconsiderar */

    if (!AStar_init_)
    {
        AStar_init_ = true;

        insertInOpenSet(new AStarTray(pos_, chest_)); // Open list con la casilla raiz
        // Closed list vacío
    }

    if (open_set_.empty()) {
        std::cout << "AADSDA" << std::endl;
        return 1; // No hay solución
    }

    AStarTray* first = *open_set_.begin(); // Escoger la primera trayectoria (menor coste total)
    move(first->getLast());
    open_set_.erase(open_set_.begin()); // Eliminar la trayectoria de la lista abierta
    insertInClosedSet(first); // Insertar la trayectoria en la lista cerrada, en caso de que ya exista una similar, eliminar la de mayor coste

    if (pos_==chest_) {
        first->paint();
        return 2;
    }

    // Formar nuevas trayectorias
    std::vector<tile*> adyacents;
    adyacents.push_back(pos_->getFriend(dir::UP));
    adyacents.push_back(pos_->getFriend(dir::DOWN));
    adyacents.push_back(pos_->getFriend(dir::LEFT));
    adyacents.push_back(pos_->getFriend(dir::RIGHT));

    for (tile* t : adyacents)
    {
        if (!t || t->isWall()) continue; // No es una casilla válida

        insertInOpenSet(new AStarTray(first, t)); // Crea una trayectoria nueva hacia esa casilla y añádela al open set
        t->tint(al_map_rgb(255,255,255));
    }

    // TODO comprobar que se borran todas

    return 0;
}

void player::insertInOpenSet(AStarTray *t)
{
    // Comprueba si existe una trayectoria que acaba en el mismo nodo
    for (AStarTraySet_it it = open_set_.begin(); it != open_set_.end(); ++it)
    {
        if ((*it)->getLast() == t->getLast()) // Acaban en el mismo nodo
        {
            if ((*it)->fScore() > t->fScore()) // Elimina la de mayor coste
            {
                deleteFromOpenSet(it);

                // La de mínimo coste es t. Elimínala (No la insertes) si existe una similar con menor coste en la lista cerrada
                if (findInClosedSet(t) >= t->fScore())
                    open_set_.insert(t);
            }
            else if (findInClosedSet(*it) < (*it)->fScore())
            { // La de mínimo coste es it. Elimínala si existe una similar con menor coste en la lista cerrada
                deleteFromOpenSet(it);
            }
            return;
        }
    }

    // No se ha encontrado
    open_set_.insert(t);
}

void player::deleteFromOpenSet(AStarTraySet_it it)
{
    AStarTray* deleted = *it;
    open_set_.erase(it);

    double found_fScore = findInClosedSet(deleted);

    // if (found_fScore == deleted.fScore()) Hacer nada, es igual
    // if (found_fScore < deleted.fScre()) No insertar

    if (found_fScore > deleted->fScore())
        insertInClosedSet(deleted);
}

double player::findInClosedSet(const AStarTray *t) const
{
    for (const AStarTray *c : closed_set_)
        if (*c == *t) return c->fScore();

    return t->fScore();
}

void player::insertInClosedSet(AStarTray *t)
{
    // Comprueba que no exista ya una en el closed set
    for (AStarTraySet_it it = closed_set_.begin(); it != closed_set_.end(); ++it)
    {
        if (**it == *t) // Ya había una trayectoria igual
        {
            if ((*it)->fScore() > t->fScore()) // Elimina la de mayor coste
            {
                closed_set_.erase(it);
                break;
            }
        }
    }

    // No se ha encontrado
    closed_set_.insert(t);
}

void player::resetAStar(tile *p, tile *c)
{
    chest_ = c;
    pos_ = p;
    AStar_init_ = false;
    open_set_.clear();
    closed_set_.clear();
}
