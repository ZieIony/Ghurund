#pragma once

#include "core/reflection/Type.h"
#include "engine/graphics/mesh/Mesh.h"
#include "text/ITextMeshFactory.h"

namespace Ghurund::Core {
    class ResourceManager;
    class Window;
}

namespace Ghurund::UI {
    using namespace Ghurund::Engine;

    class UIContext {
    private:
        Ghurund::Core::Window& window;
        ITextMeshFactory& textMeshFactory;
        class IGraphicsResourceFactory& resourceFactory;

    public:
        UIContext(
            Ghurund::Core::Window& window,
            ITextMeshFactory& textMeshFactory,
            IGraphicsResourceFactory& resourceFactory
        ):window(window), textMeshFactory(textMeshFactory), resourceFactory(resourceFactory) {}

        inline Ghurund::Core::Window& getWindow() {
            return window;
        }

        __declspec(property(get = getWindow)) Ghurund::Core::Window& Window;

        virtual Mesh* makeControlMesh() = 0;

        inline ITextMeshFactory& getTextMeshFactory() const {
            return textMeshFactory;
        }

        __declspec(property(get = getTextMeshFactory)) ITextMeshFactory& TextMeshFactory;

        inline IGraphicsResourceFactory& getResourceFactory() const {
            return resourceFactory;
        }

        __declspec(property(get = getResourceFactory)) IGraphicsResourceFactory& ResourceFactory;
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::UIContext>();
}