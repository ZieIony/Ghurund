#pragma once

#include "core/Event.h"
#include "core/Pointer.h"
#include "core/ScopedPointer.h"
#include "graphics/Materials.h"
#include "graphics/entity/TransformedEntity.h"
#include "graphics/entity/Model.h"
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
        Event<Control, SizeChangedEventArgs> onSizeChanged;
        Layout* parent = nullptr;

    public:
        ~Control() {
            if (model)
                model->release();
        }

        void init(ResourceContext & context) {
            model = ghnew Model();
            ScopedPointer<Mesh> mesh = ghnew PlaneMesh();
            model->Mesh = mesh;
            ScopedPointer<Material> material = Materials::makeUi(context);
            model->Material = material;
        }

        Event<Control, SizeChangedEventArgs>& getOnSizeChanged() {
            return onSizeChanged;
        }

        __declspec(property(get = getOnSizeChanged)) Event<Control, SizeChangedEventArgs>& OnSizeChanged;

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