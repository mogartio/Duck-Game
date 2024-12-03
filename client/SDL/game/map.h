#include <list>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include "../../../common/messages/generic_msg.h"
#include "../../../common/queue.h"

#include "player.h"

struct WeaponData {

    int pos_x;
    int pos_y;
    int facing_direction_first;
    int facing_direction_second;

    WeaponData()
        : pos_x(0), pos_y(0), facing_direction_first(0), facing_direction_second(0) {}
        
    // Constructor
    WeaponData(int x, int y, int fd1, int fd2)
        : pos_x(x), pos_y(y), facing_direction_first(fd1), facing_direction_second(fd2) {}
};

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
    uint theme;

    // Imagenes de los tiles dia/noche
    std::vector<std::shared_ptr<Image>> tilesImagesDay;
    std::vector<std::shared_ptr<Image>> tilesImagesNight;
    // Posiciones de los tiles
    std::unordered_map<TileType, std::vector<std::pair<int, int>>> tilesPlace;

    // Jugadores
    std::unordered_map<std::string, std::shared_ptr<Player>> players;
    std::list<std::string> playersNamesAlive;

    // Puntos de los jugadores
    std::unordered_map<std::string, int> playersPoints;
    // Textura de los nombres de los jugadores
    std::vector<std::pair<std::shared_ptr<SDL_Texture>, SDL_Rect>> textura_texto;

    // Imagenes de las armas
    std::unordered_map<ProjectilesId::ProjectileId, std::shared_ptr<Image>> weapons;
    // Posiciones de las armas
    std::unordered_map<ProjectilesId::ProjectileId, WeaponData> weaponsMap;

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

    // Imagenes de las cajas
    std::vector<std::shared_ptr<Image>> boxes;
    std::vector<std::pair<int, std::pair<int, int>>> boxesPos;


    // zoom del mapa
    float currentZoom;

    bool canAddTile(std::vector<std::vector<int>> matriz, int filaActual, int columnaActual);

    void redifine_sizes();

    void makeWeapon(ProjectilesId::ProjectileId id);
    void makeExplosion();
    void makeHelmet(ProjectilesId::ProjectileId helmet);
    void makeArmor();
    void makeTile(TileType tileType);
    void makeBoxes();

    float animationZoom(float targetZoom);
    float getDeltaTime();
    SDL_Rect adjustMapZoom();


public:
    Map(SDL_Renderer* rend, uint tiles, uint width_window, uint height_window);

    void makeMap(int w, int h, std::vector<uint16_t> mapa);

    void addPlayer(int columnaActual, int filaActual, int color, std::string name);
    void remove(std::string playerName);

    // Actualiza posicion y estado del jugador
    void update(std::string player, int x, int y, DuckState state, Side side);
    // Pone a todos los jugadores en estado de parados
    void standing(std::unordered_map<std::string, bool> players_updated);

    // Agrega un nuevo arma al mapa
    void newWeapon(int x, int y, ProjectilesId::ProjectileId id, int facing_direction_first,
                   int facing_direction_second);
    // Asignar arma a un jugador
    void weaponPlayer(ProjectilesId::ProjectileId id,
                      std::string playerName);  // si ya tiene arma tonces dispara

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

    // Agregar caja
    void newBox(int x, int y);

    // Remover del mapa
    void removeWeapon(int x, int y, ProjectilesId::ProjectileId id);

    void setTheme(uint theme);


    // Dibujar mapa, jugadores, armas, armaduras y cascos
    void fill();

    // Points
    void addPoints(std::string winner);
    std::pair<std::string, std::string> get_winner();
    std::unordered_map<std::string, int> getPoints();

    SDL_Texture* getTextureMapWithAll() const;

    SDL_Texture* getTextureMapWithoutAnything() const;

    ~Map();
};
