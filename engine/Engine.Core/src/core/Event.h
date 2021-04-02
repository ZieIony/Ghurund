#pragma once

#include "EventHandler.h"
#include "core/collection/List.h"

namespace Ghurund {
    template <class...> class Event;

    template<class SenderType>
    class Event<SenderType> {
    private:
        List<EventHandler<SenderType>> listeners;
        SenderType& owner;

    public:
        Event(SenderType& owner):owner(owner) {}

        inline void add(std::function<bool(SenderType& sender)> lambda) {
            listeners.add(lambda);
        }

        inline void add(const EventHandler<SenderType>& listener) {
            listeners.add(listener);
        }

        inline void remove(const EventHandler<SenderType>& listener) {
            size_t i = listeners.indexOf(listener);
            if (i == listeners.Size)
                return;
            listeners.removeAt(i);
        }

        inline void clear() {
            listeners.clear();
        }

        inline bool invoke() {
            bool result = false;
            for (auto& listener : listeners)
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
        List<EventHandler<SenderType, Type>> listeners;
        SenderType& owner;

    public:
        Event(SenderType& owner):owner(owner) {}

        inline void add(std::function<bool(SenderType& sender, const Type& args)> lambda) {
            listeners.add(lambda);
        }

        inline void add(const EventHandler<SenderType, Type>& listener) {
            listeners.add(listener);
        }

        inline void remove(const EventHandler<SenderType, Type>& listener) {
            listeners.remove(listener);
        }

        void clear() {
            listeners.clear();
        }

        bool invoke(const Type& args) {
            bool result = false;
            for (auto& listener : listeners)
                result |= listener(owner, args);
            return result;
        }

        inline bool operator()(const Type& args) {
            return invoke(args);
        }
    };
}