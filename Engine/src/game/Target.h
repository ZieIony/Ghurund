#pragma once

#include "Entity.h"

namespace Ghurund {
    class Target:public Entity {
    public:
        Target() {
            Name = _T("target");
        }

        virtual EntityType getType() const override {
            return EntityType::TARGET;
        }

        virtual const Array<ResourceFormat> &getFormats() const override {
            static const Array<ResourceFormat> formats = {ResourceFormat::AUTO, ResourceFormat::ENTITY};
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::ENTITY;
        }
    };
}