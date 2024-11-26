#include "game.h"

enum Front_event { MOVE_LEFT, MOVE_RIGHT, JUMP_EVENT, PLAY_DEAD, END };

Game::Game(Queue<std::shared_ptr<GenericMsg>>& queueSend,
           Queue<std::shared_ptr<GenericMsg>>& queueRecive, std::string playerName1,
           std::string playerName2):
        queueRecive(queueRecive),
        running(true),
        event_handler(queueSend, playerName1, running, playerName2),
        musicHandler(nullptr) {
    // Inicializo SDL con todo (no recomendado, se puede cambiar para lo que se necesite)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        throw std::runtime_error("Error initializing SDL" + std::string(SDL_GetError()));
    }

    // Inicializo SDL_mixer para reproducir sonidos
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_Quit();  // Cierra SDL
        IMG_Quit();  // Cierra SDL_image
        throw std::runtime_error("Error initializing SDL_mixer" + std::string(Mix_GetError()));
    }

    // Inicializa TTF
    if (TTF_Init() < 0) {
        SDL_Quit();        // Cierra SDL
        IMG_Quit();        // Cierra SDL_image
        Mix_CloseAudio();  // Cierra el sistema de audio
        Mix_Quit();        // Cierra SDL_mixer
        throw std::runtime_error("Error initializing TTF" + std::string(TTF_GetError()));
    }

    if (SDL_GetDisplayUsableBounds(0, &displayBounds) != 0) {
        SDL_Quit();        // Cierra SDL
        IMG_Quit();        // Cierra SDL_image
        Mix_CloseAudio();  // Cierra el sistema de audio
        Mix_Quit();        // Cierra SDL_mixer
        TTF_Quit();        // Cierra TTF
        throw("Error al obtener los limites de la pantalla");
    }

    // Creo el manejador de musica
    musicHandler = std::make_unique<MusicHandler>();

    // Despues de todas las corroboraciones, starteo el event handler
    event_handler.start();

    // Creo la window
    win = std::make_unique<Window>(displayBounds.w, displayBounds.h);

    // Creo la pantalla de carga
    loadingScreen =
            std::make_unique<LoadingScreen>(win->get_rend(), displayBounds.w, displayBounds.h);
}

