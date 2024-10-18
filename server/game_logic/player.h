#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "../../common/coordinate.h"
class Player{
private:
    Coordinate position; // La coordenada principal. Arriba a la izquierda
    bool is_alive;
    bool is_falling;
    std::vector<Coordinate> occupied; //Las coordenadas que esta ocupando
public:
    int id;
    Coordinate get_position();
    Player(Coordinate&);
    void set_position(Coordinate);
    void die();
    void fall();
    void occupy(Coordinate);
    void free_occupied();
    std::vector<Coordinate> get_occupied();
};

#endif
