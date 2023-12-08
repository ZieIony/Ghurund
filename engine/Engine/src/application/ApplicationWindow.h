#pragma once

#include "core/window/SystemWindow.h"
#include "core/input/Input.h"
#include "core/directx/SwapChain.h"
#include "graphics/Renderer.h"
#include "core/application/Application.h"

#include "application/LayerList.h"

namespace Ghurund {
    using namespace Ghurund::Core;
    using namespace Ghurund::Core::DirectX;

    class ApplicationWindow: public Ghurund::Core::SystemWindow {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ApplicationWindow::GET_TYPE();
#pragma endregion

    private:
        SwapChain* swapChain = nullptr;
        LayerList layers;
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
        ApplicationWindow(Application& app, Renderer& renderer);

        ~ApplicationWindow() {
            delete swapChain;
            swapChain = nullptr;
        }

        virtual void init(WindowManager& windowManager) override;

        inline SwapChain& getSwapChain() {
            return *swapChain;
        }

        __declspec(property(get = getSwapChain)) Ghurund::Core::DirectX::SwapChain& SwapChain;

        inline LayerList& getLayers() {
            return layers;
        }

        __declspec(property(get = getLayers)) LayerList& Layers;

        inline Application& getApplication() {
            return app;
        }

        __declspec(property(get = getApplication)) Ghurund::Application& Application;

        virtual bool onKeyEvent(const KeyEventArgs& args) override;

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& args) override;

        virtual bool onMouseMotionEvent(const MouseMotionEventArgs& args) override;

        virtual bool onMouseWheelEvent(const MouseWheelEventArgs& args) override;

        virtual void update(const uint64_t time) override;

        virtual Status paint() override;
    };
}