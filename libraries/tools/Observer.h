#pragma once

#include "Array.h"


#define MAX_LISTENERS 10


class Observable;

class Observer {
public:
    //observable - the object, calling this method
    virtual void update(Observable& observable) = 0;
};

class Observable {
    Array<Observer*> observers = Array<Observer*>(MAX_LISTENERS);

public:
    bool subscribe(Observer& observer) {
        return observers.add(&observer);
    }

    bool unsubscribe(Observer& observer) {
        return observers.remove(&observer);
    }

protected:
    void notifyObservers() {
        for (uint16_t i = 0; i < observers.size(); i++) {
            (*observers.get(i)).update(*this);
        }
    }
};