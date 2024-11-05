#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"
class Subject {
protected:
public:
    Subject() {}
    virtual void notify() {}
    virtual ~Subject() = default;
};
class PlayerSubject: public Subject {
protected:
    std::list<PlayerObserver*> observers;

public:
    PlayerSubject() {}
    void attach(PlayerObserver* obs) { observers.push_back(obs); }
    void dettach(PlayerObserver* obs) { observers.remove(obs); }
};

class ProjectileSubject: public Subject {
protected:
    std::list<ProjectileObserver*> observers;

public:
    ProjectileSubject() {}
    void attach(ProjectileObserver* obs) { observers.push_back(obs); }
    void dettach(ProjectileObserver* obs) { observers.remove(obs); }
};
#endif
