#pragma once

#include "core/Pointer.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/Property.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class Control;
    class ICanvas;

    class Drawable:public Pointer {
    protected:
        Ghurund::Core::FloatSize size = { 0, 0 };
        Ghurund::Core::FloatSize preferredSize = { 0, 0 };

        Control* owner = nullptr;

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        ~Drawable() = 0 {}

        inline Ghurund::Core::FloatSize& getSize() {
            return size;
        }

        inline void setSize(const Ghurund::Core::FloatSize& size) {
            this->size = size;
        }

        inline void setSize(float width, float height) {
            size.Width = width;
            size.Height = height;
        }

        __declspec(property(get = getSize, put = setSize)) Ghurund::Core::FloatSize& Size;

        inline const FloatSize& getPreferredSize() const {
            return preferredSize;
        }

        __declspec(property(get = getPreferredSize)) const FloatSize& PreferredSize;

        inline Control* getOwner() {
            return owner;
        }

        inline void setOwner(Control* owner) {
            this->owner = owner;
        }

        __declspec(property(get = getOwner, put = setOwner)) Control* Owner;

        virtual void update(const uint64_t time) {}

        virtual void onDraw(ICanvas& canvas) = 0;

        void draw(ICanvas& canvas) {
            onDraw(canvas);
        }
    };
}