#include "TextField.h"
#include "application/Clipboard.h"
#include "input/Input.h"

namespace Ghurund::UI {
    void TextField::onReturn() {
        UINT32 absolutePosition = caretPosition + caretPositionOffset;
        deleteSelection();
        WString textToInsert(L"\r\n");
        layoutEditor.insertTextAt(textLayout, text, absolutePosition, textToInsert, TextFormat);
        setSelection(SetSelectionMode::AbsoluteLeading, absolutePosition + textToInsert.Size, false, false);
        repaint();
    }

    void TextField::onBackspace() {
        // Erase back one character (less than a character though).
        // Since layout's hit-testing always returns a whole cluster,
        // we do the surrogate pair detection here directly. Otherwise
        // there would be no way to delete just the diacritic following
        // a base character.

        UINT32 absolutePosition = caretPosition + caretPositionOffset;

        if (absolutePosition != caretAnchor) {
            deleteSelection();
        } else if (absolutePosition > 0) {
            UINT32 count = 1;
            // Need special case for surrogate pairs and CR/LF pair.
            if (absolutePosition >= 2 && absolutePosition <= text.Size) {
                wchar_t charBackOne = text[absolutePosition - 1];
                wchar_t charBackTwo = text[absolutePosition - 2];
                if ((isLowSurrogate(charBackOne) && isHighSurrogate(charBackTwo)) || (charBackOne == '\n' && charBackTwo == '\r'))
                    count = 2;
            }
            setSelection(SetSelectionMode::LeftChar, count, false);
            layoutEditor.removeTextAt(textLayout, text, caretPosition, count);
            repaint();
        }
    }

    void TextField::onDelete() {
        UINT32 absolutePosition = caretPosition + caretPositionOffset;

        if (absolutePosition != caretAnchor) {
            deleteSelection();
        } else {
            DWRITE_HIT_TEST_METRICS hitTestMetrics;
            float caretX, caretY;

            // Get the size of the following cluster.
            textLayout->HitTestTextPosition(absolutePosition, false, &caretX, &caretY, &hitTestMetrics);

            layoutEditor.removeTextAt(textLayout, text, hitTestMetrics.textPosition, hitTestMetrics.length);

            setSelection(SetSelectionMode::AbsoluteLeading, hitTestMetrics.textPosition, false);
            repaint();
        }
    }

    void TextField::onKeyPress(UINT32 keyCode) {
        UINT32 absolutePosition = caretPosition + caretPositionOffset;

        Ghurund::Input::Input& input = Context->Window.Input;
        if (keyCode == VK_RETURN) {
            onReturn();
        } else if (keyCode == VK_BACK) {
            onBackspace();
        } else if (keyCode == VK_DELETE) {
            onDelete();
        } else if (keyCode == VK_LEFT) {
            setSelection(input.isControlDown() ? SetSelectionMode::LeftWord : SetSelectionMode::Left, 1, input.isShiftDown());
        } else if (keyCode == VK_RIGHT) {
            setSelection(input.isControlDown() ? SetSelectionMode::RightWord : SetSelectionMode::Right, 1, input.isShiftDown());
        } else if (keyCode == VK_UP) {
            setSelection(SetSelectionMode::Up, 1, input.isShiftDown());
        } else if (keyCode == VK_DOWN) {
            setSelection(SetSelectionMode::Down, 1, input.isShiftDown());
        } else if (keyCode == VK_HOME) {
            setSelection(input.isControlDown() ? SetSelectionMode::First : SetSelectionMode::Home, 0, input.isShiftDown());
        } else if (keyCode == VK_END) {
            setSelection(input.isControlDown() ? SetSelectionMode::Last : SetSelectionMode::End, 0, input.isShiftDown());
        } else if (keyCode == VK_INSERT) {
            if (input.isControlDown()) {
                copyToClipboard();
            } else if (input.isShiftDown()) {
                pasteFromClipboard();
            }
        } else if (keyCode == 'V' && input.isControlDown()) {
            pasteFromClipboard();
        } else if (keyCode == 'X' && input.isControlDown()) {
            copyToClipboard();
            deleteSelection();
        } else if (keyCode == 'A' && input.isControlDown()) {
            setSelection(SetSelectionMode::All, 0, true);
        }
    }

    void TextField::onKeyCharacter(UINT32 charCode) {
        if (charCode >= 0x20 || charCode == 9) {
            deleteSelection();

            // Convert the UTF32 character code from the Window message to UTF16,
            // yielding 1-2 code-units. Then advance the caret position by how
            // many code-units were inserted.

            WString textToInsert;
            textToInsert.add((wchar_t)charCode);

            // If above the basic multi-lingual plane, split into
            // leading and trailing surrogates.
            if (charCode > 0xFFFF) {
                // http://unicode.org/faq/utf_bom.html#35
                textToInsert.set(0, wchar_t(0xD800 + (charCode >> 10) - (0x10000 >> 10)));
                textToInsert.add(wchar_t(0xDC00 + (charCode & 0x3FF)));
            }
            layoutEditor.insertTextAt(textLayout, text, caretPosition + caretPositionOffset, textToInsert, TextFormat);
            setSelection(SetSelectionMode::Right, textToInsert.Size, false, false);

            repaint();
        }
    }

    void TextField::deleteSelection() {
        DWRITE_TEXT_RANGE selectionRange = getSelectionRange();
        if (selectionRange.length <= 0)
            return;

        layoutEditor.removeTextAt(textLayout, text, selectionRange.startPosition, selectionRange.length);

        setSelection(SetSelectionMode::AbsoluteLeading, selectionRange.startPosition, false);
        repaint();
    }

    void TextField::pasteFromClipboard() {
        if (!Context)
            return;

        deleteSelection();

        WString* data = Clipboard::getUnicodeText(Context->Window.Handle);
        if (data) {
            layoutEditor.insertTextAt(textLayout, text, caretPosition + caretPositionOffset, *data);
            setSelection(SetSelectionMode::RightChar, data->Length, true);
            repaint();
        }
    }

    const Ghurund::Type& TextField::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<TextField>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(TextField))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool TextField::dispatchKeyEvent(const KeyEventArgs& event) {
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
}
