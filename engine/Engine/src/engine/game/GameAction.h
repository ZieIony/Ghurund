#pragma once

namespace Ghurund::Engine {
	class GameAction {
    protected:
        virtual void onStarted() {}

        virtual void onInProgress() {}

        virtual void onFinished() {}

    public:
        virtual ~GameAction() = 0 {}

        void dispatchStarted() {
            onStarted();
        }

        void dispatchInProgress() {
            onInProgress();
        }

        void dispatchFinished() {
            onFinished();
        }
    };

    class FloatGameAction:public GameAction {
    private:
        float value;

    public:
        FloatGameAction(float value):value(value) {}

        inline float getValue() const {
            return value;
        }

        __declspec(property(get = getValue)) float Value;
    };
}