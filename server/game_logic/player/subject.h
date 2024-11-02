#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"
class Subject {
protected:
    std::list<Observer*> observers;
    GenericMsg& msg;

public:
    Subject();
    virtual void attach(Observer* obs) { observers.push_back(obs); }
    virtual void detach(Observer* obs) { observers.remove(obs); }
    virtual void notify() {}
};
class PlayerSubject: public Subject {
public:
    virtual void notify() override;
};

class ProjectileSubject: public Subject {
public:
    virtual void notify() override;
};
#endif
