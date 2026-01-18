#pragma once

#include "core/reflection/TypeBuilder.h"
#include "core/resource/Resource.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    // this is just a common type for meshes used by RenderingContext
    class Mesh:public Resource {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<Mesh>()
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        inline static const Ghurund::Core::Type& TYPE = Mesh::GET_TYPE();
#pragma endregion
    };
}