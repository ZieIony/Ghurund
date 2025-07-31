#pragma once

#include "core/resource/Resource.h"

namespace Ghurund::Engine {

    class IMaterial:public Ghurund::Core::Resource {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = IMaterial::GET_TYPE();
#pragma endregion

    public:
        ~IMaterial() = 0 {}
    };
}