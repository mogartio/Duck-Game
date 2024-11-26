#include <algorithm>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <SDL2/SDL_timer.h>

#include "../../../common/messages/generic_msg.h"
#include "../../../common/queue.h"
#include "../../../common/thread.h"

#include "eventhandler.h"
#include "loadingscreen.h"
#include "map.h"
#include "musichandler.h"
#include "window.h"
class Game {
private:
    Queue<std::shared_ptr<GenericMsg>>& queueRecive;
    std::atomic<bool> running;
    EventHandler event_handler;
    SDL_Rect displayBounds;
    std::unique_ptr<MusicHandler> musicHandler;
    std::unique_ptr<Window> win;
    std::unique_ptr<LoadingScreen> loadingScreen;

public:
    Game(Queue<std::shared_ptr<GenericMsg>>& queueSend,
         Queue<std::shared_ptr<GenericMsg>>& queueRecive, std::string playerName1,
         std::string playerName2 = "");

    void play();

    ~Game();
};
