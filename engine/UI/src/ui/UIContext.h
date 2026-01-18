#pragma once

#include "core/reflection/Type.h"
#include "engine/graphics/mesh/Mesh.h"
#include "engine/graphics/texture/ITextureFactory.h"
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
        ITextureFactory& textureFactory;

    public:
        UIContext(
            Ghurund::Core::Window& window,
            ITextMeshFactory& textMeshFactory,
            ITextureFactory& textureFactory
        ):window(window), textMeshFactory(textMeshFactory), textureFactory(textureFactory) {}

        inline Ghurund::Core::Window& getWindow() {
            return window;
        }

        __declspec(property(get = getWindow)) Ghurund::Core::Window& Window;

        virtual Mesh* makeControlMesh() = 0;

        inline ITextMeshFactory& getTextMeshFactory() const {
            return textMeshFactory;
        }

        __declspec(property(get = getTextMeshFactory)) ITextMeshFactory& TextMeshFactory;

        inline ITextureFactory& getTextureFactory() const {
            return textureFactory;
        }

        __declspec(property(get = getTextureFactory)) ITextureFactory& TextureFactory;
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::UIContext>();
}