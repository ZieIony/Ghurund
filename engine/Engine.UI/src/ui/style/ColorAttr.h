#pragma once

#include "ui/theme/Theme.h"
#include "core/Color.h"

#include <stdint.h>

namespace Ghurund::UI {
    class ColorAttr:public Object {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ColorAttr::GET_TYPE();
#pragma endregion

    public:
        virtual const Color* resolve(const Theme& theme) const = 0;
    };

    class ColorValue:public ColorAttr {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ColorValue::GET_TYPE();
#pragma endregion

    private:
        Color value;

    public:
        ColorValue(const Color& value):value(value) {}

        ColorValue(const ColorValue& other) :value(other.value) {}

        ColorValue(ColorValue&& other) noexcept :value(std::move(other.value)) {}

        virtual const Color* resolve(const Theme& theme) const override {
            return &value;
        }

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
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ColorRef::GET_TYPE();
#pragma endregion

    private:
        ColorKey key;

    public:
        ColorRef(const ColorKey& key):key(key) {}

        ColorRef(const ColorRef& other) :key(other.key) {}

        ColorRef(ColorRef&& other) noexcept :key(std::move(other.key)) {}

        virtual const Color* resolve(const Theme& theme) const override;

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
