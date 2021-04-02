#pragma once

#include "ui/control/Control.h"

namespace Ghurund::UI {
    class Drawable:public Pointer {
    protected:
        FloatSize size = { 0, 0 };
        PreferredSize preferredSize;

        Control* owner = nullptr;

    public:
        inline FloatSize& getSize() {
            return size;
        }

        inline void setSize(const FloatSize& size) {
            this->size = size;
        }

        inline void setSize(float width, float height) {
            size.width = width;
            size.height = height;
        }

        __declspec(property(get = getSize, put = setSize)) FloatSize& Size;

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