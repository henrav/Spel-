//
// Created by Henrik Ravnborg on 2025-09-08.
//

#ifndef UNTITLED13_EVENTBUSS_H
#define UNTITLED13_EVENTBUSS_H

#endif //UNTITLED13_EVENTBUSS_H
#include "iostream"
template<typename ...Args>
struct EventSignal{

    EventSignal(std::function<void(Args...)> func) : set(true), func(func) {};

private:
    bool set;
    std::function<void(Args...)> func;


};