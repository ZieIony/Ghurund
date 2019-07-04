#pragma once

#include "collection/List.h"

#include <functional>

namespace Ghurund {
    template <class...> class Event;

    template<class SenderType>
    class Event<SenderType> {
    private:
        List<std::function<void(SenderType& sender)>> listeners;

    public:
        void add(std::function<void(SenderType& sender)> listener) {
            listeners.add(listener);
        }

        void clear() {
            listeners.clear();
        }

        void invoke(SenderType& sender) {
            for (auto listener : listeners)
                listener(sender);
        }

        inline void operator()(SenderType& sender) {
            invoke(sender);
        }
    };

    template<class SenderType, class Type>
    class Event<SenderType, Type> {
    private:
        List<std::function<void(SenderType& sender, const Type& args)>> listeners;

    public:
        void add(std::function<void(SenderType& sender, const Type& args)> listener) {
            listeners.add(listener);
        }

        void clear() {
            listeners.clear();
        }

        void invoke(SenderType& sender, const Type& args) {
            for (auto listener : listeners)
                listener(sender, args);
        }

        inline void operator()(SenderType& sender, const Type& args) {
            invoke(sender, args);
        }
    };
}