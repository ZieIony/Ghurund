#pragma once

#include "ui/layout/StackLayout.h"
#include "ui/widget/textfield/TextField.h"

namespace Ghurund::Editor {
    using namespace Ghurund::UI;

    class SearchField:public StackLayout {
    private:
        SharedPointer<TextBlock> hint;
        TextFieldPtr textField;

    public:
        SearchField(ResourceContext& context, Ghurund::UI::Theme& theme) {
            PreferredSize.height = PreferredSize::Height::WRAP;
            hint = ghnew TextBlock("Search", theme.TextStyles[Theme::TEXTSTYLE_TEXT_SECONDARY]);
            hint->PreferredSize.width = PreferredSize::Width::FILL;
            textField = ghnew TextField();
            textField->PreferredSize.width = PreferredSize::Width::FILL;
            Children = { hint, textField };

            OnStateChanged.add([this](Control& control) {
                hint->Visible = Focused;
                return true;
            });
        }
    };
}