#pragma once

#include "CaretFormat.h"

#include "ui/Graphics2D.h"

namespace Ghurund::UI {
    class LayoutEditor {
    private:
        IDWriteFactory* factory;

    public:
        LayoutEditor(IDWriteFactory* factory):factory(factory) {}

        IDWriteFactory* getFactory() {
            return factory;
        }

        __declspec(property(get = getFactory)) IDWriteFactory* Factory;

        HRESULT recreateLayout(IDWriteTextLayout*& currentLayout, const UnicodeString& text);

        void copySinglePropertyRange(
            IDWriteTextLayout* oldLayout,
            UINT32 startPosForOld,
            IDWriteTextLayout* newLayout,
            UINT32 startPosForNew,
            UINT32 length,
            CaretFormat* caretFormat = nullptr
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

        HRESULT insertTextAt(
            IDWriteTextLayout*& currentLayout,
            UnicodeString& text,
            UINT32 position,
            WCHAR const* textToInsert,                  // [lengthToInsert]
            UINT32 textToInsertLength,
            CaretFormat* caretFormat = nullptr
        );

        HRESULT removeTextAt(IDWriteTextLayout*& currentLayout, UnicodeString& text, UINT32 position, UINT32 lengthToRemove);

        inline HRESULT clear(IDWriteTextLayout*& currentLayout, UnicodeString& text) {
            text.clear();
            return recreateLayout(currentLayout, text);
        }

        void copyGlobalProperties(IDWriteTextLayout* oldLayout, IDWriteTextLayout* newLayout);
    };
}