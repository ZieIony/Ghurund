#pragma once

#include "core/collection/List.h"

#include <functional>

namespace Ghurund {
    template <class...> class Event;

    template<class SenderType>
    class Event<SenderType> {
    private:
        List<std::function<void(SenderType& sender)>> listeners;
        SenderType& owner;

    public:
        Event(SenderType& owner):owner(owner) {}

        void add(std::function<void(SenderType& sender)> listener) {
            listeners.add(listener);
        }

        void clear() {
            listeners.clear();
        }

        void invoke() {
            for (auto listener : listeners)
                listener(owner);
        }

        inline void operator()() {
            invoke();
        }
    };

    template<class SenderType, class Type>
    class Event<SenderType, Type> {
    private:
        List<std::function<void(SenderType& sender, const Type& args)>> listeners;
        SenderType& owner;

    public:
        Event(SenderType& owner):owner(owner) {}
    
        void add(std::function<void(SenderType& sender, const Type& args)> listener) {
            listeners.add(listener);
        }

        void clear() {
            listeners.clear();
        }

        void invoke(const Type& args) {
            for (auto listener : listeners)
                listener(owner, args);
        }

        inline void operator()(const Type& args) {
            invoke(args);
        }
    };
}