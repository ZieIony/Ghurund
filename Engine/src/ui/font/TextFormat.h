#pragma once

#include "Common.h"
#include "core/string/String.h"
#include "core/SharedPointer.h"
#include "core/Size.h"
#include "Status.h"

#include <dwrite.h>
#include <wrl.h>

namespace Ghurund::UI {
    using Microsoft::WRL::ComPtr;

    class Canvas;
    class Control;
    class Graphics2D;

    class TextFormat:public Pointer {
    private:
        WString file;
        WString familyName;
        float size;
        bool italic = false, underline = false, strikethrough = false;
        uint32_t weight = 400, stretch = 0;
        WString locale;

        ComPtr<IDWriteTextFormat> textFormat;

    public:
        TextFormat(const WString& file, const WString& family, float size, unsigned int weight = 400, bool italic = false, const WString& locale = L"en-us");

        TextFormat(IDWriteTextLayout* textLayout, UINT32 position);

        Status init(Graphics2D& graphics2d);

        inline const WString& getFamilyName() const {
            return familyName;
        }

        __declspec(property(get = getFamilyName)) const WString& FamilyName;

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

        inline const WString& getLocale() const {
            return locale;
        }

        __declspec(property(get = getLocale)) const WString& Locale;

        inline IDWriteTextFormat* getFormat() {
            return textFormat.Get();
        }

        __declspec(property(get = getFormat)) IDWriteTextFormat* Format;
    };
}