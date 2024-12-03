#ifndef OBSERVER_H
#define OBSERVER_H
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "../../../common/coordinate.h"
#include "../../../common/messages/generic_msg.h"
#include "../../comunication/send_queues_monitor.h"


namespace PlayerInfoId {
#define AIM_RIGHT 1
#define AIM_LEFT 2
#define AIM_UP 3
#define AIM_DOWN 4

#define GROUNDED 1
#define JUMPING 2
#define FALLING 3
#define SLOW_FALL 4
#define PLAYING_DEAD 5
#define TRIPPING 5

}  // namespace PlayerInfoId

class Observer {
protected:
    SendQueuesMonitor<std::shared_ptr<GenericMsg>>& senders;
    std::shared_ptr<std::set<uint>> ids;

public:
    explicit Observer(SendQueuesMonitor<std::shared_ptr<GenericMsg>>& queues,
                      std::shared_ptr<std::set<uint>> ids):
            senders(queues), ids(ids) {}
    virtual void update() const {}
    virtual void update(std::string, uint16_t, uint16_t, uint8_t, uint8_t) const {}
    virtual void update(uint8_t, uint8_t, uint8_t) const {}
    virtual void update(std::string, uint8_t) const {}
    virtual void update(std::vector<std::pair<uint8_t, uint8_t>> trail, uint8_t current_pos_x,
                        uint8_t current_pos_y, uint8_t id, uint8_t x_direction,
                        uint8_t y_direction) const {}
    virtual void updateOldPos(uint8_t, uint8_t, uint8_t) const {}
    virtual void broadcast(std::shared_ptr<GenericMsg> msg) const {
        for (auto id: *ids) {
            senders.send_to_client(msg, id);
        }
    }
    virtual void updateShot(std::string& player_name, Coordinate& position) const {};
    virtual ~Observer() = default;
};

class PlayerObserver: public Observer {
    using Observer::update;

public:
    explicit PlayerObserver(SendQueuesMonitor<std::shared_ptr<GenericMsg>>& queues,
                            std::shared_ptr<std::set<uint>> ids):
            Observer(queues, ids) {}

    virtual void update(std::string name, uint16_t pos_x, uint16_t pos_y, uint8_t state,
                        uint8_t facing_direction) const override {
        std::shared_ptr<GenericMsg> msg = std::make_shared<UpdatedPlayerInfoMsg>(
                name, std::make_pair(pos_x, pos_y), state, facing_direction);

        broadcast(msg);
    }

    virtual void update(std::string name, uint8_t id) const override {
        std::shared_ptr<GenericMsg> msg = std::make_shared<PickupDropMsg>(name, id);
        broadcast(msg);
    }
};

class ProjectileObserver: public Observer {
    using Observer::update;

public:
    virtual void update(std::vector<std::pair<uint8_t, uint8_t>> trail, uint8_t current_pos_x,
                        uint8_t current_pos_y, uint8_t id, uint8_t x_direction,
                        uint8_t y_direction) const override {

        std::shared_ptr<GenericMsg> msg = std::make_shared<ProjectileInfoMsg>(
                trail, current_pos_x, current_pos_y, id, x_direction, y_direction);
        broadcast(msg);
    }

    virtual void updateOldPos(uint8_t pos_x, uint8_t pos_y, uint8_t id) const override {
        std::shared_ptr<GenericMsg> msg =
                std::make_shared<NotProyectileInfo>(id, std::pair<uint8_t, uint8_t>(pos_x, pos_y));
        broadcast(msg);
    }

    explicit ProjectileObserver(SendQueuesMonitor<std::shared_ptr<GenericMsg>>& queues,
                                std::shared_ptr<std::set<uint>> ids):
            Observer(queues, ids) {}

    virtual void updateShot(std::string& player_name, Coordinate& position) const override {
        std::shared_ptr<GenericMsg> msg = std::make_shared<ShootMsg>(
                player_name, std::pair<uint8_t, uint8_t>(position.x, position.y));
        broadcast(msg);
    }
};

#endif
