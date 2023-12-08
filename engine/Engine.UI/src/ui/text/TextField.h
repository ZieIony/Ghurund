#pragma once

#include "TextView.h"

#include "core/window/Window.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI {
    class TextField:public TextView {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = TextField::GET_TYPE();
#pragma endregion

    private:
        Event<TextField> onTextChanged = Event<TextField>(*this);

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

    protected:
        ~TextField() {}

    public:
        TextField(std::unique_ptr<TextLayout> textLayout):TextView(std::move(textLayout)) {
            Focusable = true;
        }

        inline Event<TextField>& getOnTextChanged() {
            return onTextChanged;
        }

        __declspec(property(get = getOnTextChanged)) Event<TextField>& OnTextChanged;

        void deleteSelection();

        void pasteFromClipboard();

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override;
    };
}