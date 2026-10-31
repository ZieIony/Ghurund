#pragma once

#include "Event_templateDeclaration.h"
#include "EventHandler_withArguments.h"
#include "core/collection/List.h"

namespace Ghurund::Core {
    template<class SenderType, typename ArgsType>
    class Event<SenderType, bool, ArgsType> {
    public:
        using handler_t = EventHandler<SenderType, bool, ArgsType>;

    private:
        List<handler_t> listeners;
        SenderType& owner;

    public:
        Event(SenderType& owner):owner(owner) {}

        inline void add(const handler_t& listener) {
            listeners.add(listener);
        }

        inline Event& operator+=(const handler_t& listener) {
            listeners.add(listener);
            return *this;
        }

        inline void remove(const handler_t& listener) {
            listeners.remove(listener);
        }

        inline Event& operator-=(const handler_t& listener) {
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
    public:
        using handler_t = EventHandler<SenderType, void, ArgsType>;

    private:
        List<handler_t> listeners;
        SenderType& owner;

    public:
        Event(SenderType& owner):owner(owner) {}

        inline void addListener(const handler_t& listener) {
            listeners.add(listener);
        }

        inline Event& operator+=(const handler_t& listener) {
            listeners.add(listener);
            return *this;
        }

        inline void removeListener(const handler_t& listener) {
            listeners.remove(listener);
        }

        inline Event& operator-=(const handler_t& listener) {
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
