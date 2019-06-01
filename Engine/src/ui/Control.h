#pragma once

#include "Event.h"
#include "core/Pointer.h"
#include "core/ScopedPointer.h"
#include "game/entity/TransformedEntity.h"
#include "game/entity/Model.h"
#include "graphics/Materials.h"
#include "graphics/mesh/PlaneMesh.h"
#include "input/EventConsumer.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"

namespace Ghurund {
    struct SizeChangedEventArgs {
        float width, height;
    };

    class Layout;

    class Control:public TransformedEntity, public EventConsumer {
    protected:
        Model *model = nullptr;
        Event<SizeChangedEventArgs> onSizeChanged;
        Layout* parent = nullptr;

    public:
        ~Control() {
            if (model)
                model->release();
        }

        void init(ResourceManager &resourceManager, ResourceContext & context) {
            model = ghnew Model();
            ScopedPointer<Mesh> mesh = ghnew PlaneMesh();
            model->Mesh = mesh;
            ScopedPointer<Material> material = Materials::makeUi(resourceManager, context);
            model->Material = material;
        }

        Event<SizeChangedEventArgs>& getOnSizeChanged() {
            return onSizeChanged;
        }

        __declspec(property(get = getOnSizeChanged)) Event<SizeChangedEventArgs>& OnSizeChanged;

        virtual void setSize(float width, float height) {
            scale.x = abs(width);
            scale.y = abs(height);
            onSizeChanged.invoke(*this, {scale.x, scale.y});
        }

        void setParent(Layout* parent) {
            this->parent = parent;
        }

        Layout* getParent()const {
            return parent;
        }

        __declspec(property(get = getParent, put = setParent)) Layout* Parent;

        void setBackground(Image* image) {
            Texture* texture = ghnew Texture();
        }

        virtual void draw() {}
    };
}