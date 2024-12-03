#include "eventhandler.h"

#include <map>

#include <SDL2/SDL_timer.h>

#define ID_ITEM 0x05

EventHandler::EventHandler(Queue<std::shared_ptr<GenericMsg>>& queueSend, std::string& p1,
                           std::atomic<bool>& running, std::string p2):
        queueSend(queueSend), playerName1(p1), running(running), playerName2(p2) {
    // Key down actions
    key_accion_map[std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_E)] = [this]() {
        // shoot y pickup
        return std::make_shared<StartActionMsg>(ActionsId::SHOOT, playerName1);
    };
    key_accion_map[std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_R)] = [this]() {
        return std::make_shared<StartActionMsg>(ActionsId::THROW_WEAPON, playerName1);
    };
    key_accion_map[std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_W)] = [this]() {
        return std::make_shared<StartActionMsg>(ActionsId::AIM_UP, playerName1);
    };
    key_accion_map[std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_LSHIFT)] = [this]() {
        return std::make_shared<StartActionMsg>(ActionsId::JUMP, playerName1);
    };
    key_accion_map[std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_S)] = [this]() {
        return std::make_shared<StartActionMsg>(ActionsId::PLAY_DEAD, playerName1);
    };
    key_accion_map[std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_A)] = [this]() {
        return std::make_shared<StartActionMsg>(ActionsId::MOVE_LEFT, playerName1);
    };
    key_accion_map[std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_D)] = [this]() {
        return std::make_shared<StartActionMsg>(ActionsId::MOVE_RIGHT, playerName1);
    };
    key_accion_map[std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_C)] = [this]() {
        return std::make_shared<StartActionMsg>(ActionsId::CHEAT, playerName1);
    };

    // Key up actions
    key_accion_map[std::make_tuple(SDL_KEYUP, SDL_SCANCODE_S)] = [this]() {
        return std::make_shared<StopActionMsg>(ActionsId::PLAY_DEAD, playerName1);
    };
    key_accion_map[std::make_tuple(SDL_KEYUP, SDL_SCANCODE_A)] = [this]() {
        return std::make_shared<StopActionMsg>(ActionsId::MOVE_LEFT, playerName1);
    };
    key_accion_map[std::make_tuple(SDL_KEYUP, SDL_SCANCODE_D)] = [this]() {
        return std::make_shared<StopActionMsg>(ActionsId::MOVE_RIGHT, playerName1);
    };
    key_accion_map[std::make_tuple(SDL_KEYUP, SDL_SCANCODE_W)] = [this]() {
        return std::make_shared<StopActionMsg>(ActionsId::AIM_UP, playerName1);
    };
    key_accion_map[std::make_tuple(SDL_KEYUP, SDL_SCANCODE_LSHIFT)] = [this]() {
        return std::make_shared<StopActionMsg>(ActionsId::JUMP, playerName1);
    };
    key_accion_map[std::make_tuple(SDL_KEYUP, SDL_SCANCODE_E)] = [this]() {
        return std::make_shared<StopActionMsg>(ActionsId::SHOOT, playerName1);
    };
    key_accion_map[std::make_tuple(SDL_KEYUP, SDL_SCANCODE_R)] = [this]() {
        return std::make_shared<StopActionMsg>(ActionsId::THROW_WEAPON, playerName1);
    };

    // Inicializo el estado de las teclas
    pressed_keys_state[SDL_SCANCODE_E] = false;
    pressed_keys_state[SDL_SCANCODE_R] = false;
    pressed_keys_state[SDL_SCANCODE_W] = false;
    pressed_keys_state[SDL_SCANCODE_LSHIFT] = false;
    pressed_keys_state[SDL_SCANCODE_S] = false;
    pressed_keys_state[SDL_SCANCODE_A] = false;
    pressed_keys_state[SDL_SCANCODE_D] = false;
    pressed_keys_state[SDL_SCANCODE_C] = false;

    // Si hay un segundo jugador, se agregan las teclas correspondientes
    if (playerName2 != "") {
        // Key down actions
        key_accion_map[std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_M)] = [this]() {
            // shoot y pickup
            return std::make_shared<StartActionMsg>(ActionsId::SHOOT, playerName2);
        };
        key_accion_map[std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_SPACE)] = [this]() {
            return std::make_shared<StartActionMsg>(ActionsId::JUMP, playerName2);
        };
        key_accion_map[std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_UP)] = [this]() {
            return std::make_shared<StartActionMsg>(ActionsId::AIM_UP, playerName2);
        };
        key_accion_map[std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_DOWN)] = [this]() {
            return std::make_shared<StartActionMsg>(ActionsId::PLAY_DEAD, playerName2);
        };
        key_accion_map[std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_LEFT)] = [this]() {
            return std::make_shared<StartActionMsg>(ActionsId::MOVE_LEFT, playerName2);
        };
        key_accion_map[std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_RIGHT)] = [this]() {
            return std::make_shared<StartActionMsg>(ActionsId::MOVE_RIGHT, playerName2);
        };
        key_accion_map[std::make_tuple(SDL_KEYDOWN, SDL_SCANCODE_N)] = [this]() {
            return std::make_shared<StartActionMsg>(ActionsId::THROW_WEAPON, playerName2);
        };

        // Key up actions
        key_accion_map[std::make_tuple(SDL_KEYUP, SDL_SCANCODE_DOWN)] = [this]() {
            return std::make_shared<StopActionMsg>(ActionsId::PLAY_DEAD, playerName2);
        };
        key_accion_map[std::make_tuple(SDL_KEYUP, SDL_SCANCODE_LEFT)] = [this]() {
            return std::make_shared<StopActionMsg>(ActionsId::MOVE_LEFT, playerName2);
        };
        key_accion_map[std::make_tuple(SDL_KEYUP, SDL_SCANCODE_RIGHT)] = [this]() {
            return std::make_shared<StopActionMsg>(ActionsId::MOVE_RIGHT, playerName2);
        };
        key_accion_map[std::make_tuple(SDL_KEYUP, SDL_SCANCODE_UP)] = [this]() {
            return std::make_shared<StopActionMsg>(ActionsId::AIM_UP, playerName2);
        };
        key_accion_map[std::make_tuple(SDL_KEYUP, SDL_SCANCODE_M)] = [this]() {
            return std::make_shared<StopActionMsg>(ActionsId::SHOOT, playerName2);
        };
        key_accion_map[std::make_tuple(SDL_KEYUP, SDL_SCANCODE_SPACE)] = [this]() {
            return std::make_shared<StopActionMsg>(ActionsId::JUMP, playerName2);
        };
        key_accion_map[std::make_tuple(SDL_KEYUP, SDL_SCANCODE_N)] = [this]() {
            return std::make_shared<StopActionMsg>(ActionsId::THROW_WEAPON, playerName2);
        };

        pressed_keys_state[SDL_SCANCODE_M] = false;
        pressed_keys_state[SDL_SCANCODE_SPACE] = false;
        pressed_keys_state[SDL_SCANCODE_N] = false;
        pressed_keys_state[SDL_SCANCODE_UP] = false;
        pressed_keys_state[SDL_SCANCODE_DOWN] = false;
        pressed_keys_state[SDL_SCANCODE_LEFT] = false;
        pressed_keys_state[SDL_SCANCODE_RIGHT] = false;
    }
}

