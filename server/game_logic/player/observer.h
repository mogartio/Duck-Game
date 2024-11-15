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
    explicit Observer(SendQueuesMonitor<GenericMsg*>& queues): senders(queues) {}
    virtual void update() const {}
    virtual void update(std::string, uint16_t, uint16_t, uint8_t, uint8_t) const {}
    virtual void update(uint8_t, uint8_t, uint8_t) const {}
    virtual void update(std::string, uint8_t) const {}
    virtual void update(std::vector<std::pair<uint8_t, uint8_t>>, uint8_t, uint8_t, uint8_t) const {
    }
    virtual ~Observer() = default;
};

class PlayerObserver: public Observer {
    using Observer::update;

public:
    explicit PlayerObserver(SendQueuesMonitor<GenericMsg*>& queues): Observer(queues) {}
    virtual void update(std::string name, uint16_t pos_x, uint16_t pos_y, uint8_t state,
                        uint8_t facing_direction) const override {
        UpdatedPlayerInfoMsg* msg = new UpdatedPlayerInfoMsg(name, std::make_pair(pos_x, pos_y),
                                                             state, facing_direction);
        // std::cout << "se esta broadcasteando un jugador que es:" << name
        //           << " con pos: " << std::to_string(pos_x) << " , " << std::to_string(pos_y)
        //           << " En estado: " << std::to_string(state) << "mirando a "
        //           << std::to_string(facing_direction) << std::endl;
        senders.broadcast(msg);
    }
    virtual void update(std::string name, uint8_t id) const override {
        PickupDropMsg* msg = new PickupDropMsg(name, id);
        senders.broadcast(msg);
    }
};

class ProjectileObserver: public Observer {
    using Observer::update;

public:
    virtual void update(std::vector<std::pair<uint8_t, uint8_t>> trail, uint8_t current_pos_x,
                        uint8_t current_pos_y, uint8_t id) const override {
        ProjectileInfoMsg* msg = new ProjectileInfoMsg(trail, current_pos_x, current_pos_y, id);
        senders.broadcast(msg);
        std::stringstream ss;
        for (auto& coor: trail) {
            ss << std::to_string(std::get<0>(coor)) << " , " << std::to_string(std::get<1>(coor))
               << std::endl;
        }
        std::cout << "se esta broadcasteando la posicion de un proyectil que es:"
                  << std::to_string(current_pos_x) << std::to_string(current_pos_y)
                  << " con trail: " << ss.str() << std::endl;
    }
    explicit ProjectileObserver(SendQueuesMonitor<GenericMsg*>& queues): Observer(queues) {}
    // virtual void update(uint8_t pos_x, uint8_t pos_y, uint8_t id) override {
    //     ProjectileInfoMsg* msg = new ProjectileInfoMsg(pos_x, pos_y, id);
    //     std::list<GenericMsg*>
    //             porquenecesitounalist;  // Preferiria poder broadcastear un mensaje a la vez
    //     porquenecesitounalist.push_back(msg);
    //     senders.broadcast(porquenecesitounalist);
    // }
};

#endif
