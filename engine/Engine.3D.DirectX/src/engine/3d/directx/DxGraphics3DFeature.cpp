#include "ghe3ddxpch.h"
#include "DxGraphics3DFeature.h"

namespace Ghurund::Engine::_3D::DirectX {
    const Ghurund::Core::Type& DxGraphics3DFeature::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<DxGraphics3DFeature>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
