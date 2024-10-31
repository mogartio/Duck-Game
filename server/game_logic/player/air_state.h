#ifndef AIR_STATE_H
#define AIR_STATE_H
#include <memory>
#define INITIAL_FALLING_SPEED 1
#define NORMAL_FALLING_SPEED 2
#define TOTAL_JUMPS 3

class PlayerPosition;  // Declaracion adelantada para no tener dependencia circularl

class AirState {
public:
    virtual int get_offset() = 0;
    virtual void jump(PlayerPosition&) = 0;
    virtual void stop_jumping(PlayerPosition&) {}
    virtual void update(bool, PlayerPosition&) = 0;
};

class Grounded: public AirState {
public:
    virtual int get_offset() override;
    virtual void jump(PlayerPosition& player) override;
    virtual void update(bool, PlayerPosition&) override;
};

class Falling: public AirState {
private:
    int falling_speed;

public:
    Falling(): falling_speed(INITIAL_FALLING_SPEED) {}
    virtual int get_offset() override;
    virtual void jump(PlayerPosition&) override;
    virtual void update(bool, PlayerPosition&) override;
};

class Jumping: public AirState {
private:
    int jumps_left;
    bool keeps_jumping;

public:
    Jumping(): jumps_left(TOTAL_JUMPS), keeps_jumping(true) {}
    virtual int get_offset() override;
    virtual void jump(PlayerPosition&) override;
    virtual void update(bool, PlayerPosition&) override;
    void stop_jumping(PlayerPosition&) override;
};

#endif
