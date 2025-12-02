#pragma once

#include "PropertyLoader.h"
#include "engine/graphics/material/IMaterial.h"
#include <engine/graphics/material/IMaterialFactory.h>

namespace Ghurund::UI {
    using namespace Ghurund::Engine;

    class MaterialPropertyLoader:public PropertyLoader {
    private:
        ResourceManager& resourceManager;
        IMaterialFactory& materialFactory;

    public:
        MaterialPropertyLoader(
            ResourceManager& resourceManager,
            IMaterialFactory& materialFactory
		):resourceManager(resourceManager), materialFactory(materialFactory) {
		}

        virtual const Type& getType() const override {
            return Ghurund::Core::getType<IMaterial*>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override;

        virtual void loadElement(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) const override;
    };
}