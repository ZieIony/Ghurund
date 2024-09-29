#pragma once

#include "core/application/Application.h"
#include "core/application/LayerList.h"
#include "core/window/SystemWindow.h"
#include "engine/directx/DirectXDrawingContext.h"
#include "engine/directx/Renderer.h"
#include "engine/directx/SwapChain.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class DirectXWindow: public Ghurund::Core::SystemWindow {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = DirectXWindow::GET_TYPE();
#pragma endregion

    private:
        SwapChain* swapChain = nullptr;
        LayerList<DirectXDrawingContext> layers;
        Application& app;
        Renderer& renderer;

    protected:
        virtual bool onSizeChangingEvent(const IntSize& size) override {
            __super::onSizeChangingEvent(size);
            if (swapChain)
                swapChain->uninitBuffers();
            return true;
        }

        virtual bool onSizeChangedEvent() override {
            layers.Size = Size;
            if (swapChain) {
                swapChain->resize(Size);
                swapChain->initBuffers();
            }
            __super::onSizeChangedEvent();
            return true;
        }

        virtual bool onFocusedChangedEvent() override;

    public:
        DirectXWindow(Application& app, Renderer& renderer);

        ~DirectXWindow() {
            delete swapChain;
            swapChain = nullptr;
        }

        virtual void init(WindowManager& windowManager) override;

        inline SwapChain& getSwapChain() {
            return *swapChain;
        }

        __declspec(property(get = getSwapChain)) Ghurund::Engine::DirectX::SwapChain& SwapChain;

        inline LayerList<DirectXDrawingContext>& getLayers() {
            return layers;
        }

        __declspec(property(get = getLayers)) LayerList<DirectXDrawingContext>& Layers;

        inline Application& getApplication() {
            return app;
        }

        __declspec(property(get = getApplication)) Ghurund::Core::Application& Application;

        virtual bool onKeyEvent(const KeyEventArgs& args) override;

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& args) override;

        virtual bool onMouseMotionEvent(const MouseMotionEventArgs& args) override;

        virtual bool onMouseWheelEvent(const MouseWheelEventArgs& args) override;

        virtual void update(const uint64_t time) override;

        virtual void paint() override;
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<LayerList<Ghurund::Engine::DirectX::DirectXDrawingContext>>();
}