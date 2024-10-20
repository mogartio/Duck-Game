#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <string>
#include <vector>
#include "../../common/coordinate.h"
#include "air_state.h"
#include "stage.h"
class Player{
private:
    Coordinate position; // La coordenada principal. Arriba a la izquierda
    std::unique_ptr<AirState> air_state;
    bool is_alive;
    std::vector<Coordinate> occupied; //Las coordenadas que esta ocupando
    void move_horizontally(int);
    void move_vertically(int);
    void move_up(int);
    void move_down(int);
    Stage& stage;
public:
    int id;
    Coordinate get_position();
    Player(Coordinate&, Stage&);
    void set_position(int x_offset, int y_offset);
    void die();
    void occupy(Coordinate);
    void free_occupied();
    std::vector<Coordinate> get_occupied();
    void move(std::string&);
    void update_air_state();
    void set_state(std::unique_ptr<AirState>);
};

#endif
