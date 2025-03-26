#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <string>

class Subject;

class Observer {
  public:
    // Pass in the Subject that called the notify method.
    virtual void notify() = 0; 
    virtual std::string getName() = 0;

    virtual ~Observer() = default;
};

#endif
