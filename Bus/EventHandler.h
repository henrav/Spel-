//
// Created by Henrik Ravnborg on 2025-10-30.
//
#pragma once
#ifndef UNTITLED13_EVENTHANDLER_H
#define UNTITLED13_EVENTHANDLER_H
#include "iostream"
#include "any"
struct event{};
using namespace std;
namespace handler{
    enum event{
        dmgEvent,
        moveEvent
    };

    struct eventData{};

    struct dmgEventData : public eventData{

        int amount;
        int ownerID;
        int targetID;

        dmgEventData(int amount, int ownerID, int targetID) : amount(amount), ownerID(ownerID), targetID(targetID){};
    };

    struct moveEventData : public eventData{
        int ownerID;

        moveEventData(int id) : ownerID(id){};
    };

    struct EventHandler {
        std::unordered_map<event, std::vector<std::function<void(const std::any&)>>> listeners;

        template<class F>
        void subscribe(event e, F&& f) {
            static_assert(std::is_invocable_r_v<void, F&>,
                          "subscribe(e, f): f must be void()");
            listeners[e].push_back(
                    [fn = std::forward<F>(f)](const std::any&) { std::invoke(fn); }
            );
        }

        template<class Payload, class F>
        void subscribe(event e, F&& f) {
            static_assert(std::is_invocable_r_v<void, F&, const Payload&>,
                          "subscribe<Payload>(e, f): f must be void(const Payload&)");
            listeners[e].push_back(
                    [fn = std::forward<F>(f)](const std::any& a) {
                        std::invoke(fn, std::any_cast<const Payload&>(a));
                    }
            );
        }

        template<class Payload>
        void emit(event e, Payload payload) {
            auto it = listeners.find(e);
            if (it == listeners.end()) return;
            std::any newData(std::move(payload));
            for (auto& listener : it->second) listener(newData);
        }
    };
    inline EventHandler& Bus() {
        static EventHandler instance;
        return instance;
    }
}


#endif //UNTITLED13_EVENTHANDLER_H
