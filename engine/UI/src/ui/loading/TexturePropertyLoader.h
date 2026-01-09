#pragma once

#include "core/loading/PropertyLoader.h"
#include "engine/graphics/texture/ITextureFactory.h"
#include "ui/style/TextureAttr.h"

namespace Ghurund::UI {
    class TexturePropertyLoader:public PropertyLoader {
    private:
        static inline const char* THEME_TEXTURE = "theme://texture/";

        ResourceManager& resourceManager;
        ITextureFactory& textureFactory;

    public:
        TexturePropertyLoader(
            ResourceManager& resourceManager,
            ITextureFactory& textureFactory
        ):resourceManager(resourceManager), textureFactory(textureFactory) {}

        virtual const Type& getType() const override {
            return Ghurund::Core::getType<std::unique_ptr<Ghurund::UI::TextureAttr>>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override;
    };
}