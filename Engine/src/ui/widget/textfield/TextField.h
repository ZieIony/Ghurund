#pragma once

#include "TextView.h"
#include "LayoutEditor.h"

#include "application/Window.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    class TextField:public TextView {
    private:
        Event<TextField> onTextChanged = Event<TextField>(*this);
        LayoutEditor layoutEditor;

        void onKeyPress(UINT32 keyCode);

        void onKeyCharacter(UINT32 charCode);

        inline bool isSurrogate(UINT32 ch) {
            // 0xD800 <= ch <= 0xDFFF
            return (ch & 0xF800) == 0xD800;
        }

        inline bool isHighSurrogate(UINT32 ch) {
            // 0xD800 <= ch <= 0xDBFF
            return (ch & 0xFC00) == 0xD800;
        }

        inline bool isLowSurrogate(UINT32 ch) {
            // 0xDC00 <= ch <= 0xDFFF
            return (ch & 0xFC00) == 0xDC00;
        }

    public:
        TextField(IDWriteFactory* factory, Ghurund::UI::Theme& theme):TextView(theme), layoutEditor(factory) {
            Focusable = true;
        }

        inline Event<TextField>& getOnTextChanged() {
            return onTextChanged;
        }

        __declspec(property(get = getOnTextChanged)) Event<TextField>& OnTextChanged;

        void copyToClipboard();

        void deleteSelection();

        void pasteFromClipboard();

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override {
            if (Focused) {
                if (event.Action == KeyAction::DOWN) {
                    onKeyPress(event.Key);
                    return true;
                } else if (event.Action == KeyAction::CHAR) {
                    onKeyCharacter(event.Key);
                    return true;
                }
            }
            return __super::dispatchKeyEvent(event);
        }

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override {
            return __super::dispatchMouseButtonEvent(event);
        }


        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override {
            return __super::dispatchMouseMotionEvent(event);
        }
    };

    typedef SharedPointer<TextField> TextFieldPtr;
}