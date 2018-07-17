#pragma once

#include "game/Entity.h"
#include "game/Target.h"

namespace Ghurund {
    class Light: public Entity {
    private:
        Target target;

        static const List<ResourceFormat> formats;

    public:
        Light() {
            Name = _T("light");

            subentities.add(&target);
        }

        virtual EntityType getType() const override {
            return EntityType::LIGHT;
        }

        virtual const List<ResourceFormat> &getFormats() const override {
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::MATERIAL;
        }
    };
}