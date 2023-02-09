#pragma once

#include "ui/text/TextLayout.h"
#include "ui/text/TextMetrics.h"
#include "ui/text/TextFormat.h"
#include "core/math/Size.h"
#include "ui/Canvas.h"
#include "ui/Color.h"

namespace UnitTest {
    using namespace Microsoft::WRL;
    using namespace Ghurund::UI;

    class TextLayout:public Ghurund::UI::TextLayout {
    public:
        TextLayout(const Ghurund::Core::WString& text, const Ghurund::UI::Color& color, UnitTest::TextFormat* format)
            :Ghurund::UI::TextLayout(text, color, format) {}

        Ghurund::UI::Color getColor(uint32_t pos);

        Ghurund::UI::TextFormat* getFormat(uint32_t position);

        Ghurund::UI::TextMetrics getMetrics();

        __declspec(property(get = getMetrics)) Ghurund::UI::TextMetrics TextMetrics;

        Ghurund::Core::Array<Ghurund::UI::LineMetrics> getLineMetrics();

        __declspec(property(get = getLineMetrics)) Ghurund::Core::Array<Ghurund::UI::LineMetrics> LineMetrics;

        Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> getClusterMetrics();;

        __declspec(property(get = getClusterMetrics)) Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> ClusterMetrics;

        Status insertTextAt(uint32_t position, const Ghurund::Core::WString& textToInsert);

        Status removeTextAt(uint32_t position, uint32_t lengthToRemove);

        HitTestMetrics hitTestPoint(float pointX, float pointY, bool* isTrailingHit) {
            return {};
        }

        HitTestMetrics hitTestTextPosition(uint32_t textPosition, bool isTrailingHit, float* pointX, float* pointY) {
            return {};
        }

        Ghurund::Core::Array<HitTestMetrics> hitTestTextRange(uint32_t textPosition, uint32_t textLength, float originX, float originY) {
            return {};
        }

        Status refresh() {
            size = { text.Length * 10.0f, format->Size };
            return Status::OK;
        }

        void draw(ICanvas& canvas) {}
    };
}