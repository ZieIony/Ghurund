#pragma once

#include "TextView.h"
#include "LayoutEditor.h"

#include "application/Window.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    class TextField:public TextView {
    private:
        Event<TextField> onTextChanged = Event<TextField>(*this);
        LayoutEditor layoutEditor;

        void onReturn();

        void onBackspace();

        void onDelete();

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
        TextField() {
            Focusable = true;
        }

        inline Event<TextField>& getOnTextChanged() {
            return onTextChanged;
        }

        __declspec(property(get = getOnTextChanged)) Event<TextField>& OnTextChanged;

        void deleteSelection();

        void pasteFromClipboard();

        virtual void dispatchContextChanged() override {
            __super::dispatchContextChanged();
            if (Context)
                layoutEditor.init(Context->Graphics.DWriteFactory);
        }

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override;
    };

    typedef SharedPointer<TextField> TextFieldPtr;
}