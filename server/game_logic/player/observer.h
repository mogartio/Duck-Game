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
    virtual void update(uint8_t, uint8_t, uint8_t) {}
    virtual void update(std::string, uint8_t) {}
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
        UpdatedPlayerInfoMsg* msg = new UpdatedPlayerInfoMsg(name, std::make_pair(pos_x, pos_y),
                                                             state, facing_direction);
        // std::cout << "se esta broadcasteando un jugador que es:" << name
        //           << " con pos: " << std::to_string(pos_x) << " , " << std::to_string(pos_y)
        //           << " En estado: " << std::to_string(state) << "mirando a "
        //           << std::to_string(facing_direction) << std::endl;
        porquenecesitounalist.push_back(msg);
        senders.broadcast(porquenecesitounalist);
    }
    virtual void update(std::string name, uint8_t id) override {
        std::cout << "entro en el obs per se" << std::endl;
        std::list<GenericMsg*> odio;
        PickupDropMsg* msg = new PickupDropMsg(name, id);
        odio.push_back(msg);
        senders.broadcast(odio);
    }
};

class ProjectileObserver: public Observer {
    using Observer::update;

public:
    // virtual void update(std::vector<std::pair<uint16_t, uint16_t>> trail,
    //                     std::pair<uint16_t, uint16_t> final_position, uint8_t id) override {
    //     ProjectileInfoMsg* msg = new ProjectileInfoMsg(trail, final_position, id);
    //     std::stringstream ss;
    //     for (auto& coor: trail) {
    //         ss << std::to_string(std::get<0>(coor)) << " , " << std::to_string(std::get<1>(coor))
    //            << std::endl;
    //     }
    //     // std::cout << "se esta broadcasteando la posicion de un proyectil que es:"
    //     //           << std::to_string(std::get<0>(final_position))
    //     //           << std::to_string(std::get<1>(final_position)) << " con trail: " << ss.str()
    //     //           << std::endl;
    //     std::list<GenericMsg*>
    //             porquenecesitounalist;  // Preferiria poder broadcastear un mensaje a la vez
    //     porquenecesitounalist.push_back(msg);
    //     senders.broadcast(porquenecesitounalist);
    // }
    ProjectileObserver(SendQueuesMonitor<GenericMsg*>& queues): Observer(queues) {}
    virtual void update(uint8_t pos_x, uint8_t pos_y, uint8_t id) override {
        ProjectileInfoMsg* msg = new ProjectileInfoMsg(pos_x, pos_y, id);
        std::list<GenericMsg*>
                porquenecesitounalist;  // Preferiria poder broadcastear un mensaje a la vez
        porquenecesitounalist.push_back(msg);
        senders.broadcast(porquenecesitounalist);
    }
};

#endif
