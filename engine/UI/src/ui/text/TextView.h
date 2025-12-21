#pragma once

#include "Selection.h"
#include "SetSelectionMode.h"

#include "core/input/Input.h"
#include "core/math/Rect.h"
#include "ui/drawable/CursorDrawable.h"
#include "ui/text/TextBlock.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class TextView:public Control {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = TextView::GET_TYPE();
#pragma endregion

    private:
        Color textSelectionEffect = 0;
        Color imageSelectionEffect = 0;
        Color caretBackgroundEffect = 0;

        //CursorDrawable* cursorDrawable = nullptr;

    protected:
        TextLayout textLayout;

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
            //if (cursorDrawable)
          //      cursorDrawable->update(time);
        }

        virtual void onDraw(RenderGroup& group, const XMFLOAT2& parentPosition) override;

        virtual void onThemeChanged() override;

        ~TextView() {
         //   if (cursorDrawable)
         //       cursorDrawable->release();
        }

    public:
        TextView();

       /* inline void setCursorDrawable(CursorDrawable* drawable) {
            setPointer(cursorDrawable, drawable);
        }

        __declspec(property(put = setCursorDrawable)) CursorDrawable* CursorDrawable;*/

        TextDocument* getDocument() {
            return textLayout.Document;
        }

        inline void setDocument(TextDocument* textDocument) {
            textLayout.Document = textDocument;
        }

        __declspec(property(get = getDocument, put = setDocument)) TextDocument* Document;

        bool setSelection(SetSelectionMode moveMode, uint32_t advance, bool extendSelection, bool updateCaretFormat = true);

        void copyToClipboard();

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override;

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;
    };
}