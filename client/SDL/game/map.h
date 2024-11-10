#include "../../../common/queue.h"
#include "player.h"

#include <list>
#include <SDL2/SDL_render.h>

class Map {
private:

    SDL_Renderer* rend;
    // mapa que entra por parametro para ser dibujado
    std::vector<uint16_t> mapa;

    // Imagenes de los tiles
    std::vector<Image*> tilesImages;
    // Posiciones de los tiles
    std::unordered_map<Image*, std::vector<std::pair<int, int>>> tilesPlace;

    // Jugadores
    std::unordered_map<std::string, Player*> players;

    // Imagenes de las armas
    // std::vector<Image*> weapons;
    std::unordered_map<Weapon, Image*> weapons;
    // Posiciones de las armas
    std::unordered_map<Weapon, std::vector<std::pair<int, int>>> weaponsMap;

    // Imagenes de los cascos usables
    std::vector<Image*> helmets;
    // Posiciones de los cascos en el mapa
    std::unordered_map<Image*, std::vector<std::pair<int, int>>> helmetsMap;
    
    // Imagen de armadura usable
    Image armor;
    Image hombro;
    // Imagen de armadura en el mapa
    Image armorOnMap;
    // Posiciones de la armadura
    std::vector<std::pair<int, int>> armorMap;

    Image background;

    void makeTile(TileType tileType);
    void makeWeapon(Weapon weapon);
    void makeHelmet(Helemts helmet);

public:
    Map(SDL_Renderer* rend, std::vector<uint16_t> mapa);

    void makeMap(int w, int h);

    void addPlayer(int columnaActual, int filaActual, int color, std::string name);

    // Actualiza posicion y estado del jugador
    void update(std::string player, int x, int y, DuckState state, Side side);

    // Agrega un nuevo arma al mapa
    void newWeapon(int x, int y, Weapon newWeapon);
    // Asignar arma a un jugador
    void addWeaponPlayer(int x, int y, Weapon weapon, std::string playerName);
    // Remover arma del jugador
    void dropWeapon(int x, int y, std::string playerName);

    // Agrega un nuevo casco al mapa
    void newHelmet(int x, int y, Helemts newHelmet);
    // Asignar casco a un jugador
    void addHelmetPlayer(int x, int y, Helemts helmet, std::string playerName);
    // Remover casco del jugador
    void dropHelmet(int x, int y, std::string playerName);

    // Agrega una nueva armadura al mapa
    void newArmor(int x, int y);
    // Asignar armadura a un jugador
    void addArmorPlayer(int x, int y, std::string playerName);
    // Remover armadura del jugador
    void dropArmor(int x, int y, std::string playerName);

    // Dibujar mapa, jugadores, armas, armaduras y cascos
    void fill();

    ~Map();
};
