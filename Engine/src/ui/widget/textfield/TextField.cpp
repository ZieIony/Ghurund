#include "TextField.h"

namespace Ghurund::UI {
    void TextField::onKeyPress(UINT32 keyCode) {
        // Handles caret navigation and special presses that
        // do not generate characters.

        bool heldShift = (GetKeyState(VK_SHIFT) & 0x80) != 0;
        bool heldControl = (GetKeyState(VK_CONTROL) & 0x80) != 0;

        UINT32 absolutePosition = caretPosition + caretPositionOffset;

        switch (keyCode) {
        case VK_RETURN:
            // Insert CR/LF pair
            deleteSelection();
            layoutEditor.insertTextAt(textLayout, text, absolutePosition, L"\r\n", 2, &caretFormat);
            setSelection(SetSelectionModeAbsoluteLeading, absolutePosition + 2, false, false);
            repaint();
            break;

        case VK_BACK:
            // Erase back one character (less than a character though).
            // Since layout's hit-testing always returns a whole cluster,
            // we do the surrogate pair detection here directly. Otherwise
            // there would be no way to delete just the diacritic following
            // a base character.

            if (absolutePosition != caretAnchor) {
                deleteSelection();
            } else if (absolutePosition > 0) {
                UINT32 count = 1;
                // Need special case for surrogate pairs and CR/LF pair.
                if (absolutePosition >= 2
                    && absolutePosition <= text.Size) {
                    wchar_t charBackOne = text[absolutePosition - 1];
                    wchar_t charBackTwo = text[absolutePosition - 2];
                    if ((isLowSurrogate(charBackOne) && isHighSurrogate(charBackTwo))
                        || (charBackOne == '\n' && charBackTwo == '\r')) {
                        count = 2;
                    }
                }
                setSelection(SetSelectionModeLeftChar, count, false);
                layoutEditor.removeTextAt(textLayout, text, caretPosition, count);
                repaint();
            }
            break;

        case VK_DELETE:
            // Delete following cluster.

            if (absolutePosition != caretAnchor) {
                // Delete all the selected text.
                deleteSelection();
            } else {
                DWRITE_HIT_TEST_METRICS hitTestMetrics;
                float caretX, caretY;

                // Get the size of the following cluster.
                textLayout->HitTestTextPosition(
                    absolutePosition,
                    false,
                    &caretX,
                    &caretY,
                    &hitTestMetrics
                );

                layoutEditor.removeTextAt(textLayout, text, hitTestMetrics.textPosition, hitTestMetrics.length);

                setSelection(SetSelectionModeAbsoluteLeading, hitTestMetrics.textPosition, false);
                repaint();
            }
            break;

        case VK_TAB:
            break; // want tabs

        case VK_LEFT: // seek left one cluster
            setSelection(heldControl ? SetSelectionModeLeftWord : SetSelectionModeLeft, 1, heldShift);
            break;

        case VK_RIGHT: // seek right one cluster
            setSelection(heldControl ? SetSelectionModeRightWord : SetSelectionModeRight, 1, heldShift);
            break;

        case VK_UP: // up a line
            setSelection(SetSelectionModeUp, 1, heldShift);
            break;

        case VK_DOWN: // down a line
            setSelection(SetSelectionModeDown, 1, heldShift);
            break;

        case VK_HOME: // beginning of line
            setSelection(heldControl ? SetSelectionModeFirst : SetSelectionModeHome, 0, heldShift);
            break;

        case VK_END: // end of line
            setSelection(heldControl ? SetSelectionModeLast : SetSelectionModeEnd, 0, heldShift);
            break;

        case 'C':
            if (heldControl)
                copyToClipboard();
            break;

        case VK_INSERT:
            if (heldControl)
                copyToClipboard();
            else if (heldShift)
                pasteFromClipboard();
            break;

        case 'V':
            if (heldControl)
                pasteFromClipboard();
            break;

        case 'X':
            if (heldControl) {
                copyToClipboard();
                deleteSelection();
            }
            break;

        case 'A':
            if (heldControl)
                setSelection(SetSelectionModeAll, 0, true);
            break;
        }
    }
    void TextField::onKeyCharacter(UINT32 charCode) {
        // Inserts text characters.

        // Allow normal characters and tabs
        if (charCode >= 0x20 || charCode == 9) {
            // Replace any existing selection.
            deleteSelection();

            // Convert the UTF32 character code from the Window message to UTF16,
            // yielding 1-2 code-units. Then advance the caret position by how
            // many code-units were inserted.

            UINT32 charsLength = 1;
            wchar_t chars[2] = { static_cast<wchar_t>(charCode), 0 };

            // If above the basic multi-lingual plane, split into
            // leading and trailing surrogates.
            if (charCode > 0xFFFF) {
                // From http://unicode.org/faq/utf_bom.html#35
                chars[0] = wchar_t(0xD800 + (charCode >> 10) - (0x10000 >> 10));
                chars[1] = wchar_t(0xDC00 + (charCode & 0x3FF));
                charsLength++;
            }
            layoutEditor.insertTextAt(textLayout, text, caretPosition + caretPositionOffset, chars, charsLength, &caretFormat);
            setSelection(SetSelectionModeRight, charsLength, false, false);

            repaint();
        }
    }
    void TextField::copyToClipboard() {
        DWRITE_TEXT_RANGE selectionRange = getSelectionRange();
        if (selectionRange.length <= 0)
            return;

        /*if (OpenClipboard(Window->Handle)) {
        if (EmptyClipboard()) {
        // Allocate room for the text
        size_t byteSize = sizeof(wchar_t) * (selectionRange.length + 1);
        HGLOBAL hClipboardData = GlobalAlloc(GMEM_DDESHARE | GMEM_ZEROINIT, byteSize);

        if (hClipboardData != NULL) {
        void* memory = GlobalLock(hClipboardData);  // [byteSize] in bytes

        if (memory != NULL) {
        // Copy text to memory block.
        const wchar_t* text = Text.getData();
        memcpy(memory, &text[selectionRange.startPosition], byteSize);
        GlobalUnlock(hClipboardData);

        if (SetClipboardData(CF_UNICODETEXT, hClipboardData) != NULL) {
        hClipboardData = NULL; // system now owns the clipboard, so don't touch it.
        }
        }
        GlobalFree(hClipboardData); // free if failed
        }
        }
        CloseClipboard();
        }*/
    }

