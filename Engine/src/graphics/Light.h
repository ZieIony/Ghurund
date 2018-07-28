#pragma once

#include "game/Entity.h"
#include "game/Target.h"

namespace Ghurund {
    class Light: public Entity {
    private:
        Target target;

    public:
        Light() {
            Name = _T("light");

            entities.add(&target);
        }

        virtual EntityType getType() const override {
            return EntityType::LIGHT;
        }

        virtual const Array<ResourceFormat> &getFormats() const override {
            static const Array<ResourceFormat> formats = {ResourceFormat::AUTO, ResourceFormat::ENTITY};
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::MATERIAL;
        }
    };
}