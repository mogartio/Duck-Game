#include "client.h"
#include "comunication/reciver.h"
#include "comunication/sender.h"
//#include "SDL/front.h"
#include "lobby.h"
#include "game.h"

#define TAMANIO_QUEUE 50

int Client::run() {
    
	// ------------------- Queues -------------------
	Queue<ClientInfo*> queueSender(TAMANIO_QUEUE);
	Queue<std::string> queueReciver(TAMANIO_QUEUE);

    Queue<std::string> queueFrontSender(TAMANIO_QUEUE);
    Queue<std::string> queueFrontReciver(TAMANIO_QUEUE);

    // ------------------- Front -------------------
    //Front front(queueFrontSender, queueFrontReciver);
    //front.start();

    // ------------------- Sender/Reciver -------------------
	Sender sender(skt_client, queueSender);
    sender.start();
    Reciver reciver(skt_client, queueReciver);
    reciver.start();

	// ------------------- Lobby -------------------
	Lobby lobby(queueSender, queueReciver, queueFrontSender, queueFrontReciver);
    lobby.run(); //el lobby corre hasta que se decide iniciar a jugar 

	// ------------------- Game -------------------
    Game game(queueSender, queueReciver, queueFrontSender, queueFrontReciver);
    game.play();

    // ------------------- Close and Join -------------------
    queueSender.close();
    queueReciver.close();
    queueFrontReciver.close();
    queueFrontSender.close();

    sender.close();
    sender.join();

    reciver.close();
    reciver.join();

    //front.close();
    //front.join();

    return 0;
}

