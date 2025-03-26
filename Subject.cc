#include "Subject.h"
#include "Observer.h"
#include <vector>
#include <algorithm>

void Subject::attach(Observer *observer) {
    observers.emplace_back(observer); 
}

void Subject::detach(Observer *observer) {
    for (auto it = observers.begin(); it != observers.end();) {
      if (*it == observer) {
        it = observers.erase(it);
      }
      else {
        ++it;
      }
    }
} 


void Subject::notifyObservers() {
    for ( auto &ob : observers ) {
        ob->notify( *this );
    }
} // Subject::notifyObservers

