#pragma once

#include "ui/control/ControlContainer.h"
#include "ui/control/TextBlock.h"
#include "ui/layout/FlowLayout.h"
#include "ui/drawable/CursorDrawable.h"

namespace Ghurund::UI {
    class TextView:public ControlGroup {
    private:
        unsigned int textColor = 0xde000000;
        Font* font = nullptr;
        FlowLayoutManager layoutManager;

        Paint paint;
        bool pressed = false;
        TextSelection selectionStart, selectionEnd, cursorPos;
        unsigned int selectionColor = 0x7f0078D7;

        CursorDrawable* cursorDrawable = nullptr;

        void updateSelection(TextSelection& selection, float x, float y);

    public:
        TextView() {
            preferredSize.height = PreferredSize::Height::WRAP;
            CursorDrawable = ghnew Ghurund::UI::CursorDrawable(0xff333333, 2, 2);
        }

        ~TextView() {
            if (cursorDrawable)
                cursorDrawable->release();
        }

        String getText() const;

        void setText(const String& text);

        __declspec(property(get = getText, put = setText)) String& Text;

        inline unsigned int getTextColor() const {
            return textColor;
        }

        void setTextColor(unsigned int color);

        __declspec(property(get = getTextColor, put = setTextColor)) unsigned int TextColor;

        inline Font* getFont() {
            return font;
        }

        void setFont(Font* font);

        __declspec(property(get = getFont, put = setFont)) Font* Font;

        inline CursorDrawable* getCursorDrawable() {
            return cursorDrawable;
        }

        inline void setCursorDrawable(CursorDrawable* cursorDrawable) {
            if (this->cursorDrawable)
                this->cursorDrawable->Owner = nullptr;
            setPointer(this->cursorDrawable, cursorDrawable);
            if (this->cursorDrawable)
                this->cursorDrawable->Owner = this;
        }

        __declspec(property(get = getCursorDrawable, put = setCursorDrawable)) CursorDrawable* CursorDrawable;

        virtual void onMeasure(float parentWidth, float parentHeight) override {
            measuredSize = layoutManager.measure(*this, parentWidth, parentHeight);
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            layoutManager.layout(*this, x, y, width, height);
        }

        virtual void update(const Timer& timer) override {
            if (cursorDrawable)
                cursorDrawable->update(timer);
        }

        virtual void onDraw(Canvas& canvas) override;

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;
    };

    typedef ScopedPointer<TextView> TextViewPtr;
}
