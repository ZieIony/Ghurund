#pragma once

#include "PropertyLoader.h"

#include "engine/graphics/material/Material.h"
#include "engine/graphics/material/MaterialLoader.h"

namespace Ghurund::UI {
    using namespace Ghurund::Engine;

    class MaterialPropertyLoader:public PropertyLoader {
    private:
        ResourceManager& resourceManager;
        MaterialLoader& materialLoader;

    public:
		MaterialPropertyLoader(
            ResourceManager& resourceManager,
            MaterialLoader& materialLoader
		):resourceManager(resourceManager), materialLoader(materialLoader) {
		}

        virtual const Type& getType() const override {
            return Ghurund::Core::getType<Material*>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override;

        virtual void loadElement(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) const override;
    };
}