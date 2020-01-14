#pragma once

template <class T>
class IObserver abstract
{
  public:
    virtual void Update(T) = 0;
};