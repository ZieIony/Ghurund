#include "pch.h"
#include "TextLayout.h"
#include "test/ui/text/TextFormat.h"

namespace UnitTest {
    Ghurund::Core::Array<Ghurund::UI::LineMetrics> TextLayout::getLineMetrics() {
        uint32_t lineCount = 0;
        Ghurund::Core::Array<Ghurund::UI::LineMetrics> lineMetrics(lineCount);
        return lineMetrics;
    }

    Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> TextLayout::getClusterMetrics() {
        UINT32 clusterCount = 0;
        Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> clusterMetrics(clusterCount);
        return clusterMetrics;
    }

    Status TextLayout::insertTextAt(uint32_t position, const Ghurund::Core::WString& textToInsert) {
        return Status::OK;
    }

    Status TextLayout::removeTextAt(uint32_t position, uint32_t lengthToRemove) {
        return Status::OK;
    }

    Ghurund::UI::Color TextLayout::getColor(uint32_t pos) {
        return Color;
    }

    Ghurund::UI::TextFormat* TextLayout::getFormat(uint32_t position) {
        return nullptr;
    }

    TextMetrics TextLayout::getMetrics() {
        return {
            .width = Size.Width,
            .height = Size.Height,
            .layoutWidth = Size.Width,
            .layoutHeight = Size.Height
        };
    }
}
