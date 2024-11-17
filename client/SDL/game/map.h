#include <list>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <SDL2/SDL_render.h>

#include "../../../common/queue.h"

#include "player.h"

class Map {
private:
    SDL_Renderer* rend;

    // Textura del mapa completo (las cosas constantes)
    SDL_Texture* mapTexture;
    // Textura padre para renderizar todo
    SDL_Texture* parentTexture;

    // Numeros para calculos y variaciones de tamaños
    uint tiles;
    uint width_window;
    uint height_window;
    uint columnas;
    uint filas;

    // Imagenes de los tiles
    std::vector<Image*> tilesImages;
    // Posiciones de los tiles
    std::unordered_map<TileType, std::vector<std::pair<int, int>>> tilesPlace;

    // Jugadores
    std::unordered_map<std::string, Player*> players;
    std::list<std::string> playersNamesAlive;

    // Imagenes de las armas
    std::unordered_map<ProjectilesId::ProjectileId, Image*> weapons;
    std::unordered_map<ProjectilesId::ProjectileId, std::pair<int, int>> weaponsPos;
    std::vector<std::pair<int, int>> laser;
    // Posiciones de las armas
    // std::unordered_map<Weapon, std::vector<std::pair<int, int>>> weaponsMap;

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

    Image prueba;

    void makeWeapon(ProjectilesId::ProjectileId id);
    void makeHelmet(Helemts helmet);
    void makeArmor();
    void makeTile(TileType tileType);
    SDL_Rect adjustMapZoom();


public:
    Map(SDL_Renderer* rend, uint tiles, uint width_window,
        uint height_window);

    void makeMap(int w, int h, std::vector<uint16_t> mapa);

    void addPlayer(int columnaActual, int filaActual, int color, std::string name);
    void remove(std::string playerName);

    // Actualiza posicion y estado del jugador
    void update(std::string player, int x, int y, DuckState state, Side side);
    // Pone a todos los jugadores en estado de parados
    void allStanding();

    // Agrega un nuevo arma al mapa
    void newWeapon(int x, int y, ProjectilesId::ProjectileId id);
    // Balas
    void newWeapon(int x, int y, ProjectilesId::ProjectileId id, std::vector<std::pair<uint8_t, uint8_t>> trail);
    // Asignar arma a un jugador
    void weaponPlayer(ProjectilesId::ProjectileId id, std::string playerName);  // si ya tiene arma tonces dispara
    // Remover arma del jugador
    void dropWeapon(std::string playerName);

    // Agrega un nuevo casco al mapa
    void newHelmet(int x, int y, Helemts newHelmet);
    // Asignar/Remover casco a un jugador
    void helmetPlayer(Helemts helmet, std::string playerName);

    // Agrega una nueva armadura al mapa
    void newArmor(int x, int y);
    // Asignar/Reomver armadura a un jugador
    void armorPlayer(std::string playerName);

    // Dibujar mapa, jugadores, armas, armaduras y cascos
    void fill();

    ~Map();
};
