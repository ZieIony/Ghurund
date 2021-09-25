#pragma once

#include <functional>

namespace Ghurund::Core {
    template <class...> class EventHandler;

    template<class SenderType>
    class EventHandler<SenderType> {
    private:
        static inline uint32_t ID = 1;

        uint32_t id = 0;
        std::function<bool(SenderType& sender)> lambda;

    public:
        EventHandler() {}

        EventHandler(const std::function<bool(SenderType& sender)>& lambda, uint32_t id = ID++) {
            this->lambda = lambda;
            this->id = id;
        }

        EventHandler(const EventHandler& handler) {
            id = handler.id;
            lambda = handler.lambda;
        }

        EventHandler(EventHandler&& handler) noexcept {
            id = handler.id;
            lambda = std::move(handler.lambda);
        }

        bool operator==(const EventHandler& handler) const {
            return id == handler.id;
        }

        inline bool operator()(SenderType& sender) {
            return lambda(sender);
        }

        EventHandler& operator=(const EventHandler& handler) {
            id = handler.id;
            lambda = handler.lambda;
            return *this;
        }
    };

    template<class SenderType, class Type>
    class EventHandler<SenderType, Type> {
    private:
        static inline uint32_t ID = 0;

        uint32_t id = 0;
        std::function<bool(SenderType& sender, const Type& args)> lambda;

    public:
        EventHandler() {}

        EventHandler(std::function<bool(SenderType& sender, const Type& args)> lambda, uint32_t id = ID++) {
            this->lambda = lambda;
        }

        EventHandler(const EventHandler& handler) {
            id = handler.id;
            lambda = handler.lambda;
        }

        EventHandler(EventHandler&& handler) noexcept {
            id = handler.id;
            lambda = std::move(handler.lambda);
        }

        bool operator==(const EventHandler& handler) const {
            return id == handler.id;
        }

        inline bool operator()(SenderType& sender, const Type& args) {
            return lambda(sender, args);
        }

        EventHandler& operator=(const EventHandler& handler) {
            id = handler.id;
            lambda = handler.lambda;
            return *this;
        }
    };
}