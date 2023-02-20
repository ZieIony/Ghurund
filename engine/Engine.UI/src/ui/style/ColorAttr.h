#pragma once

#include "Theme.h"

#include <stdint.h>

namespace Ghurund::UI {
    class ColorAttr:public Object {
    public:
        virtual Color getValue(const Control& owner) const = 0;

        static const Ghurund::Core::Type& GET_TYPE();

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };

    class ColorValue:public ColorAttr {
    private:
        Color value;

    public:
        ColorValue(const Color& value):value(value) {}

        virtual Color getValue(const Control& owner) const override {
            return value;
        }

        static const Ghurund::Core::Type& GET_TYPE();

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;

        virtual ColorValue* clone() const override {
            return ghnew ColorValue(value);
        }
    };

    class ColorRef:public ColorAttr {
    private:
        ColorKey key;

    public:
        ColorRef(const ColorKey& key):key(key) {}

        virtual Color getValue(const Control& owner) const override;

        static const Ghurund::Core::Type& GET_TYPE();

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;

        virtual ColorRef* clone() const override {
            return ghnew ColorRef(key);
        }
    };
}

namespace Ghurund::Core {

    template<>
    const Type& getType<Ghurund::UI::ColorAttr>();
}
