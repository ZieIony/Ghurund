#pragma once

namespace Ghurund::Core {
    class Initializable {
    private:
        bool isInitialized = false;

    protected:
        virtual void onInit() {};

        virtual void onDeinit() {};

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

        inline void deinit() {
            if (!isInitialized)
                return;
            onDeinit();
            isInitialized = false;
        }
    };
}
