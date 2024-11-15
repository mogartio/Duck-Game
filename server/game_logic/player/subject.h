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
    std::list<const PlayerObserver*> observers;

public:
    PlayerSubject() {}
    void attach(const PlayerObserver& obs) { observers.push_back(&obs); }
    void dettach(const PlayerObserver& obs) { observers.remove(&obs); }
};

class ProjectileSubject: public Subject {
protected:
    std::list<const ProjectileObserver*> observers;

public:
    ProjectileSubject() {}
    void attach(const ProjectileObserver& obs) { observers.push_back(&obs); }
    void dettach(const ProjectileObserver& obs) { observers.remove(&obs); }
};
#endif
