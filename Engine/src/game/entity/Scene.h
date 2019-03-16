#pragma once

#include "game/entity/EntityGroup.h"

namespace Ghurund {

    class Scene:public EntityGroup {
    private:
        Array<Parameter*> parameters;

    public:

        Scene():parameters(Array<Parameter*>(0)) {
            Name = _T("scene");
        }

        virtual Array<Parameter*>& getParameters() {
            return parameters;
        }

        virtual const Ghurund::Type& getType() const override {
            return Type::SCENE;
        }

        static const Array<ResourceFormat*>& getFormats() {
            static const Array<ResourceFormat*> formats = {(ResourceFormat*)& ResourceFormat::SCENE};
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*> & Formats;
    };
}