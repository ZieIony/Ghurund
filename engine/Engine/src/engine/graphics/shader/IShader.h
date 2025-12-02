#pragma once

#include "core/resource/Resource.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class IShader:public Resource {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = IShader::GET_TYPE();
#pragma endregion

    protected:
        bool isTransparencyEnabled = false;

    public:
        bool getIsTransparencyEnabled() {
            return isTransparencyEnabled;
        }

        __declspec(property(get = getIsTransparencyEnabled)) bool IsTransparencyEnabled;
    };
}