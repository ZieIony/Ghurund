#include "ghedxpch.h"
#include "DxRenderer.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Engine::DirectX {
    const Ghurund::Core::Type& DxRenderer::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<DxRenderer>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void DxRenderer::onInit() {
    }

    void DxRenderer::onUninit() {
        uninitDxRenderer();
    }

    void DxRenderer::uninitDxRenderer() {
    }
}
