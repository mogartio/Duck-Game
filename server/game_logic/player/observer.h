#ifndef OBSERVER_H
#define OBSERVER_H
#include "../../../common/coordinate.h"
#include "../../../common/messages/generic_msg.h"
#include "../../send_queues_monitor.h"


namespace PlayerInfoId {
#define AIM_RIGHT 1
#define AIM_LEFT 2
#define AIM_UP 3
#define AIM_DOWN 4

#define GROUNDED 1
#define JUMPING 2
#define FALLING 3
#define DEAD 4

}  // namespace PlayerInfoId
class Observer {
protected:
    SendQueuesMonitor<GenericMsg*>& senders;

public:
    Observer(SendQueuesMonitor<GenericMsg*>& queues): senders(queues) {}
    virtual void update() {}
    virtual void update(std::string, uint16_t, uint16_t, uint8_t, uint8_t) {}
    virtual void update(std::vector<std::pair<uint16_t, uint16_t>>, std::pair<uint16_t, uint16_t>) {
    }
    virtual ~Observer() = default;
};

class PlayerObserver: public Observer {
    using Observer::update;

public:
    PlayerObserver(SendQueuesMonitor<GenericMsg*>& queues): Observer(queues) {}
    virtual void update(std::string name, uint16_t pos_x, uint16_t pos_y, uint8_t state,
                        uint8_t facing_direction) override {
        std::list<GenericMsg*>
                porquenecesitounalist;  // Preferiria poder broadcastear un mensaje a la vez
        UpdatedPlayerInfoMsg msg(name, std::make_pair(pos_x, pos_y), state, facing_direction);

        std::cout << "se esta broadcasteando un jugador que es:" << name << " con pos: " << pos_x
                  << pos_y << "En estado: " << state << "mirando a" << facing_direction
                  << std::endl;
        porquenecesitounalist.push_back(&msg);
        senders.broadcast(porquenecesitounalist);
    }
};

class ProjectileObserver: public Observer {
    using Observer::update;

public:
    ProjectileObserver(SendQueuesMonitor<GenericMsg*>& queues): Observer(queues) {}
    virtual void update(std::vector<std::pair<uint16_t, uint16_t>> trail,
                        std::pair<uint16_t, uint16_t> final_position) override {
        ProjectileInfoMsg msg(trail, final_position);
        std::cout << "se esta broadcasteando la posicion de un proyectil que es:"
                  << std::get<0>(final_position) << std::get<1>(final_position) << std::endl;
        std::list<GenericMsg*>
                porquenecesitounalist;  // Preferiria poder broadcastear un mensaje a la vez
        porquenecesitounalist.push_back(&msg);
        senders.broadcast(porquenecesitounalist);
    }
};

#endif
