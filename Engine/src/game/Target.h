#pragma once

#include "Entity.h"

namespace Ghurund {
    class Target:public Entity {
    private:
        static const List<ResourceFormat> formats;

    public:
        Target() {
            Name = _T("target");
        }

        virtual EntityType getType() const override {
            return EntityType::TARGET;
        }

        virtual const List<ResourceFormat> &getFormats() const override {
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::ENTITY;
        }
    };
}