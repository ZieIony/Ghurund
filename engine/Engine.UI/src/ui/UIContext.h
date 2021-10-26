#pragma once

#include "StrokeStyle.h"
#include "core/collection/Array.h"
#include "core/reflection/Type.h"
#include "ui/effects/ShadowEffect.h"
#include "ui/effects/TintEffect.h"

namespace Ghurund::Core {
    class ResourceManager;
    class Window;
}

namespace Ghurund::UI {
    class IUIContext {
    private:
        Ghurund::Core::Window& window;
        Ghurund::Core::ResourceManager& manager;

    public:
        IUIContext(
            Ghurund::Core::Window& window,
            Ghurund::Core::ResourceManager& manager
        ):window(window), manager(manager) {}

        inline Ghurund::Core::Window& getWindow() {
            return window;
        }

        __declspec(property(get = getWindow)) Ghurund::Core::Window& Window;

        inline Ghurund::Core::ResourceManager& getResourceManager() {
            return manager;
        }

        __declspec(property(get = getResourceManager)) Ghurund::Core::ResourceManager& ResourceManager;

        virtual IStrokeStyle* makeStrokeStyle(Ghurund::Core::Array<float>& dashes) = 0;

        virtual ShadowEffect* makeShadowEffect() = 0;

        virtual TintEffect* makeTintEffect() = 0;
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::IUIContext>();
}