#include "TextView.h"

namespace Ghurund::UI {
    void TextView::onDraw(Canvas& canvas) {
        bool selection = false;
        bool focused = Focused;

        TextSelection& selStart = selectionStart.index < selectionEnd.index ? selectionStart : selectionEnd;
        TextSelection& selEnd = selectionStart.index >= selectionEnd.index ? selectionStart : selectionEnd;

        if (focused && selectionStart.index != selectionEnd.index) {
            paint.Color = selectionColor;
            if (selectionStart.control == selectionEnd.control) {
                canvas.save();
                canvas.transform(selectionStart.control->Transformation);
                canvas.fillRect(selStart.x, 0, selEnd.x - selStart.x, selectionStart.control->Size.height, paint);
                canvas.restore();
            } else {
                canvas.save();
                canvas.transform(selStart.control->Transformation);
                canvas.fillRect(selStart.x, 0, selStart.control->Size.width - selStart.x, selStart.control->Size.height, paint);
                canvas.restore();

                canvas.save();
                canvas.transform(selEnd.control->Transformation);
                canvas.fillRect(0, 0, selEnd.x, selEnd.control->Size.height, paint);
                canvas.restore();
            }
        }

        for (Control* c : Children) {
            if (c == selEnd.control)
                selection = false;
            if (focused && selection) {
                paint.Color = selectionColor;
                canvas.save();
                canvas.transform(c->Transformation);
                canvas.fillRect(0, 0, c->Size.width, c->Size.height, paint);
                canvas.restore();
            }
            c->draw(canvas);
            if (c == selStart.control && selStart.control != selEnd.control)
                selection = true;
        }

        if (focused && cursorPos.control && cursorDrawable) {
            canvas.save();
            canvas.transform(cursorPos.control->Transformation);
            cursorDrawable->Size.width = cursorDrawable->PreferredSize.width;
            cursorDrawable->Size.height = cursorPos.control->Size.height;
            cursorDrawable->Position = { cursorPos.x - cursorDrawable->Size.width / 2, 0 };
            cursorDrawable->draw(canvas);
            canvas.restore();
        }
    }

    void TextView::updateSelection(TextSelection& selection, float x, float y) {
        selection.index = 0;
        for (Control* c : Children) {
            if (c->Type.isOrExtends(TextBlock::TYPE)) {
                auto tv = ((TextBlock*)c);
                if (c->hitTest(x, y)) {
                    if (tv->Font) {
                        TextSelection s = font->findSelection(tv->Text, x - c->Position.x);
                        selection.index += s.index;
                        selection.x = s.x;
                        selection.control = c;
                        repaint();
                        return;
                    }
                } else {
                    selection.index += tv->Text.Length;
                }
            }
        }
    }

    String TextView::getText() const {
        String text;
        for (Control* c : Children) {
            if (c->Type.extends(TextBlock::TYPE))
                text.add(((TextBlock*)c)->Text);
        }
        return text;
    }

    void TextView::setText(const String& text) {
        Children.clear();
        size_t prevSpace = 0;
        for (size_t i = 0; i < text.Length; i++) {
            if (isspace(text[i])) {
                TextBlock* t = ghnew TextBlock(text.subString(prevSpace, i - prevSpace + 1), font);
                t->TextColor = textColor;
                Children.add(t);
                t->release();
                prevSpace = i + 1;
            }
        }
        selectionStart.control = nullptr;
        selectionEnd.control = nullptr;
        cursorPos.control = nullptr;
    }

    void TextView::setTextColor(unsigned int color) {
        textColor = color;
        for (Control* c : Children) {
            if (c->Type.extends(TextBlock::TYPE))
                ((TextBlock*)c)->TextColor = color;
        }
    }

    void TextView::setFont(Ghurund::UI::Font* font) {
        setPointer(this->font, font);
        for (Control* c : Children) {
            if (c->Type.extends(TextBlock::TYPE))
                ((TextBlock*)c)->Font = font;
        }
    }

    bool TextView::dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
        if (event.Action == MouseAction::DOWN && Focusable) {
            pressed = true;
            updateSelection(selectionStart, event.Position.x, event.Position.y);
            cursorPos = selectionEnd = selectionStart;
            requestFocus();
            return true;
        } else if (pressed) {
            pressed = false;
            updateSelection(selectionEnd, event.Position.x, event.Position.y);
            cursorPos = selectionEnd;
            return true;
        }
        return __super::dispatchMouseButtonEvent(event);
    }

    bool TextView::dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
        if (pressed) {
            updateSelection(selectionEnd, event.Position.x, event.Position.y);
            cursorPos = selectionEnd;
            return true;
        }
        return __super::dispatchMouseMotionEvent(event);
    }
}
