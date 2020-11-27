#pragma once

#include "Common.h"
#include "core/string/String.h"
#include "core/ScopedPointer.h"
#include "ui/Size.h"

#include <dwrite.h>
#include <wrl.h>

namespace Ghurund::UI {
    using Microsoft::WRL::ComPtr;
    
    class Canvas;
    class Control;
    class Graphics2D;

    class TextSelection {
    public:
        Control* control;
        size_t index = 0;
        float x;
    };

    class Font:public Pointer {
    private:
        float size;
        String familyName;
        bool italic = false;
        unsigned int weight = 400;

        TEXTMETRIC tm;
        ComPtr<IDWriteTextFormat> textFormat;
        Graphics2D* graphics2d = nullptr;

    public:
        Font(const String& file, const String& family, float size, unsigned int weight = 400, bool italic = false);

        Status init(Graphics2D& graphics2d);

        long getAscent() const {
            return tm.tmAscent;
        }

        long getDescent() const {
            return tm.tmDescent;
        }

        long getInternalLeading() const {
            return tm.tmInternalLeading;
        }

        long getExternalLeading() const {
            return tm.tmExternalLeading;
        }

        long getHeight() const {
            return tm.tmHeight;
        }

        inline IDWriteTextFormat* getTextFormat() {
            return textFormat.Get();
        }

        __declspec(property(get = getTextFormat)) IDWriteTextFormat* TextFormat;

        IDWriteTextLayout* makeLayout(UnicodeString& text, float width, float height);
    };
}