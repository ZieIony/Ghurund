#pragma once

#include "ui/Graphics2D.h"
#include "ui/font/Font.h"

namespace Ghurund::UI {
    class LayoutEditor {
    private:
        IDWriteFactory* factory;

    public:
        void init(IDWriteFactory* factory) {
            this->factory = factory;
        }

        Status recreateLayout(IDWriteTextLayout*& currentLayout, const UnicodeString& text);

        void copySinglePropertyRange(
            IDWriteTextLayout* oldLayout,
            UINT32 startPosForOld,
            IDWriteTextLayout* newLayout,
            UINT32 startPosForNew,
            UINT32 length,
            Font* font = nullptr
        );

        UINT32 calculateRangeLengthAt(IDWriteTextLayout* layout, UINT32 pos);

        void copyRangedProperties(
            IDWriteTextLayout* oldLayout,
            UINT32 startPos,
            UINT32 endPos, // an STL-like one-past position.
            UINT32 newLayoutTextOffset,
            IDWriteTextLayout* newLayout,
            bool isOffsetNegative = false
        );

        Status insertTextAt(
            IDWriteTextLayout*& currentLayout,
            UnicodeString& text,
            UINT32 position,
            const UnicodeString& textToInsert,
            Font* font = nullptr
        );

        Status removeTextAt(IDWriteTextLayout*& currentLayout, UnicodeString& text, UINT32 position, UINT32 lengthToRemove);

        inline Status clear(IDWriteTextLayout*& currentLayout, UnicodeString& text) {
            text.clear();
            return recreateLayout(currentLayout, text);
        }

        void copyGlobalProperties(IDWriteTextLayout* oldLayout, IDWriteTextLayout* newLayout);
    };
}