#pragma once

#include "Theme.h"
#include "ui/control/Control.h"

#include <stdint.h>

namespace Ghurund::UI {
    class ColorAttr:public Object {
    protected:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<Pointer>(NAMESPACE_NAME, GH_STRINGIFY(ColorAttr))
                .withModifiers(TypeModifier::ABSTRACT)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    public:
        virtual Color getValue(const Control& owner) const = 0;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };

    class ColorValue:public ColorAttr {
    private:
        Color value;

    protected:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<Pointer>(NAMESPACE_NAME, GH_STRINGIFY(ColorValue))
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    public:
        ColorValue(Color value):value(value) {}

        virtual Color getValue(const Control& owner) const override {
            return value;
        }

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        virtual ColorValue* clone() const override {
            return ghnew ColorValue(value);
        }
    };

    class ColorRef:public ColorAttr {
    private:
        ColorKey key;

    protected:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<Pointer>(NAMESPACE_NAME, GH_STRINGIFY(ColorRef))
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    public:
        ColorRef(const ColorKey& key):key(key) {}

        virtual Color getValue(const Control& owner) const override {
            return owner.Theme->Colors[key];
        }

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        virtual ColorRef* clone() const override {
            return ghnew ColorRef(key);
        }
    };
}