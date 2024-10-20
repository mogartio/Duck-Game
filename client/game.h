#ifndef GAME_H
#define GAME_H

#include "../common/queue.h"

class Game {
private:

    Queue<std::string>& queueSender;
    Queue<std::string>& queueReciver;
    Queue<std::string>& queueFrontSender;
    Queue<std::string>& queueFrontReciver;

public:
    // ------------------- Constructores -------------------
    /*
     * Constructor del Juego
     */
    explicit Game(Queue<std::string>& queueSender, 
                   Queue<std::string>& queueReciver, 
                   Queue<std::string>& queueFrontSender,
                   Queue<std::string>& queueFrontReciver):
                   queueSender(queueSender),
                   queueReciver(queueReciver),
                   queueFrontSender(queueFrontSender),
                   queueFrontReciver(queueFrontReciver) {}
    
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


