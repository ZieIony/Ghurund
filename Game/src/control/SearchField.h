#pragma once

#include "ui/layout/StackLayout.h"
#include "ui/widget/TextField.h"

namespace Ghurund::Editor {
    using namespace Ghurund::UI;

    class SearchField:public StackLayout {
    private:
        TextBlockPtr hint;
        TextFieldPtr textField;

    public:
        SearchField(Theme& theme) {
            PreferredSize.height = PreferredSize::Height::WRAP;
            hint = ghnew TextBlock("Search", theme.getSecondaryTextFont());
            hint->PreferredSize.width = PreferredSize::Width::FILL;
            textField = ghnew TextField(theme);
            textField->PreferredSize.width = PreferredSize::Width::FILL;
            Children = { hint, textField };

            OnStateChanged.add([this](Control& control) {
                hint->Visible = Focused;
                return true;
            });
        }
    };
}