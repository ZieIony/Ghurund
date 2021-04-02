#pragma once

#include "SearchFieldBinding.h"

#include "ui/widget/button/Button.h"
#include "ui/widget/text/TextField.h"

namespace Ghurund::Editor {
    using namespace Ghurund::UI;

    class SearchFieldLayout:public SearchFieldBinding {
    private:
        EventHandler<Control> stateHandler = [this](Control& control) {
            Hint->Visible = QueryField->Focused;
            return true;
        };

    public:
        SearchFieldLayout(Control* layout):SearchFieldBinding(layout) {
            QueryField->StateChanged.add(stateHandler);
        }

        ~SearchFieldLayout() {
            QueryField->StateChanged.remove(stateHandler);
        }
    };
}