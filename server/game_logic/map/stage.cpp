#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include "../player/player.h"
#define FLOOR 1
#define BACKGROUND 0
#define PLAYER_SIZE 3
#define LEFT "a"
#define RIGHT "d"
#define UP "w"
#include "csv_reader.h"
#include "stage.h"
#include "../player/projectile.h"

Stage::Stage(const std::string& file_name): map(0,0){
    CSVReader reader(file_name);
    map = std::move(reader.read_map());
}

void Stage::print(){
    map.print();
}

void Stage::add_projectile(std::unique_ptr<Projectile>&& projectile) {
    projectiles.push_back(std::move(projectile));
}

void Stage::remove_projectile(std::unique_ptr<Projectile>& projectile){
    std::vector<std::unique_ptr<Projectile>>::iterator position_to_delete = 
        std::find(projectiles.begin(), projectiles.end(), projectile); // itera el vector buscando en que posicion esta projectile
    if (position_to_delete != projectiles.end()){ // si se encontro borrar, sino se encontro... no
        projectiles.erase(position_to_delete);
    }
}

void Stage::update(){
    for (auto& c : coordinates_to_delete){
        map.set(c, BACKGROUND);
    }
    coordinates_to_delete.clear();
    for (auto& projectile : projectiles){
        ray_trace(projectile);
        if (projectile == nullptr){
            return;
        }
        projectile->move();
    }
}

void Stage::draw_player(Player& player){
    Coordinate init_position = player.get_position();
    int x = init_position.x;
    int y = init_position.y;
    for (int i=0; i < PLAYER_SIZE; i++){
        for (int j=0; j < PLAYER_SIZE; j++){
            Coordinate current(x+i, y+j);
            player.occupy(current);
            map.set(current, player.get_id());
        }
    }
}

void Stage::delete_player_from_stage(Player& player){
    std::vector<Coordinate> occupied = player.get_occupied();
    for (auto& coordinate : occupied){
        map.set(coordinate, BACKGROUND);
    }
}

bool Stage::should_fall(PlayerPosition& player_position){
    Coordinate current_position = player_position.get_position();
    Coordinate duck_feet(current_position.x, current_position.y + PLAYER_SIZE);
    for (int i=0; i < PLAYER_SIZE; i ++){
        Coordinate aux(duck_feet.x + i, duck_feet.y);
        if (map.get(aux) == FLOOR){
            return false;
        }
    }
    return true;
}

bool Stage::is_valid_position(Coordinate position, int color){
    for (int i=0; i < PLAYER_SIZE; i++){
        for (int j=0; j < PLAYER_SIZE; j++){
            Coordinate aux(position.x + j, position.y + i);
            if (map.out_of_range(aux)){
                return false;
            }
            int value = map.get(aux);
            if (value != BACKGROUND && value != color){
                return false;
            }
        }
    }
    return true;
}

// direction es un versor del eje x. es decir es 1 o -1
void Stage::ray_trace(std::unique_ptr<Projectile>& projectile){
    int direction = projectile->get_direction();
    int reach = projectile->get_speed(); // cuanto tiene que moverse en un tick
    Coordinate initial_position = projectile->get_position();
    int direction_handler = direction; // para usar el mismo loop sea la direccion 1 o -1
    for (int i=0; i < reach; i ++){
        Coordinate bullet_position(initial_position.x + direction + i * direction_handler, initial_position.y);
        int next_tile = map.get(bullet_position);
        if (next_tile == -1){
            remove_projectile(projectile);
            return;
        }
        if (next_tile == BACKGROUND) {
            map.set(bullet_position, 3);
            coordinates_to_delete.push_back(bullet_position);
        /*} else if(next_tile == PLAYER){
            kill(player); */
        } else if (next_tile == FLOOR) {
            remove_projectile(projectile);
            return;
        }
    }
}
