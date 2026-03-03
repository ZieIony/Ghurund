#pragma once

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
}