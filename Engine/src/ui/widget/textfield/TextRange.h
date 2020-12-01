#pragma once

#include "ui/Graphics2D.h"

namespace Ghurund::UI {
    struct TextRange: public DWRITE_TEXT_RANGE {
        TextRange(UINT32 startPosition, UINT32 length) {
            this->startPosition = startPosition;
            this->length = length;
        }

        TextRange(UINT32 startPosition) {
            this->startPosition = startPosition;
            this->length = UINT32_MAX - startPosition;
        }
    };
}
