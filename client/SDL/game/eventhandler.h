#include <functional>
#include <map>
#include <string>
#include <tuple>

#include <SDL2/SDL.h>

#include "../../../common/messages/generic_msg.h"
#include "../../../common/queue.h"
#include "../../../common/thread.h"

class EventHandler: public Thread {
private:
    Queue<GenericMsg*>& queueSend;
    std::string playerName1;
    std::atomic<bool>& running;
    std::string playerName2;

    std::map<std::tuple<Uint32, SDL_Scancode>, std::function<GenericMsg*(void)>> key_accion_map;

    std::map<SDL_Scancode, bool> pressed_keys_state;

    bool corroboraciones(SDL_Event& event);

public:
    EventHandler(Queue<GenericMsg*>& queueSend, std::string& playerName1,
                 std::atomic<bool>& running, std::string playerName2 = "");

    void run() override;
};
