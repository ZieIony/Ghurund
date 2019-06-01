#pragma once

#include "collection/List.h"
#include <functional>

namespace Ghurund {
    class Control;

    template<class Type>
    class Event {
    private:
        List<std::function<void(Control& sender, const Type& args)>> listeners;

    public:
        void add(std::function<void(Control &sender, const Type& args)> listener) {
            listeners.add(listener);
        }

        void clear() {
            listeners.clear();
        }

        void invoke(Control &sender, const Type& args) {
            for (auto listener : listeners)
                listener(sender, args);
        }
    };
}