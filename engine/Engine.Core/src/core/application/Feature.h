#pragma once

#include "Status.h"
#include "core/Pointer.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {
    using namespace Ghurund::Core;

    class Feature:public Pointer {
    private:
        bool initialized = false;

#pragma region reflection
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();
        virtual const Ghurund::Core::Type& getType() const override { return TYPE; }
#pragma endregion

    protected:
        virtual void onInit() {}
        virtual void onUninit() {}

    public:
        virtual ~Feature() {
            uninit();
        }

        void init() {
            if (initialized)
                return;
            try {
                onInit();
                initialized = true;
            } catch (std::exception& e) {
                throw e;
            }
        }

        void uninit() {
            if (!initialized)
                return;
            onUninit();
            initialized = false;
        }

        inline bool isInitialized() const {
            return initialized;
        }

        __declspec(property(get = isInitialized)) bool Initialized;
    };
}