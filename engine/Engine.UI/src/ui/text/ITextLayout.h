#pragma once

#include "core/math/Size.h"
#include "core/string/String.h"
#include "ui/Color.h"
#include "TextMetrics.h"
#include "TextFormat.h"

namespace Ghurund::UI {
    __interface ITextLayout {
        const Ghurund::Core::WString& getText() const;

        void setText(const Ghurund::Core::WString& text);

        __declspec(property(get = getText, put = setText)) const Ghurund::Core::WString& Text;

        TextFormat* getFormat();

        void setFormat(TextFormat* textFormat);

        __declspec(property(get = getFormat, put = setFormat)) TextFormat* Format;

        inline void setColor(const Color& color);

        inline const Color& getColor() const;

        __declspec(property(get = getColor, put = setColor)) const Color& Color;

        const Ghurund::Core::FloatSize& getSize() const;

        void setSize(const Ghurund::Core::FloatSize& size);

        void setSize(float w, float h);

        __declspec(property(get = getSize, put = setSize)) const Ghurund::Core::FloatSize& Size;

        TextMetrics getMetrics();

        __declspec(property(get = getMetrics)) TextMetrics TextMetrics;

        Ghurund::Core::Array<Ghurund::UI::LineMetrics> getLineMetrics();

        __declspec(property(get = getLineMetrics)) Ghurund::Core::Array<Ghurund::UI::LineMetrics> LineMetrics;

        Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> getClusterMetrics();;

        __declspec(property(get = getClusterMetrics)) Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> ClusterMetrics;

        HitTestMetrics hitTestTextPosition(uint32_t textPosition, bool isTrailingHit, float* pointX, float* pointY);

        Ghurund::Core::Array<HitTestMetrics> hitTestTextRange(uint32_t textPosition, uint32_t textLength, float originX, float originY);

        HitTestMetrics hitTestPoint(float pointX, float pointY, bool* isTrailingHit);

        Status refresh();

        Status insertTextAt(uint32_t position, const Ghurund::Core::WString& textToInsert);

        Status removeTextAt(uint32_t position, uint32_t lengthToRemove);
    };
}