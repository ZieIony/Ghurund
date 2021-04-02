#include "ghcpch.h"
#include "Window.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund {
    /*using namespace DirectX;

    void Window::updateParameters() {
        XMFLOAT2 sizeParam = { (float)size.width, (float)size.height };
        parameterViewportSize->setValue(&sizeParam);
    }*/
    
    const Ghurund::Type& Window::GET_TYPE() {
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Window))
            .withModifiers(TypeModifier::ABSTRACT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}