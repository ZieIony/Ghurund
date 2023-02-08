#pragma once

#include "ui/text/ITextLayout.h"
#include "ui/text/TextMetrics.h"
#include "ui/text/TextFormat.h"
#include "core/math/Size.h"
#include "ui/Canvas.h"
#include "core/IUnknownImpl.h"

#include <wrl.h>
#include <ui/Color.h>
#include <gdiplus.h>

namespace Ghurund::UI::GDI {
    using namespace Microsoft::WRL;

    class TextLayout:public ITextLayout {
    private:
        Ghurund::Core::FloatSize size;
        Ghurund::UI::Color color;
        Ghurund::Core::WString text;
        Ghurund::UI::TextFormat* format = nullptr;

        bool valid = false;

    public:
        TextLayout(const Ghurund::Core::WString& text, const Ghurund::UI::Color& color, Ghurund::UI::TextFormat* format)
            :text(text), color(color) {
            Format = format;
        }

        ~TextLayout() {
            if (format)
                format->release();
        }

        inline const Ghurund::Core::FloatSize& getSize() const {
            return size;
        }

        inline void setSize(const Ghurund::Core::FloatSize& size) {
            setSize(size.Width, size.Height);
        }

        virtual void setSize(float w, float h) {
            if (size.Width != w || size.Height != h) {
                size = { w, h };
                valid = false;
            }
        }

        __declspec(property(get = getSize, put = setSize)) const Ghurund::Core::FloatSize& Size;

        inline void setColor(const Ghurund::UI::Color& color) {
            this->color = color;
        }

        inline const Ghurund::UI::Color& getColor() const {
            return color;
        }

        __declspec(property(get = getColor, put = setColor)) const Ghurund::UI::Color& Color;

        Ghurund::UI::Color getColor(uint32_t pos);

        inline const Ghurund::Core::WString& getText() const {
            return text;
        }

        inline void setText(const Ghurund::Core::WString& text) {
            if (this->text != text) {
                this->text = text;
                valid = false;
            }
        }

        __declspec(property(get = getText, put = setText)) const Ghurund::Core::WString& Text;

        inline Ghurund::UI::TextFormat* getFormat() {
            return format;
        }

        inline void setFormat(Ghurund::UI::TextFormat* textFormat) {
            setPointer(this->format, (Ghurund::UI::TextFormat*)textFormat);
        }

        __declspec(property(get = getFormat, put = setFormat)) Ghurund::UI::TextFormat* Format;

        Ghurund::UI::TextFormat* getFormat(uint32_t position);

        Ghurund::UI::TextMetrics getMetrics();

        __declspec(property(get = getMetrics)) Ghurund::UI::TextMetrics TextMetrics;

        Ghurund::Core::Array<Ghurund::UI::LineMetrics> getLineMetrics();

        __declspec(property(get = getLineMetrics)) Ghurund::Core::Array<Ghurund::UI::LineMetrics> LineMetrics;

        Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> getClusterMetrics();;

        __declspec(property(get = getClusterMetrics)) Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> ClusterMetrics;

        HitTestMetrics hitTestTextPosition(uint32_t textPosition, bool isTrailingHit, float* pointX, float* pointY);

        Ghurund::Core::Array<HitTestMetrics> hitTestTextRange(uint32_t textPosition, uint32_t textLength, float originX, float originY);

        HitTestMetrics hitTestPoint(float pointX, float pointY, bool* isTrailingHit);

        inline void invalidate() {
            valid = false;
        }

        Status refresh();

        Status insertTextAt(uint32_t position, const Ghurund::Core::WString& textToInsert);

        Status removeTextAt(uint32_t position, uint32_t lengthToRemove);
    };
}