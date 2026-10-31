#pragma once

#include "core/object/RefCountedObject.h"
#include "core/reflection/Type.h"

namespace Ghurund::Engine::_3D {
    using namespace Ghurund::Core;

    class Light: public RefCountedObject {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Light::GET_TYPE();
#pragma endregion
    };
}
