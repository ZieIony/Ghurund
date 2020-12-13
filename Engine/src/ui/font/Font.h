#pragma once

#include "Common.h"
#include "core/string/String.h"
#include "core/SharedPointer.h"
#include "ui/Size.h"

#include <dwrite.h>
#include <wrl.h>

namespace Ghurund::UI {
    using Microsoft::WRL::ComPtr;

    class Canvas;
    class Control;
    class Graphics2D;

    class Font:public Pointer {
    private:
        UnicodeString file;
        UnicodeString familyName;
        float size;
        bool italic = false, underline = false, strikethrough = false;
        uint32_t weight = 400, stretch = 0;
        UnicodeString locale;

        TEXTMETRIC tm;
        ComPtr<IDWriteTextFormat> textFormat;
        Graphics2D* graphics2d = nullptr;

    public:
        Font(const UnicodeString& file, const UnicodeString& family, float size, unsigned int weight = 400, bool italic = false, const UnicodeString& locale = L"en-us");

        Font(IDWriteTextLayout* textLayout, UINT32 position);

        Status init(Graphics2D& graphics2d);

        inline const UnicodeString& getFamilyName() const {
            return familyName;
        }

        __declspec(property(get = getFamilyName)) const UnicodeString& FamilyName;

        inline float getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) float Size;

        inline bool isItalic() const {
            return italic;
        }

        __declspec(property(get = isItalic)) bool Italic;

        inline bool hasUnderline() const {
            return underline;
        }

        __declspec(property(get = hasUnderline)) bool Underline;

        inline bool hasStrikethrough() const {
            return strikethrough;
        }

        __declspec(property(get = hasStrikethrough)) bool Strikethrough;

        inline uint32_t getWeight() const {
            return weight;
        }

        __declspec(property(get = getWeight)) uint32_t Weight;

        inline uint32_t getStretch() const {
            return stretch;
        }

        __declspec(property(get = getStretch)) uint32_t Stretch;

        inline const UnicodeString& getLocale() const {
            return locale;
        }

        __declspec(property(get = getLocale)) const UnicodeString& Locale;

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
    };
}