#ifndef GAME_H
#define GAME_H
#include <string>

#include "../common/queue.h"
#include "../common/queuesStructs/clientInfo.cpp"

class Game {
private:
    Queue<ClientInfo*>& queueSender;
    Queue<std::string>& queueReciver;
    Queue<std::string>& queueFrontSender;
    Queue<std::string>& queueFrontReciver;

    bool playing;

public:
    // ------------------- Constructores -------------------
    /*
     * Constructor del Juego
     */
    explicit Game(Queue<ClientInfo*>& queueSender, Queue<std::string>& queueReciver,
                  Queue<std::string>& queueFrontSender, Queue<std::string>& queueFrontReciver):
            queueSender(queueSender),
            queueReciver(queueReciver),
            queueFrontSender(queueFrontSender),
            queueFrontReciver(queueFrontReciver),
            playing(true) {}

    // ------------------- Metodos -------------------
    /*
     * El metodo play se encarga de correr el juego
     */
    void play();

    // ------------------- Restricciones -------------------
    /*
     * Deshabilitamos el constructor por copia y operador asignación por copia
     * */
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    /*
     * Hacemos que la clase no sea movible.
     * */
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;

    ~Game() = default;
};

#endif
