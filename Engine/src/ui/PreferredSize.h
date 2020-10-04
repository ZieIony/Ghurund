#pragma once

#include <algorithm>

namespace Ghurund::UI {
    struct PreferredSize {
    private:
        enum class SpecialValues {
            WRAP = -1, FILL = -2
        };

    public:
        class Width {
        private:
            float value;

            Width(SpecialValues v) {
                value = (float)v;
            }

        public:
            static const Width& WRAP;
            static const Width& FILL;

            Width(float v) {
                this->value = std::max(0.0f, v);
            }

            operator float() const {
                return value;
            }

            inline bool operator==(const Width& type) const {
                return this->value == type.value;
            }

            inline bool operator==(const Width& type) {
                return this->value == type.value;
            }
        };

        class Height {
        private:
            float value;

            Height(SpecialValues v) {
                value = (float)v;
            }

        public:
            static const Height& WRAP;
            static const Height& FILL;

            Height(float v) {
                this->value = std::max(0.0f, v);
            }

            operator float() const {
                return value;
            }

            inline bool operator==(const Height& type) const {
                return this->value == type.value;
            }

            inline bool operator==(const Height& type) {
                return this->value == type.value;
            }
        };

        Width width = Width::WRAP;
        Height height = Height::WRAP;
    };
}