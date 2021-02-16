#pragma once

#include "DrawingEffect.h"
#include "SetSelectionMode.h"
#include "ui/style/Theme.h"
#include "ui/control/TextBlock.h"
#include "ui/drawable/CursorDrawable.h"
#include "input/Input.h"

namespace Ghurund::UI {
    class TextView:public TextBlock {
    private:
        DrawingEffect* textSelectionEffect = nullptr;
        DrawingEffect* imageSelectionEffect = nullptr;
        DrawingEffect* caretBackgroundEffect = nullptr;

        CursorDrawable* cursorDrawable = nullptr;

    protected:
        uint32_t caretAnchor = 0;
        uint32_t caretPosition = 0;
        uint32_t caretPositionOffset = 0;
        bool pressed = false;

        Ghurund::UI::TextFormat* currentFont = nullptr;
        uint32_t currentColor = 0;

        ~TextView();

        DWRITE_TEXT_RANGE getSelectionRange();

        D2D1_RECT_F getCaretRect();

        void getLineMetrics(std::vector<DWRITE_LINE_METRICS>& lineMetrics);

        void getLineFromPosition(const DWRITE_LINE_METRICS* lineMetrics, UINT32 lineCount, UINT32 textPosition, UINT32* lineOut, UINT32* linePositionOut);

        void alignCaretToNearestCluster(bool isTrailingHit, bool skipZeroWidth);

        void updateCaretFormatting();

        void updateSystemCaret(const D2D1_RECT_F& rect);

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

        bool setSelection(SetSelectionMode moveMode, UINT32 advance, bool extendSelection, bool updateCaretFormat = true);

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