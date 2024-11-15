#include <map>

#include <SDL2/SDL_timer.h>

#include "frontOnePlaye.h"
#define TILES_TO_PIXELS 16

enum Front_event { MOVE_LEFT, MOVE_RIGHT, JUMP_EVENT, PLAY_DEAD, END };

OnePlayer::OnePlayer(Queue<GenericMsg*>& queueSend, Queue<GenericMsg*>& queueRecive,
                     std::string playerName1, std::string playerName2):
        queueRecive(queueRecive),
        running(true),
        event_handler(queueSend, playerName1, running, playerName2) {}

void OnePlayer::play() {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return;
    }

    SDL_Rect displayBounds;
    if (SDL_GetDisplayUsableBounds(0, &displayBounds) != 0) {
        SDL_Quit();
        throw("Error al obtener los limites de la pantalla");
    }

    GenericMsg* msg_players_info = queueRecive.pop();

    if (msg_players_info->get_header() != GenericMsg::MsgTypeHeader::INFO_LOBBY_MSG) {
        throw("Estoy recibiendo un mensaje que no es de info lobby");
    }

    GenericMsg* matriz = queueRecive.pop();

    std::vector<uint16_t> mapa;
    uint16_t filas;
    uint16_t columnas;
    if (matriz->get_header() == GenericMsg::MsgTypeHeader::SEND_MAP_MSG) {
        SendMapMsg* map = dynamic_cast<SendMapMsg*>(matriz);
        mapa = map->get_map();
        filas = map->get_filas();
        columnas = map->get_columnas();
    } else if (matriz == nullptr) {
        throw("Algo anda mal! Mandaste un msj que nda que ver");
    }

    uint tiles_w = displayBounds.w / columnas;
    uint tiles_h = displayBounds.h / filas;
    uint tiles = std::min(tiles_w, tiles_h);

    // Despues de todas las corroboraciones, starteo el event handler
    event_handler.start();

    Window win(displayBounds.w, displayBounds.h);

    // Window win(columnas * TILES_TO_PIXELS, filas * TILES_TO_PIXELS);

    Map map(win.get_rend(), mapa, tiles, displayBounds.w, displayBounds.h);
    map.makeMap(columnas, filas);

    // Recibo toda la informacion de los jugadores y sus skins de parte del lobby
    InfoLobbyMsg* info_lobby = dynamic_cast<InfoLobbyMsg*>(msg_players_info);
    std::list<DescipcionPlayer> players = info_lobby->get_players();
    std::map<std::string, uint8_t> players_info;
    for (auto& player: players) {
        players_info[player.nombre] = player.color;
    }

    // Agrego a cada jugador usando el mensaje de info lobby
    for (uint i = 0; i < players.size(); i++) {
        GenericMsg* jugador = queueRecive.pop();
        if (jugador->get_header() != GenericMsg::MsgTypeHeader::UPDATED_PLAYER_INFO_MSG) {
            throw std::runtime_error(
                    "Estoy recibiendo un mensaje que no es de updated player info");
        }
        UpdatedPlayerInfoMsg* player_info = dynamic_cast<UpdatedPlayerInfoMsg*>(jugador);
        map.addPlayer(player_info->get_position().first, player_info->get_position().second,
                      players_info[player_info->get_player_name()], player_info->get_player_name());
    }

    const Uint32 frame_rate = 1000 / 30;      // 30 FPS
    Uint32 last_frame_time = SDL_GetTicks();  // Tiempo del último frame

    bool stated_palying = false;
    std::string player_name;
    std::pair<uint16_t, uint16_t> position;
    uint8_t facing_direction = 1;

    while (running) {
        Uint32 current_time = SDL_GetTicks();
        Uint32 elapsed_time = current_time - last_frame_time;

        GenericMsg* msj;

        for (int i = 0; i < 15; i++) {
            if (queueRecive.try_pop(msj)) {
                UpdatedPlayerInfoMsg* player = nullptr;
                uint8_t state = 0;
                ProjectileInfoMsg* projectile = nullptr;
                uint8_t pos_x, pos_y, item = 0;
                std::vector<std::pair<uint8_t, uint8_t>> trail;
                switch (msj->get_header()) {
                    case GenericMsg::MsgTypeHeader::UPDATED_PLAYER_INFO_MSG:
                        player = dynamic_cast<UpdatedPlayerInfoMsg*>(msj);
                        player_name = player->get_player_name();
                        position = player->get_position();
                        state = player->get_state();
                        facing_direction = player->get_facing_direction();
                        map.update(player_name, position.first, position.second, DuckState(state),
                                   Side(facing_direction - 1));
                        stated_palying = true;
                    case GenericMsg::MsgTypeHeader::PROJECTILE_INFO_MSG:
                        projectile = dynamic_cast<ProjectileInfoMsg*>(msj);
                        pos_x = projectile->get_pos_x();
                        pos_y = projectile->get_pos_y();
                        item = projectile->get_item();
                        trail = projectile->get_trail();  // para el laser
                        map.newWeapon(pos_x, pos_y, Weapon(item));
                        break;
                    /* case GenericMsg::MsgTypeHeader::PLAYER_DEAD_MSG:
                        // directa de que murio el jugador y de que hay que mostrar la pantalla de
                    muerte UpdatedPlayerInfoMsg* player = dynamic_cast<UpdatedPlayerInfoMsg*>(msj);
                        player_name = player->get_player_name();
                        map.remove(player_name);
                    case GenericMsg::MsgTypeHeader::PROJECTILE_INFO_MSG:
                        // directa de que hay que mostrar el proyectil (weapon o bullet)
                        ProyectileInfoMsg* proyectile = dynamic_cast<ProyectileInfoMsg*>(msj);
                        uint16_t weapon = proyectile->get_proyectile();
                        map.weaponPlayer(weapon, player_name);
                    case GenericMsg::MsgTypeHeader::PICKUP_SHOOT_MSG:
                        // directa de que hay que mostrar el item que se levanto o disparo

                    case GenericMsg::MsgTypeHeader::DROP_MSG:
                        // directa de que hay que mostrar el item que se tiro
                        // necesito nombre de player y que cosa esta dropeando (weapon, armor,
                    helmet)
                    */
                    case GenericMsg::MsgTypeHeader::GAME_ENDED_MSG:
                        // directa de que termino la partida y de q hay que mostrar la pantalla de
                        // fin

                    default:
                        break;
                }
            } else if (stated_palying) {
                map.update(player_name, position.first, position.second, DuckState::STANDING,
                           Side(facing_direction - 1));
            }

            // Renderiza los objetos en la ventana
            if (elapsed_time >= frame_rate) {
                win.clear();
                map.fill();
                win.fill();
                last_frame_time = current_time;
            }
        }

        // Controla la frecuencia de cuadros por segundo (FPS)
        SDL_Delay(std::max(0, static_cast<int>(frame_rate - (SDL_GetTicks() - current_time))));
    }

    event_handler.stop();
    event_handler.join();
}
