#pragma once

#include "core/string/String.h"
#include "core/math/Size.h"

namespace Ghurund::UI {
    class SizeConstraints {
    public:
        enum class Type {
            PIXELS, PERCENT
        };

    private:
        class OrientationConstraint {
        private:
            SizeConstraints::Type type;
            float value;

        public:
            OrientationConstraint(float v):type(SizeConstraints::Type::PIXELS) {
                this->value = v > 0 ? v : 0.0f;
            }

            OrientationConstraint(SizeConstraints::Type type, float v):type(type) {
                this->value = v > 0 ? v : 0.0f;
            }

            inline SizeConstraints::Type getType() const {
                return type;
            }

            __declspec(property(get = getType)) SizeConstraints::Type Type;

            inline float getValue() const {
                return value;
            }

            __declspec(property(get = getValue)) float Value;

            inline float resolve(float size) const {
                if (Type == Type::PERCENT)
                    return size * Value / 100.0f;
                return Value;
            }

            inline bool operator==(const OrientationConstraint& other) const {
                return this->type == other.type && this->value == other.value;
            }

            inline bool operator==(const OrientationConstraint& other) {
                return this->type == other.type && this->value == other.value;
            }
        };

    public:
        class Width:public OrientationConstraint {
        public:
            Width(float v):OrientationConstraint(v) {}

            Width(SizeConstraints::Type type, float v):OrientationConstraint(type, v) {}
        };

        class Height:public OrientationConstraint {
        public:
            Height(float v):OrientationConstraint(v) {}

            Height(SizeConstraints::Type type, float v):OrientationConstraint(type, v) {}
        };

        Width width;
        Height height;

        SizeConstraints(const Ghurund::Core::FloatSize& size):width(size.Width), height(size.Height) {}

        SizeConstraints(float width, float height):width(width), height(height) {}

        SizeConstraints(const Width& width, const Height& height):width(width), height(height) {}

        static SizeConstraints parse(const Ghurund::Core::AString& str) {
            return SizeConstraints(Width(0), Height(0));
        }
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::SizeConstraints>();
}