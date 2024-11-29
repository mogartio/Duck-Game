#ifndef AIR_STATE_H
#define AIR_STATE_H
#include <memory>

#include "../../config/config.h"
#define INITIAL_FALLING_SPEED 0
#define NORMAL_FALLING_SPEED 1

class PlayerPosition;  // Declaracion adelantada para no tener dependencia circularl

class AirState {
public:
    virtual int get_offset() = 0;
    virtual void jump(PlayerPosition&) = 0;
    virtual void stop_jumping(PlayerPosition&) {}
    virtual void update(bool, PlayerPosition&) = 0;
    virtual int get_x_offset() { return 0; };
    virtual ~AirState() = default;
};

class Grounded: public AirState {
private:
    bool stopped_jumping;

public:
    explicit Grounded(bool stopped_jumping): stopped_jumping(stopped_jumping) {}
    virtual int get_offset() override;
    virtual void jump(PlayerPosition& player) override;
    virtual void update(bool, PlayerPosition&) override;
    virtual void stop_jumping(PlayerPosition&) override;
};

class Falling: public AirState {
private:
    int falling_speed;
    bool stopped_jumping;

public:
    Falling(): falling_speed(INITIAL_FALLING_SPEED), stopped_jumping(true) {}
    virtual int get_offset() override;
    virtual void jump(PlayerPosition&) override;
    virtual void update(bool, PlayerPosition&) override;
    virtual void stop_jumping(PlayerPosition&) override;
};

class Jumping: public AirState {
private:
    int jumps_left;
    bool keeps_jumping;

public:
    Jumping(): jumps_left(Config::get_instance()->player_jumping_height), keeps_jumping(true) {}
    virtual int get_offset() override;
    virtual void jump(PlayerPosition&) override;
    virtual void update(bool, PlayerPosition&) override;
    void stop_jumping(PlayerPosition&) override;
};

class PlayingDead: public AirState {
public:
    PlayingDead() {}
    virtual int get_offset() override;
    virtual void jump(PlayerPosition&) override;
    virtual void update(bool, PlayerPosition&) override;
    virtual void stop_jumping(PlayerPosition&) override {};
};

class Tripping: public AirState {
private:
    int stun_duration;
    int turns_stunned;
    int x_direction;    // para donde esta cayendo
    int falling_speed;  // por si esta cayendo mientras esta stunneado
public:
    Tripping(int x_direction):
            stun_duration(Config::get_instance()->stun_duration),
            x_direction(x_direction),
            falling_speed(0) {}
    virtual int get_offset() override;
    virtual void jump(PlayerPosition&) override;
    virtual void update(bool, PlayerPosition&) override;
    virtual void stop_jumping(PlayerPosition&) override {};
    virtual int get_x_offset() override { return x_direction; };
};

#endif
