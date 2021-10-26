#pragma once

#include "core/string/String.h"

namespace Ghurund::UI {
    class Alignment {
    public:
        enum class Horizontal {
            LEFT, RIGHT, CENTER
        };

        enum class Vertical {
            TOP, BOTTOM, CENTER
        };

        Horizontal horizontal = Horizontal::LEFT;
        Vertical vertical = Vertical::TOP;

        bool operator==(const Alignment& alignment) const {
            return horizontal == alignment.horizontal && vertical == alignment.vertical;
        }

        static Alignment parse(const Ghurund::Core::AString& alignment);
    };
}