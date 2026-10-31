#pragma once

#include "Event_templateDeclaration.h"
#include "EventHandler_noArguments.h"
#include "core/collection/List.h"

namespace Ghurund::Core {
    template<class SenderType>
    class Event<SenderType, bool> {
    public:
        using handler_t = EventHandler<SenderType, bool>;

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
        using handler_t = EventHandler<SenderType, void>;

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

        inline void invoke() const {
            for (auto& listener : listeners)
                listener(owner);
        }

        inline void operator()() const {
            invoke();
        }
    };
}
