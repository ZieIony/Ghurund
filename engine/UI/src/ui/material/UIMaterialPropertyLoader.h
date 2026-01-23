#pragma once

#include "core/loading/PropertyLoader.h"
#include "ui/material/UIMaterialLoader.h"

namespace Ghurund::UI {
    using namespace Ghurund::Engine;

    class UIMaterialPropertyLoader:public PropertyLoader {
    private:
        static inline const char* THEME_MATERIAL = "theme://material/";
  
        ResourceManager& resourceManager;
        UIMaterialLoader& materialLoader;

    public:
		UIMaterialPropertyLoader(
            ResourceManager& resourceManager,
            UIMaterialLoader& materialLoader
		):resourceManager(resourceManager), materialLoader(materialLoader) {
		}

        virtual const Type& getType() const override {
            return Ghurund::Core::getType<std::unique_ptr<ThemedMaterial>>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override;

        virtual void loadElement(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) const override;
    };
}