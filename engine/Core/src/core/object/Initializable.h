#pragma once

namespace Ghurund::Core {
    class Initializable {
    private:
        bool isInitialized = false;

    protected:
        virtual void onInit() = 0;

        virtual void onUninit() = 0;

    public:
        virtual ~Initializable() = default;

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
}