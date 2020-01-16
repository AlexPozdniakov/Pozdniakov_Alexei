#pragma once

template <class T>
class IObserver
{
  public:
    virtual ~IObserver() {}
    virtual void update(const T) = 0;
};