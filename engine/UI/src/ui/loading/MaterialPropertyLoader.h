#pragma once

#include "PropertyLoader.h"
#include "engine/graphics/material/IMaterial.h"

namespace Ghurund::UI {
    using namespace Ghurund::Engine;

    class MaterialPropertyLoader:public PropertyLoader {
    private:
        ResourceManager& resourceManager;

    public:
        MaterialPropertyLoader(ResourceManager& resourceManager):resourceManager(resourceManager) {}

        virtual const Type& getType() const override {
            return Ghurund::Core::getType<IMaterial*>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override;
    };
}