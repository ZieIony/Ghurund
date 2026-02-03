#include "ghepch.h"
#include "GameWindow.h"

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
            viewportSizeParameter->Value = { (int32_t)ClientSize.Width, (int32_t)ClientSize.Height };
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
            Input->releaseAllKeysAndButtons();
            layers.clearFocus();
        }
        return __super::onFocusedChanged();
    }

    void GameWindow::update() {
        __super::update();
        timeParameter->Value = Timer.Time;
        layers.update(Timer.TimeMs);
        Input->dispatchGamepadEvents(Timer.TimeMs, *this);
        actionMapping.executeDispatches();
    }
}