#pragma once

#include "ui/control/Control.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/Property.h"

namespace Ghurund::UI {
    class Drawable:public Pointer {
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

    protected:
        Ghurund::Core::FloatSize size = { 0, 0 };
        PreferredSize preferredSize;

        Control* owner = nullptr;

    public:
        ~Drawable() = 0 {}

        inline Ghurund::Core::FloatSize& getSize() {
            return size;
        }

        inline void setSize(const Ghurund::Core::FloatSize& size) {
            this->size = size;
        }

        inline void setSize(float width, float height) {
            size.width = width;
            size.height = height;
        }

        __declspec(property(get = getSize, put = setSize)) Ghurund::Core::FloatSize& Size;

        inline const PreferredSize& getPreferredSize() const {
            return preferredSize;
        }

        __declspec(property(get = getPreferredSize)) const PreferredSize& PreferredSize;

        inline Control* getOwner() {
            return owner;
        }

        inline void setOwner(Control* owner) {
            this->owner = owner;
        }

        __declspec(property(get = getOwner, put = setOwner)) Control* Owner;

        virtual void update(const uint64_t time) {}

        virtual void onDraw(Canvas& canvas) = 0;

        void draw(Canvas& canvas) {
            onDraw(canvas);
        }
    };
}