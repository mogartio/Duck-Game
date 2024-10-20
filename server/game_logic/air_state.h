#ifndef AIR_STATE_H
#define AIR_STATE_H
#include <memory>
#define INITIAL_FALLING_SPEED 1
#define NORMAL_FALLING_SPEED 2
#define TOTAL_JUMPS 3

class Player; // Declaracion adelantada para no tener dependencia circularl

class AirState{
    public:
        virtual int get_offset() = 0;
        virtual void jump(Player&) = 0;
        virtual void update(bool, Player&) = 0;
    };

class Grounded : public AirState{
    public:
        virtual int get_offset() override;
        virtual void jump(Player& player) override;
        virtual void update(bool, Player&) override;
    };

class Falling : public AirState{
    private:
        int falling_speed;
    public:
        Falling(): falling_speed(INITIAL_FALLING_SPEED) {}
        virtual int get_offset() override;
        virtual void jump(Player&) override;
        virtual void update(bool, Player&) override;
    };

class Jumping : public AirState{
    private:
        int jumps_left;
        bool keeps_jumping;
    public:
        Jumping(): jumps_left(TOTAL_JUMPS), keeps_jumping(true) {}
        virtual int get_offset() override;
        virtual void jump(Player&) override;
        virtual void update(bool, Player&) override;
};

#endif


