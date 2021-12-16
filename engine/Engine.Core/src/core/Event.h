#pragma once

#include "EventHandler.h"
#include "core/collection/List.h"

namespace Ghurund::Core {
    template <class...> class Event;

    template<class SenderType>
    class Event<SenderType> {
    private:
        List<EventHandler<SenderType>> listeners;
        SenderType& owner;

    public:
        Event(SenderType& owner):owner(owner) {}

        inline void add(const std::function<bool(SenderType& sender)>& lambda) {
            listeners.add(lambda);
        }

        inline Event<SenderType>& operator+=(const std::function<bool(SenderType& sender)>& lambda) {
            listeners.add(lambda);
            return *this;
        }

        inline void add(const EventHandler<SenderType>& listener) {
            listeners.add(listener);
        }

        inline Event<SenderType>& operator+=(const EventHandler<SenderType>& listener) {
            listeners.add(listener);
            return *this;
        }

        inline void remove(const EventHandler<SenderType>& listener) {
            size_t i = listeners.indexOf(listener);
            if (i == listeners.Size)
                return;
            listeners.removeAt(i);
        }

        inline Event<SenderType>& operator-=(const EventHandler<SenderType>& listener) {
            listeners.remove(listener);
            return *this;
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

        inline void add(const std::function<bool(SenderType& sender, const Type& args)>& lambda) {
            listeners.add(lambda);
        }

        inline Event<SenderType, Type>& operator+=(const std::function<bool(SenderType& sender, const Type& args)>& lambda) {
            listeners.add(lambda);
            return *this;
        }

        inline void add(const EventHandler<SenderType, Type>& listener) {
            listeners.add(listener);
        }

        inline Event<SenderType, Type>& operator+=(const EventHandler<SenderType, Type>& listener) {
            listeners.add(listener);
            return *this;
        }

        inline void remove(const EventHandler<SenderType, Type>& listener) {
            listeners.remove(listener);
        }

        inline Event<SenderType, Type> operator-=(const EventHandler<SenderType, Type>& listener) {
            listeners.remove(listener);
            return *this;
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