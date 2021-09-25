#include "ghcpch.h"
#include "Window.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {
    /*using namespace DirectX;

    void Window::updateParameters() {
        XMFLOAT2 sizeParam = { (float)size.width, (float)size.height };
        parameterViewportSize->setValue(&sizeParam);
    }*/
    
    const Ghurund::Core::Type& Window::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Window>(NAMESPACE_NAME, GH_STRINGIFY(Window))
            .withModifiers(TypeModifier::ABSTRACT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}