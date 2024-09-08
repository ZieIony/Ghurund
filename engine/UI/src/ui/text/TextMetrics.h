#pragma once

#include <stdint.h>

namespace Ghurund::UI {
    struct TextMetrics {
        float left, top, width, height;

        float widthIncludingTrailingWhitespace;

        float layoutWidth, layoutHeight;

        uint32_t maxBidiReorderingDepth;

        uint32_t lineCount;
    };

    struct LineMetrics {
        uint32_t length;
        uint32_t trailingWhitespaceLength;
        uint32_t newlineLength;

        float height;
        float baseline;

        bool isTrimmed;
    };

    struct HitTestMetrics {
        uint32_t textPosition, length;
        float left, top, width, height;
    };

    struct ClusterMetrics {
        uint32_t length;
        bool canWrapLineAfter;
    };
}