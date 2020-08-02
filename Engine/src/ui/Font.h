#pragma once

#include "Common.h"
#include "core/string/String.h"
#include "core/Pointer.h"

#include <algorithm>
#include <objidl.h>
#include <gdiplus.h>

namespace Ghurund {
    class Font:public Pointer {
    public:
        virtual void measureText(const String& text, float width, Gdiplus::SizeF* outSize) const = 0;
    };
}