#pragma once

#include "ui/Graphics2D.h"

namespace Ghurund::UI {
    struct CaretFormat {
        wchar_t fontFamilyName[100];
        wchar_t localeName[LOCALE_NAME_MAX_LENGTH];
        FLOAT fontSize;
        DWRITE_FONT_WEIGHT fontWeight;
        DWRITE_FONT_STRETCH fontStretch;
        DWRITE_FONT_STYLE fontStyle;
        UINT32 color;
        BOOL hasUnderline;
        BOOL hasStrikethrough;
    };
}