void EventHandler::setMusicHandler(std::shared_ptr<MusicHandler> musicHandler) {
    this->musicHandler = musicHandler;
}

bool EventHandler::corroboraciones(SDL_Event& event) {
    return (event.type != SDL_KEYDOWN && event.type != SDL_KEYUP) ||
           (pressed_keys_state[event.key.keysym.scancode] && event.type == SDL_KEYDOWN);
}

void EventHandler::run() {
    // Mientras el thread siga corriendo
    std::shared_ptr<GenericMsg> msg;
    bool mensajeEnviado = false;
    while (running) {
        if (is_blocked) {
            std::this_thread::sleep_for(std::chrono::milliseconds(35));
            continue;
        }
        SDL_Event event;
        // Procesa los eventos encolados
        if (SDL_WaitEvent(&event)) {  // esperamos un evento exitoso
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
            if (corroboraciones(event)) {
                continue;
            }

            if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_Q) {
                musicHandler != nullptr ? musicHandler->playThatSound(MusicHandler::Sound::QUACK) :
                                          void();
                continue;
            }


            // si es un evento de tecla presionada o soltada
            pressed_keys_state[event.key.keysym.scancode] =
                    event.type ==
                    SDL_KEYDOWN;  // si es un evento de tecla soltada, el valor pasa a ser false

            std::shared_ptr<GenericMsg> msg_posible_a_liberar = msg;
            try {
                msg = key_accion_map.at(std::make_tuple(event.type, event.key.keysym.scancode))();
                if (msg_posible_a_liberar != nullptr && !mensajeEnviado) {
                    // delete msg_posible_a_liberar;
                }
                mensajeEnviado = false;
            } catch (std::out_of_range& e) {
                // si no se encontro la tecla en el mapa, no hacemos nada
                continue;
            }
            if (!mensajeEnviado && msg != nullptr) {
                mensajeEnviado = queueSend.try_push(msg);
            }
        }
    }
}


void EventHandler::block() { is_blocked = true; }
void EventHandler::unblock() { is_blocked = false; }
