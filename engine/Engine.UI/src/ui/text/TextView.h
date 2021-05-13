#pragma once

#include "SetSelectionMode.h"
#include "Selection.h"
#include "core/input/Input.h"
#include "ui/drawable/CursorDrawable.h"
#include "ui/text/TextBlock.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    class TextView:public TextBlock {
    private:
        Color textSelectionEffect = 0;
        Color imageSelectionEffect = 0;
        Color caretBackgroundEffect = 0;

        CursorDrawable* cursorDrawable = nullptr;

    protected:
        uint32_t caretAnchor = 0;
        uint32_t caretPosition = 0;
        uint32_t caretPositionOffset = 0;
        bool pressed = false;

        Selection getSelectionRange();

        FloatRect getCaretRect();

        void getLineFromPosition(const LineMetrics* lineMetrics, UINT32 lineCount, UINT32 textPosition, UINT32* lineOut, UINT32* linePositionOut);

        void alignCaretToNearestCluster(bool isTrailingHit, bool skipZeroWidth);

        void updateSystemCaret(const FloatRect& rect);

        bool setSelectionFromPoint(float x, float y, bool extendSelection);

        virtual void onUpdate(const uint64_t time) override {
            if (cursorDrawable)
                cursorDrawable->update(time);
        }

        virtual void onDraw(Canvas& canvas) override;

        virtual void onThemeChanged() override;

        static const Ghurund::Type& GET_TYPE();

    public:
        TextView();

        ~TextView() {
            if (cursorDrawable)
                cursorDrawable->release();
        }

        inline CursorDrawable* getCursorDrawable() {
            return cursorDrawable;
        }

        inline void setCursorDrawable(CursorDrawable* drawable) {
            if (cursorDrawable)
                cursorDrawable->Owner = nullptr;
            setPointer(cursorDrawable, drawable);
            if (drawable)
                drawable->Owner = this;
        }

        __declspec(property(get = getCursorDrawable, put = setCursorDrawable)) CursorDrawable* CursorDrawable;

        bool setSelection(SetSelectionMode moveMode, uint32_t advance, bool extendSelection, bool updateCaretFormat = true);

        void copyToClipboard();

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override;

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}