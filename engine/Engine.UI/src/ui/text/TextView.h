#pragma once

#include "SetSelectionMode.h"
#include "Selection.h"
#include "core/input/Input.h"
#include "ui/drawable/CursorDrawable.h"
#include "ui/text/TextBlock.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

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

        virtual void onDraw(ICanvas& canvas) override;

        virtual void onThemeChanged() override;

        static const Ghurund::Core::Type& GET_TYPE();

        ~TextView() {
            if (cursorDrawable)
                cursorDrawable->release();
        }

    public:
        TextView(std::unique_ptr<TextLayout> textLayout);

        inline void setCursorDrawable(CursorDrawable* drawable) {
            setPointer(cursorDrawable, drawable);
        }

        __declspec(property(put = setCursorDrawable)) CursorDrawable* CursorDrawable;

        bool setSelection(SetSelectionMode moveMode, uint32_t advance, bool extendSelection, bool updateCaretFormat = true);

        void copyToClipboard();

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override;

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;

        

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}