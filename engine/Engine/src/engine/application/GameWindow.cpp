#include "ghepch.h"
#include "GameWindow.h"

#include "core/reflection/Property.h"

namespace Ghurund::Engine {
    const Ghurund::Core::Type& GameWindow::GET_TYPE() {
        static auto PROPERTY_RENDERER = Property<GameWindow, Ghurund::Engine::Renderer*>("Renderer", &getRenderer, &setRenderer);
     
        static const Ghurund::Core::Type TYPE = TypeBuilder<GameWindow>()
            .withProperty(PROPERTY_RENDERER)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
    
    bool GameWindow::onSizeChanged() {
        __super::onSizeChanged();
        if (renderingContext) {
            renderingContext->setSize(Size);
            return true;
        } else {
            return false;
        }
    }
}