#pragma once

#include "EventHandler_templateDeclaration.h"

#include "core/concepts/Callable.h"

#include <functional>
#include <type_traits>

namespace Ghurund::Core {
    template<class SenderType, typename ReturnType, typename ArgsType>
    class EventHandler<SenderType, ReturnType, ArgsType> {
    private:
        static inline uint32_t ID = 0;

        uint32_t id = 0;
        std::function<ReturnType(SenderType& sender, const ArgsType& args)> function;

    public:
        template<Callable<ReturnType, SenderType&, const ArgsType&> Type>
        EventHandler(Type&& function, uint32_t id = ID++) {
            this->function = std::forward<Type>(function);
            this->id = id;
        }

        EventHandler(const EventHandler& handler) {
            id = handler.id;
            function = handler.function;
        }

        EventHandler(EventHandler&& handler) noexcept {
            id = handler.id;
            function = std::move(handler.function);
        }

        bool operator==(const EventHandler& handler) const {
            return id == handler.id;
        }

        inline ReturnType operator()(SenderType& sender, const ArgsType& args) {
            return function(sender, args);
        }

        EventHandler& operator=(const EventHandler& handler) {
            id = handler.id;
            function = handler.function;
            return *this;
        }
    };
}
