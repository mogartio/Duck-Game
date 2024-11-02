#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"
class Subject {
protected:
    std::list<Observer*> observers;

public:
    Subject() {};
    virtual void attach(Observer* obs) { observers.push_back(obs); }
    virtual void detach(Observer* obs) { observers.remove(obs); }
    virtual void notify() {}
    virtual ~Subject() = default;
};
class PlayerSubject: public Subject {
public:
    PlayerSubject() {}
};

class ProjectileSubject: public Subject {
public:
    ProjectileSubject() {}
};
#endif
