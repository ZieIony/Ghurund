#pragma once

#include "core/reflection/TypeBuilder.h"
#include "core/resource/Resource.h"

#include <DirectXCollision.h>

namespace Ghurund::Engine {
    using namespace Ghurund::Core;
    using namespace ::DirectX;

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

    protected:
        BoundingBox boundingBox;

    public:
        inline const BoundingBox& getBoundingBox() const {
            return boundingBox;
        }

        __declspec(property(get = getBoundingBox)) const BoundingBox& BoundingBox;
    };
}
