#include "ghepch.h"
#include "GameWindow.h"

#include "GameApplication.h"

#include "core/reflection/Property.h"

#include <windowsx.h>

namespace Ghurund::Engine {
    const Ghurund::Core::Type& GameWindow::GET_TYPE() {
        static auto PROPERTY_LAYERS = Property<GameWindow, LayerList&>("Layers", &getLayers);
        static auto PROPERTY_RENDERER = Property<GameWindow, Ghurund::Engine::Renderer*>("Renderer", &getRenderer, &setRenderer);
     
        static const Ghurund::Core::Type TYPE = TypeBuilder<GameWindow>()
            .withProperty(PROPERTY_LAYERS)
            .withProperty(PROPERTY_RENDERER)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
    
    bool GameWindow::onMouseButtonEvent(const MouseButtonEventArgs& args) {
        bool consumed = layers.dispatchMouseButtonEvent(args);
        if (consumed && (IsLButtonDown() || IsMButtonDown() || IsRButtonDown())) {
            SetCapture(Handle);
        } else {
            ReleaseCapture();
        }
        return consumed || actionMapping.onMouseButtonEvent(args);
    }

    bool GameWindow::onSizeChanged() {
        __super::onSizeChanged();
        layers.Size = Size;
        if (renderingContext) {
            renderingContext->Size = ClientSize;
            return true;
        } else {
            return false;
        }
    }

    bool GameWindow::onFocusedChanged() {
        if (!Focused)
            actionMapping.cancelAll();
        if (Focused) {
            layers.restoreFocus();
        } else {
            layers.clearFocus();
        }
        return __super::onFocusedChanged();
    }

    void GameWindow::fixedUpdate() {
        systems.fixedUpdate(Timer);
    }

    void GameWindow::update() {
        renderingContext->globalParameters.time = (float)Timer.ApplicationTime.scaledValue;
        layers.update(Timer);
        systems.update(Timer);
        Input->dispatchGamepadEvents(Timer.ApplicationTime.valueMs, *this);
        actionMapping.executeDispatches();
    }
    
    void GameWindow::paint() {
        if (!renderingContext)
            return;

        renderingContext->startFrame();
        renderingContext->clear(BackgroundColor);
        systems.queueDraw(*renderingContext);
        layers.draw(*renderingContext);
        renderingContext->finishFrame();
    }
}
