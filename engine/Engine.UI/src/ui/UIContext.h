#pragma once

#include <d2d1_3.h>
#include <dwrite.h>

namespace Ghurund::Core {
    class ResourceManager;
    class Window;
}

namespace Ghurund::UI {
    class UIContext {
    private:
        ID2D1Factory6& d2dFactory;
        IDWriteFactory& dwriteFactory;
        ID2D1DeviceContext5& deviceContext;
        Ghurund::Core::Window& window;
        Ghurund::Core::ResourceManager& manager;

    public:
        UIContext(
            ID2D1Factory6& d2dFactory,
            IDWriteFactory& dwriteFactory,
            ID2D1DeviceContext5& deviceContext,
            Ghurund::Core::Window& window,
            Ghurund::Core::ResourceManager& manager
        ):d2dFactory(d2dFactory), dwriteFactory(dwriteFactory), deviceContext(deviceContext), window(window), manager(manager) {}

        inline ID2D1Factory6& getD2dFactory() {
            return d2dFactory;
        }

        __declspec(property(get = getD2dFactory)) ID2D1Factory6& D2DFactory;

        inline IDWriteFactory& getDWriteFactory() {
            return dwriteFactory;
        }

        __declspec(property(get = getDWriteFactory)) IDWriteFactory& DWriteFactory;

        inline ID2D1DeviceContext5& getDeviceContext() {
            return deviceContext;
        }

        __declspec(property(get = getDeviceContext)) ID2D1DeviceContext5& DeviceContext;

        inline Ghurund::Core::Window& getWindow() {
            return window;
        }

        __declspec(property(get = getWindow)) Ghurund::Core::Window& Window;

        inline Ghurund::Core::ResourceManager& getResourceManager() {
            return manager;
        }

        __declspec(property(get = getResourceManager)) Ghurund::Core::ResourceManager& ResourceManager;
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::UIContext>();
}