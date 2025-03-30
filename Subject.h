#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <string>
#include <memory>
#include "Observer.h"

class Observer;

class Subject {
    protected:
        std::vector<std::shared_ptr<Observer>> observers;

    public:
        void attach(std::shared_ptr<Observer> observer);
        void detach(std::shared_ptr<Observer> observer);
        void notifyObservers();
        virtual ~Subject() = 0;
};

#endif


