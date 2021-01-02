#pragma once

#include "Button.h"
#include "TextButtonLayout.h"

namespace Ghurund::UI {
    class TextButton:public Button, public TextMixin {
    private:
        static const Ghurund::Type& GET_TYPE() {
            static auto PROPERTY_TEXT = TypedProperty<TextButton, WString>(GH_STRINGIFY(String), GH_STRINGIFY(Text), [](TextButton& button, WString& value) {
                value = button.Text;
            }, [](TextButton& button, const WString& value) {
                button.Text = value;
            });

            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(TextButton))
                .withProperty(PROPERTY_TEXT)
                .withSupertype(__super::TYPE);
            return TYPE;
        }

    public:
        TextButton(TextButtonLayout* layout = ghnew TextButtonLayout()):Button(layout) {
            textView = layout->TextBlock;
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef SharedPointer<TextButton> TextButtonPtr;
}