#pragma once

#include "core/coroutine/CoroutineTask.h"

namespace Ghurund::Core {
    class Initializable {
    private:
        bool isInitialized = false;

    protected:
        virtual void onInit() {};

        virtual void onUninit() {};

    public:
        virtual ~Initializable() = 0 {};

        inline bool getIsInitialized() const {
            return isInitialized;
        }

        __declspec(property(get = getIsInitialized)) bool IsInitialized;

        inline void init() {
            if (isInitialized)
                return;
            onInit();
            isInitialized = true;
        }

        inline void uninit() {
            if (!isInitialized)
                return;
            onUninit();
            isInitialized = false;
        }
    };

    class AsyncInitializable {
    private:
        bool isInitialized = false;

    protected:
        virtual CoroutineTask<void> onInit() {
            co_return;
        };

        virtual void onUninit() {};

    public:
        virtual ~AsyncInitializable() = 0 {};

        inline bool getIsInitialized() const {
            return isInitialized;
        }

        __declspec(property(get = getIsInitialized)) bool IsInitialized;

        inline CoroutineTask<void> init() {
            if (isInitialized)
                co_return;
            co_await onInit();
            isInitialized = true;
        }

        inline void uninit() {
            if (!isInitialized)
                return;
            onUninit();
            isInitialized = false;
        }
    };
}