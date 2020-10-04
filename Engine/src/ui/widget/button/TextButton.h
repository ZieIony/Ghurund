#pragma once

#include "Button.h"
#include "TextButtonLayout.h"

namespace Ghurund::UI {
    class TextButton:public Button, public TextMixin {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(TextButton);

    public:
        TextButton(TextButtonLayout* layout):Button(layout) {
            textView = layout->TextView;
        }

        TextButton(Theme& theme):TextButton(ghnew TextButtonLayout(theme)) {}

        virtual void measure(float parentWidth, float parentHeight) {
            textView->PreferredSize = preferredSize;
            __super::measure(parentWidth, parentHeight);
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<TextButton>(NAMESPACE_NAME, CLASS_NAME)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<TextButton> TextButtonPtr;
}