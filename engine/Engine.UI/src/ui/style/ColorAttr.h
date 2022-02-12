#pragma once

#include "Theme.h"

#include <stdint.h>

namespace Ghurund::UI {
    class ColorAttr:public Object {
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        virtual Color getValue(const Control& owner) const = 0;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };

    class ColorValue:public ColorAttr {
    private:
        Color value;

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        ColorValue(const Color& value):value(value) {}

        virtual Color getValue(const Control& owner) const override {
            return value;
        }

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;

        virtual ColorValue* clone() const override {
            return ghnew ColorValue(value);
        }
    };

    class ColorRef:public ColorAttr {
    private:
        ColorKey key;

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        ColorRef(const ColorKey& key):key(key) {}

        virtual Color getValue(const Control& owner) const override;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;

        virtual ColorRef* clone() const override {
            return ghnew ColorRef(key);
        }
    };
}