#pragma once

template <class T>
class IObserver
{
  public:
    virtual void Update(const T) = 0;
};