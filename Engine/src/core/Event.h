#pragma once

#include "core/collection/List.h"

#include <functional>

namespace Ghurund {
    template <class...> class Event;

    template<class SenderType>
    class Event<SenderType> {
    private:
        List<std::function<bool(SenderType& sender)>> listeners;
        SenderType& owner;

    public:
        Event(SenderType& owner):owner(owner) {}

        void add(std::function<bool(SenderType& sender)> listener) {
            listeners.add(listener);
        }

        void clear() {
            listeners.clear();
        }

        bool invoke() {
            bool result = false;
            for (auto listener : listeners)
                result |= listener(owner);
            return result;
        }

        inline bool operator()() {
            return invoke();
        }
    };

    template<class SenderType, class Type>
    class Event<SenderType, Type> {
    private:
        List<std::function<bool(SenderType& sender, const Type& args)>> listeners;
        SenderType& owner;

    public:
        Event(SenderType& owner):owner(owner) {}
    
        void add(std::function<bool(SenderType& sender, const Type& args)> listener) {
            listeners.add(listener);
        }

        void clear() {
            listeners.clear();
        }

        bool invoke(const Type& args) {
            bool result = false;
            for (auto listener : listeners)
                result |= listener(owner, args);
            return result;
        }

        inline bool operator()(const Type& args) {
            return invoke(args);
        }
    };
}