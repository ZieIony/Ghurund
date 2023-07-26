#pragma once

#include "core/Pointer.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/Property.h"
#include "ui/Color.h"

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

        ~Drawable()
        //    = 0   // TODO: a destructor cannot be abstract
        {}

        inline const FloatSize& getPreferredSize() const {
            return preferredSize;
        }

        __declspec(property(get = getPreferredSize)) const FloatSize& PreferredSize;

        virtual void update(const uint64_t time) {}

        virtual void draw(ICanvas& canvas, const Ghurund::Core::FloatSize& size, const Ghurund::UI::Color& tint) const = 0;
    };
}