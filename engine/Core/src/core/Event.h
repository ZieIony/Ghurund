#pragma once

#include "EventHandler.h"
#include "core/collection/List.h"

namespace Ghurund::Core {
    template <class SenderType, typename ReturnType, typename...> class Event;

    template<class SenderType>
    class Event<SenderType, bool> {
    public:
        typedef EventHandler<SenderType, bool> handler_t;
    
    private:
        List<handler_t> listeners;
        SenderType& owner;

    public:
        Event(SenderType& owner):owner(owner) {}

        inline void addListener(const handler_t& listener) {
            listeners.add(listener);
        }

        inline Event<SenderType, bool>& operator+=(const handler_t& listener) {
            listeners.add(listener);
            return *this;
        }

        inline void removeListener(const handler_t& listener) {
            listeners.remove(listener);
        }

        inline Event<SenderType, bool>& operator-=(const handler_t& listener) {
            listeners.remove(listener);
            return *this;
        }

        inline void clear() {
            listeners.clear();
        }

        inline bool invoke() const {
            bool result = false;
            for (auto& listener : listeners)
                result |= listener(owner);
            return result;
        }

        inline bool operator()() const {
            return invoke();
        }
    };

    template<class SenderType>
    class Event<SenderType, void> {
    public:
        typedef EventHandler<SenderType, void> handler_t;

    private:
        List<handler_t> listeners;
        SenderType& owner;

    public:
        Event(SenderType& owner):owner(owner) {}

        inline void addListener(const handler_t& listener) {
            listeners.add(listener);
        }

        inline Event<SenderType, void>& operator+=(const handler_t& listener) {
            listeners.add(listener);
            return *this;
        }

        inline void removeListener(const handler_t& listener) {
            listeners.remove(listener);
        }

        inline Event<SenderType, void>& operator-=(const handler_t& listener) {
            listeners.remove(listener);
            return *this;
        }

        inline void clear() {
            listeners.clear();
        }

        inline void invoke() const {
            for (auto& listener : listeners)
                listener(owner);
        }

        inline void operator()() const {
            invoke();
        }
    };

    template<class SenderType, typename ArgsType>
    class Event<SenderType, bool, ArgsType> {
    private:
        List<EventHandler<SenderType, bool, ArgsType>> listeners;
        SenderType& owner;

    public:
        using args_t = ArgsType;

        Event(SenderType& owner):owner(owner) {}

        inline void add(const EventHandler<SenderType, bool, ArgsType>& listener) {
            listeners.add(listener);
        }

        inline Event<SenderType, bool, ArgsType>& operator+=(const EventHandler<SenderType, bool, ArgsType>& listener) {
            listeners.add(listener);
            return *this;
        }

        inline void remove(const EventHandler<SenderType, bool, ArgsType>& listener) {
            listeners.remove(listener);
        }

        inline Event<SenderType, bool, ArgsType> operator-=(const EventHandler<SenderType, bool, ArgsType>& listener) {
            listeners.remove(listener);
            return *this;
        }

        inline void clear() {
            listeners.clear();
        }

        inline bool invoke(const ArgsType& args) const {
            bool result = false;
            for (auto& listener : listeners)
                result |= listener(owner, args);
            return result;
        }

        inline bool operator()(const ArgsType& args) const {
            return invoke(args);
        }
    };

    template<class SenderType, typename ArgsType>
    class Event<SenderType, void, ArgsType> {
    private:
        List<EventHandler<SenderType, void, ArgsType>> listeners;
        SenderType& owner;

    public:
        using args_t = ArgsType;

        Event(SenderType& owner):owner(owner) {}

        inline void addListener(const EventHandler<SenderType, void, ArgsType>& listener) {
            listeners.add(listener);
        }

        inline Event<SenderType, void, ArgsType>& operator+=(const EventHandler<SenderType, void, ArgsType>& listener) {
            listeners.add(listener);
            return *this;
        }

        inline void removeListener(const EventHandler<SenderType, void, ArgsType>& listener) {
            listeners.remove(listener);
        }

        inline Event<SenderType, void, ArgsType> operator-=(const EventHandler<SenderType, void, ArgsType>& listener) {
            listeners.remove(listener);
            return *this;
        }

        inline void clear() {
            listeners.clear();
        }

        inline void invoke(const ArgsType& args) const {
            for (auto& listener : listeners)
                listener(owner, args);
        }

        inline void operator()(const ArgsType& args) const {
            return invoke(args);
        }
    };
}
