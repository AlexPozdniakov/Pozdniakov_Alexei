#pragma once
#include <vector>
#include "IObserver.h"
using std::vector;

template <class T>
class Event
{
  public:
    void Attach(IObserver<T>* observer);
    void Detach(IObserver<T>* observer);
    void Notify(const T eventArgument) const;

  private:
    vector<IObserver<T>*> eventObservers_;
};



template <class T>
void Event<T>::Attach(IObserver<T>* observer)
{
  auto iter = find(eventObservers_.begin(), eventObservers_.end(), observer);
  if (iter == eventObservers_.end())
    eventObservers_.push_back(observer);
}



template <class T>
void Event<T>::Detach(IObserver<T>* observer)
{
  auto iter = find(eventObservers_.begin(), eventObservers_.end(), observer);
  if (iter != eventObservers_.end())
    eventObservers_.erase(iter);
}



template <class T>
void Event<T>::Notify(const T eventArgument) const
{
  for (IObserver<T>* obs : eventObservers_) {
    if(obs != nullptr)
      obs->Update(eventArgument);
  }
}