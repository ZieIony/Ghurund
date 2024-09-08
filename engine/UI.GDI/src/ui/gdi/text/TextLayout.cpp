#include "ghuigdipch.h"
#include "TextLayout.h"

namespace Ghurund::UI::GDI {
    void TextLayout::refresh() {
    }

    HitTestMetrics TextLayout::hitTestTextPosition(uint32_t textPosition, bool isTrailingHit, float* pointX, float* pointY) {
        return {};
    }

    Ghurund::Core::Array<HitTestMetrics> TextLayout::hitTestTextRange(uint32_t textPosition, uint32_t textLength, float originX, float originY) {
        return {};
    }

    HitTestMetrics TextLayout::hitTestPoint(float pointX, float pointY, bool* isTrailingHit) {
        return {};
    }

    Ghurund::Core::Array<Ghurund::UI::LineMetrics> TextLayout::getLineMetrics() {
        return {};
    }

    Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> TextLayout::getClusterMetrics() {
        return {};
    }

    void TextLayout::insertTextAt(uint32_t position, const Ghurund::Core::WString& textToInsert) {
    }

    void TextLayout::removeTextAt(uint32_t position, uint32_t lengthToRemove) {
    }

    Ghurund::UI::Color TextLayout::getColor(uint32_t pos) {
        return Color;
    }

    Ghurund::UI::TextFormat* TextLayout::getFormat(uint32_t position) {
        return nullptr;
    }

    TextMetrics TextLayout::getMetrics() {
        return {};
    }
}
