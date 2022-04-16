#pragma once

#include "core/Enum.h"
#include "core/string/String.h"
#include "core/reflection/Type.h"
#include "core/string/TextConversionUtils.h"
#include "core/logging/Logger.h"
#include "core/math/Size.h"

#include <format>
#include <regex>

namespace Ghurund::UI {
    class PreferredSize {
    public:
        enum class Type {
            WRAP, PIXELS, PERCENT, FILL, RATIO
        };

    private:
        class OrientationSize {
        private:
            PreferredSize::Type type;
            float value;

        public:
            OrientationSize(float v):type(PreferredSize::Type::PIXELS) {
                this->value = v > 0 ? v : 0.0f;
            }

            OrientationSize(PreferredSize::Type type, float v):type(type) {
                this->value = v > 0 ? v : 0.0f;
            }

            inline PreferredSize::Type getType() const {
                return type;
            }

            __declspec(property(get = getType)) PreferredSize::Type Type;

            inline float getValue() const {
                return value;
            }

            __declspec(property(get = getValue)) float Value;

            inline bool operator==(const OrientationSize& other) const {
                return this->type == other.type && this->value == other.value;
            }

            inline bool operator==(const OrientationSize& other) {
                return this->type == other.type && this->value == other.value;
            }
        };

    public:
        class Width:public OrientationSize {
        public:
            static const Width& WRAP;
            static const Width& FILL;

            Width(float v):OrientationSize(v) {}

            Width(PreferredSize::Type type, float v):OrientationSize(type, v) {}

            static Width parse(const Ghurund::Core::AString& str);
        };

        class Height:public OrientationSize {
        public:
            static const Height& WRAP;
            static const Height& FILL;

            Height(float v):OrientationSize(v) {}

            Height(PreferredSize::Type type, float v):OrientationSize(type, v) {}

            static Height parse(const Ghurund::Core::AString& str);
        };

        Width width = Width::WRAP;
        Height height = Height::WRAP;

        PreferredSize() {}

        PreferredSize(float width, float height):width(width), height(height) {}

        PreferredSize(const Width& width, const Height& height):width(width), height(height) {}

        static PreferredSize parse(const Ghurund::Core::AString& str);
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::PreferredSize>();
}