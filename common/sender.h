#ifndef SENDER_H
#define SENDER_H
#include <string>

#include "queue.h"
#include "thread.h"

#include "protocol.h"

class Sender: public Thread {
private:
    Queue<std::string>* send_queue; // tiene que ser un puntero para poder cambiar la referencia
    Protocol* protocol;

    void run() override;

public:
    Sender(Queue<std::string>* send_queue, Protocol* protocol);
    
    /* 
    * Detiene la ejecución del hilo seteando _keep_running en false.
    */
    void kill();

    /*
    * Actualiza la referencia a la cola de envío.
    */
    void update_send_queue(Queue<std::string>* new_send_queue);


    /*
    * Actualiza la referencia al protocolo.
    */
    void update_protocol(Protocol* protocol);

};
#endif  // SENDER_H
