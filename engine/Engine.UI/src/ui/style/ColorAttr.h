#pragma once

#include "ui/theme/Theme.h"

#include <stdint.h>

namespace Ghurund::UI {
    class ColorAttr:public Object {
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ColorAttr::GET_TYPE();

        virtual const Color* resolve(const Theme& theme) const = 0;
    };

    class ColorValue:public ColorAttr {
    private:
        Color value;

    public:
        ColorValue(const Color& value):value(value) {}

        ColorValue(const ColorValue& other) :value(other.value) {}

        ColorValue(ColorValue&& other) noexcept :value(std::move(other.value)) {}

        virtual const Color* resolve(const Theme& theme) const override {
            return &value;
        }

        static const Ghurund::Core::Type& GET_TYPE();

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;

        ColorValue& operator=(const ColorValue& other) {
            value = other.value;
            return *this;
        }

        ColorValue& operator=(ColorValue&& other) noexcept {
            if (this == &other)
                return *this;
            value = std::move(other.value);
            return *this;
        }

        virtual ColorValue* clone() const override {
            return ghnew ColorValue(value);
        }
    };

    class ColorRef:public ColorAttr {
    private:
        ColorKey key;

    public:
        ColorRef(const ColorKey& key):key(key) {}

        ColorRef(const ColorRef& other) :key(other.key) {}

        ColorRef(ColorRef&& other) noexcept :key(std::move(other.key)) {}

        virtual const Color* resolve(const Theme& theme) const override;

        static const Ghurund::Core::Type& GET_TYPE();

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;

        ColorRef& operator=(const ColorRef& other) {
            key = other.key;
            return *this;
        }

        ColorRef& operator=(ColorRef&& other) noexcept {
            if (this == &other)
                return *this;
            key = std::move(other.key);
            return *this;
        }

        virtual ColorRef* clone() const override {
            return ghnew ColorRef(key);
        }
    };
}

namespace Ghurund::Core {

    template<>
    const Type& getType<Ghurund::UI::ColorAttr>();
}
