#include <list>

#include <memory>
#include <set>
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
    std::vector<std::shared_ptr<Image>> tilesImages;
    // Posiciones de los tiles
    std::unordered_map<TileType, std::vector<std::pair<int, int>>> tilesPlace;

    // Jugadores
    std::unordered_map<std::string, std::shared_ptr<Player>> players;
    std::list<std::string> playersNamesAlive;

    // Imagenes de las armas
    std::unordered_map<ProjectilesId::ProjectileId, std::shared_ptr<Image>> weapons;
    // Posiciones de las armas
    std::unordered_map<ProjectilesId::ProjectileId, std::vector<std::pair<int, int>>> weaponsMap;

    // Imagenes de los cascos usables
    std::unordered_map<ProjectilesId::ProjectileId, std::shared_ptr<Image>> helmets;
    // Posiciones de los cascos en el mapa
    std::unordered_map<ProjectilesId::ProjectileId, std::shared_ptr<Image>> helmetsMap;
    // std::unordered_map<ProjectilesId::ProjectileId, std::pair<int, int>> helmetsPos;
    std::unordered_map<ProjectilesId::ProjectileId, std::vector<std::pair<int, int>>> helmetsPos;

    // Imagen de armadura usable
    std::shared_ptr<Image> armor;
    std::shared_ptr<Image> hombro;
    // Imagen de armadura en el mapa
    std::shared_ptr<Image> armorOnMap;
    // Posiciones de la armadura
    std::vector<std::pair<int, int>> armorMap;

    std::shared_ptr<Image> background;

    std::shared_ptr<Image> prueba;

    // Imagenes de las explosiones
    std::vector<std::shared_ptr<Image>> explosions;
    // Posiciones de las explosiones
    std::vector<std::pair<int, int>> explosionsPos;
    // Contador de las explosiones
    std::vector<int> explosionCounter;

    bool canAddTile(std::vector<std::vector<int>> matriz, int filaActual, int columnaActual);

    void makeWeapon(ProjectilesId::ProjectileId id);
    void makeExplosion();
    void makeHelmet(ProjectilesId::ProjectileId helmet);
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
    void standing(std::unordered_map<std::string, bool> players_updated);

    // Agrega un nuevo arma al mapa
    void newWeapon(int x, int y, ProjectilesId::ProjectileId id);
    // Asignar arma a un jugador
    void weaponPlayer(ProjectilesId::ProjectileId id, std::string playerName);  // si ya tiene arma tonces dispara
    // Remover arma del jugador
    void dropWeapon(std::string playerName);

    // Agrega un nuevo casco al mapa
    void newHelmet(int x, int y, ProjectilesId::ProjectileId newHelmet);
    // Asignar/Remover casco a un jugador
    void helmetPlayer(ProjectilesId::ProjectileId helmet, std::string playerName);

    // Agrega una nueva armadura al mapa
    void newArmor(int x, int y);
    // Asignar/Reomver armadura a un jugador
    void armorPlayer(std::string playerName);

    // Agregar explosion
    void explosion(int x, int y);

    // Remover del mapa
    void removeWeapon(int x, int y, ProjectilesId::ProjectileId id);

    // Dibujar mapa, jugadores, armas, armaduras y cascos
    void fill();

    SDL_Texture* getTextureMapWithAll() const;

    SDL_Texture* getTextureMapWithoutAnything() const;

    ~Map();
};
