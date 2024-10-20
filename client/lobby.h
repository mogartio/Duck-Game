#ifndef LOBBY_H
#define LOBBY_H

#include "../common/queue.h"

class Lobby {
private:

    Queue<std::string>& queueSender;
    Queue<std::string>& queueReciver;
    Queue<std::string>& queueFrontSender;
    Queue<std::string>& queueFrontReciver;

    bool play;
public:

    // ------------------- Constructores -------------------
    /*
     * Constructor del Lobby
     */
    explicit Lobby(Queue<std::string>& queueSender, 
                   Queue<std::string>& queueReciver, 
                   Queue<std::string>& queueFrontSender,
                   Queue<std::string>& queueFrontReciver):
                   queueSender(queueSender),
                   queueReciver(queueReciver),
                   queueFrontSender(queueFrontSender),
                   queueFrontReciver(queueFrontReciver), 
                   play(false) {}

    
    // ------------------- Metodos -------------------
    /*
     * El metodo run se encarga de correr el juego
     */
    void run();

    // ------------------- Restricciones -------------------
    /*
     * Deshabilitamos el constructor por copia y operador asignación por copia
     * */
    Lobby(const Lobby&) = delete;
    Lobby& operator=(const Lobby&) = delete;

    /*
     * Hacemos que la clase no sea movible.
     * */
    Lobby(Lobby&&) = delete;
    Lobby& operator=(Lobby&&) = delete;

    ~Lobby() = default;


};


#endif



