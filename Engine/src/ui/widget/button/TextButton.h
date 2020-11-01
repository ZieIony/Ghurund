#pragma once

#include "Button.h"
#include "TextButtonLayout.h"

namespace Ghurund::UI {
    class TextButton:public Button, public TextMixin {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(TextButton);

    public:
        TextButton(TextButtonLayout* layout):Button(layout) {
            textView = layout->TextBlock;
        }

        TextButton(Theme& theme):TextButton(ghnew TextButtonLayout(theme)) {}

        virtual void measure(float parentWidth, float parentHeight) {
            textView->PreferredSize = preferredSize;
            __super::measure(parentWidth, parentHeight);
        }

        static const Ghurund::Type& TYPE() {
            static auto& PROPERTY_TEXT = TypedProperty<TextButton, String>(GH_STRINGIFY(String), GH_STRINGIFY(Text), [](TextButton& button, String& value) {
                value = button.Text;
            }, [](TextButton& button, const String& value) {
                button.Text = value;
            });
   
            static const Ghurund::Type TYPE = TypeBuilder<TextButton>(NAMESPACE_NAME, CLASS_NAME)
                .withProperty(PROPERTY_TEXT)
                .withSupertype(__super::TYPE);
            return TYPE;
        }

        virtual const Ghurund::Type& getType() const override {
            return TYPE();
        }
    };

    typedef ScopedPointer<TextButton> TextButtonPtr;
}