void Game::play() {
    std::shared_ptr<GenericMsg> msg_players_info = queueRecive.pop();

    if (msg_players_info->get_header() != GenericMsg::MsgTypeHeader::INFO_LOBBY_MSG) {
        throw("Estoy recibiendo un mensaje que no es de info lobby");
    }

    std::shared_ptr<GenericMsg> matriz = queueRecive.pop();
    std::vector<uint16_t> mapa;
    uint16_t filas;
    uint16_t columnas;
    std::shared_ptr<SendMapMsg> newMap;
    if (matriz->get_header() == GenericMsg::MsgTypeHeader::SEND_MAP_MSG) {
        std::shared_ptr<GenericMsg> shared_matriz = std::move(matriz);
        newMap = std::dynamic_pointer_cast<SendMapMsg>(shared_matriz);
        if (newMap) {
            mapa = newMap->get_map();
            filas = newMap->get_filas();
            columnas = newMap->get_columnas();
        } else {
            throw std::runtime_error("Failed to cast GenericMsg to SendMapMsg");
        }
    } else if (!matriz) {
        throw std::runtime_error("Algo anda mal! Mandaste un msj que nda que ver");
    }

    uint tiles_w = displayBounds.w / columnas;
    uint tiles_h = displayBounds.h / filas;
    uint tiles = std::min(tiles_w, tiles_h);

    // Creo el mapa
    Map map(win->get_rend(), tiles, displayBounds.w, displayBounds.h);
    map.makeMap(columnas, filas, mapa);

    // Recibo toda la informacion de los jugadores y sus skins de parte del lobby
    std::shared_ptr<InfoLobbyMsg> info_lobby =
            std::dynamic_pointer_cast<InfoLobbyMsg>(msg_players_info);
    std::list<DescripcionPlayer> players = info_lobby->get_players();
    std::map<std::string, uint8_t> players_info;
    for (auto& player: players) {
        players_info[player.nombre] = player.color;
    }

    // Agrego a cada jugador usando el mensaje de info lobby
    for (uint i = 0; i < players.size(); i++) {
        std::shared_ptr<GenericMsg> jugador = queueRecive.pop();
        if (jugador->get_header() != GenericMsg::MsgTypeHeader::UPDATED_PLAYER_INFO_MSG) {
            throw std::runtime_error(
                    "Estoy recibiendo un mensaje que no es de updated player info");
        }
        std::shared_ptr<UpdatedPlayerInfoMsg> player_info =
                std::dynamic_pointer_cast<UpdatedPlayerInfoMsg>(jugador);
        map.addPlayer(player_info->get_position().first, player_info->get_position().second,
                      players_info[player_info->get_player_name()], player_info->get_player_name());
    }

    const Uint32 frame_rate = 1000 / 30;      // 30 FPS
    Uint32 last_frame_time = SDL_GetTicks();  // Tiempo del último frame

    bool stated_palying = false;
    std::string player_name;
    std::pair<uint16_t, uint16_t> position;
    uint8_t facing_direction = 1;

    musicHandler->playThatMusic(0, -1);  // Reproduce la musica de fondo en bucle infinito
    musicHandler->setThatVolume(0, 10);  // Setea el volumen de la musica de fondo
    while (running) {
        Uint32 current_time = SDL_GetTicks();
        Uint32 elapsed_time = current_time - last_frame_time;

        std::shared_ptr<GenericMsg> msj;

        for (int i = 0; i < 15; i++) {
            if (queueRecive.try_pop(msj)) {
                std::shared_ptr<UpdatedPlayerInfoMsg> player = nullptr;
                uint8_t state = 0;

                std::shared_ptr<ProjectileInfoMsg> projectile = nullptr;
                std::shared_ptr<NotProyectileInfo> not_projectile = nullptr;
                std::pair<uint8_t, uint8_t> position_x_y;
                uint8_t pos_x, pos_y, item = 0;
                std::vector<std::pair<uint8_t, uint8_t>> trail;

                std::shared_ptr<PickupDropMsg> pickup_drop = nullptr;
                uint8_t item_id = 0;

                std::shared_ptr<SendMapMsg> newMap = nullptr;
                std::vector<uint16_t> mapa;
                uint16_t filas;
                uint16_t columnas;

                switch (msj->get_header()) {
                    case GenericMsg::MsgTypeHeader::UPDATED_PLAYER_INFO_MSG:
                        player = std::dynamic_pointer_cast<UpdatedPlayerInfoMsg>(msj);
                        if (player) {
                            player_name = player->get_player_name();
                            position = player->get_position();
                            state = player->get_state();
                            facing_direction = player->get_facing_direction();
                            map.update(player_name, position.first, position.second,
                                       DuckState(state), Side(facing_direction - 1));
                            stated_palying = true;
                        }
                        break;

                    case GenericMsg::MsgTypeHeader::PICKUP_DROP_MSG:
                        pickup_drop = std::dynamic_pointer_cast<PickupDropMsg>(msj);
                        if (pickup_drop) {
                            player_name = pickup_drop->get_player_name();
                            item_id = pickup_drop->get_item_id();
                            map.weaponPlayer(ProjectilesId::ProjectileId(item_id), player_name);
                        }
                        break;

                    case GenericMsg::MsgTypeHeader::PROJECTILE_INFO_MSG:
                        projectile = std::dynamic_pointer_cast<ProjectileInfoMsg>(msj);
                        if (projectile) {
                            pos_x = projectile->get_pos_x();
                            pos_y = projectile->get_pos_y();
                            item = projectile->get_item();
                            trail = projectile->get_trail();  // para el laser
                            // if (trail != std::vector<std::pair<uint8_t, uint8_t>>()) {
                            //     map.newWeapon(pos_x, pos_y, ProjectilesId::ProjectileId(item),
                            //     trail);
                            // } else {
                            map.newWeapon(pos_x, pos_y, ProjectilesId::ProjectileId(item));
                            // }
                        }
                        break;

                    case GenericMsg::MsgTypeHeader::NOT_PROJECTILE_INFO:
                        not_projectile = std::dynamic_pointer_cast<NotProyectileInfo>(msj);
                        if (not_projectile) {
                            position_x_y = not_projectile->get_position_x_y();
                            item = not_projectile->get_item();
                            map.removeWeapon(position_x_y.first, position_x_y.second, ProjectilesId::ProjectileId(item));
                        }
                        break;

                    case GenericMsg::MsgTypeHeader::SEND_MAP_MSG:
                        loadingScreen->fadeOut(map.getTextureMapWithAll(), 1000);
                        newMap = std::dynamic_pointer_cast<SendMapMsg>(msj);
                        if (newMap) {
                            mapa = newMap->get_map();
                            filas = newMap->get_filas();
                            columnas = newMap->get_columnas();

                            tiles_w = displayBounds.w / columnas;
                            tiles_h = displayBounds.h / filas;
                            tiles = std::min(tiles_w, tiles_h);

                            map.makeMap(columnas, filas, mapa);
                            map.fill();
                        }
                        loadingScreen->show(2000);  // pantalla de carga de 500 ms para que no se
                                                    // vea tan feo el cambio de mapa
                        loadingScreen->fadeIn(map.getTextureMapWithoutAnything(), 1000);
                        break;

                    /*
                    case GenericMsg::MsgTypeHeader::PLAYER_DEAD_MSG:
                        player = std::dynamic_pointer_cast<UpdatedPlayerInfoMsg>(msj);
                        if (player) {
                            player_name = player->get_player_name();
                            map.remove(player_name);
                        }
                        break;
                    */
                    case GenericMsg::MsgTypeHeader::GAME_ENDED_MSG:
                        // directa de que termino la partida y de q hay que mostrar la pantalla de
                        // fin
                        return;

                    default:
                        break;
                }
            }
        }

        // Renderiza los objetos en la ventana
        if (elapsed_time >= frame_rate) {
            win->clear();
            map.fill();
            win->fill();
            last_frame_time = current_time;
        }

        if (stated_palying) {
            map.allStanding();
        }

        // Controla la frecuencia de cuadros por segundo (FPS)
        SDL_Delay(std::max(0, static_cast<int>(frame_rate - (SDL_GetTicks() - current_time))));
    }
}

Game::~Game() {
    event_handler.stop();
    event_handler.join();
    Mix_CloseAudio();  // Cierra el sistema de audio
    Mix_Quit();        // Cierra SDL_mixer
    IMG_Quit();        // Cierra SDL_image
    TTF_Quit();        // Cierra TTF
    SDL_Quit();        // Cierra SDL
}