    void TextField::deleteSelection() {
        DWRITE_TEXT_RANGE selectionRange = getSelectionRange();
        if (selectionRange.length <= 0)
            return;

        layoutEditor.removeTextAt(textLayout, text, selectionRange.startPosition, selectionRange.length);

        setSelection(SetSelectionModeAbsoluteLeading, selectionRange.startPosition, false);
        repaint();
    }

    void TextField::pasteFromClipboard() {
        deleteSelection();

        UINT32 characterCount = 0;

        /*if (OpenClipboard(Window->Handle)) {
        HGLOBAL hClipboardData = GetClipboardData(CF_UNICODETEXT);

        if (hClipboardData != NULL) {
        // Get text and size of text.
        size_t byteSize = GlobalSize(hClipboardData);
        void* memory = GlobalLock(hClipboardData); // [byteSize] in bytes
        const wchar_t* text = reinterpret_cast<const wchar_t*>(memory);
        characterCount = static_cast<UINT32>(wcsnlen(text, byteSize / sizeof(wchar_t)));

        if (memory != NULL) {
        // Insert the text at the current position.
        layoutEditor.insertTextAt(
        textLayout,
        text,
        caretPosition + caretPositionOffset,
        text,
        characterCount
        );
        GlobalUnlock(hClipboardData);
        }
        }
        CloseClipboard();
        }*/

        setSelection(SetSelectionModeRightChar, characterCount, true);
        repaint();
    }
}
