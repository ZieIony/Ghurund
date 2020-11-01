#pragma once

namespace Ghurund::UI {
    struct Alignment {
        enum class Horizontal {
            LEFT, RIGHT, CENTER
        };

        enum class Vertical {
            TOP, BOTTOM, CENTER
        };

        Horizontal horizontal = Horizontal::LEFT;
        Vertical vertical = Vertical::TOP;
    };
}