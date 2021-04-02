#pragma once

namespace Ghurund {
    template<class Type>
    class ObservableHandler {
    private:
        static inline uint32_t ID = 0;

        uint32_t id = 0;
        std::function<void(const Type& args)> lambda;

    public:
        ObservableHandler() {}

        ObservableHandler(std::function<void(const Type& args)> lambda, uint32_t id = ID++) {
            this->lambda = lambda;
        }

        ObservableHandler(const ObservableHandler& handler) {
            id = handler.id;
            lambda = handler.lambda;
        }

        ObservableHandler(ObservableHandler&& handler) noexcept {
            id = handler.id;
            lambda = std::move(handler.lambda);
        }

        bool operator==(const ObservableHandler& handler) const {
            return id == handler.id;
        }

        inline bool operator()(const Type& args) {
            return lambda(args);
        }

        ObservableHandler& operator=(const ObservableHandler& handler) {
            id = handler.id;
            lambda = handler.lambda;
            return *this;
        }
    };
}