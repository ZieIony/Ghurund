#pragma once

#include "ui/widget/ContentWidget.h"
#include "ui/widget/button/Button.h"
#include "ui/widget/text/TextField.h"

namespace Ghurund::Editor {
    using namespace Ghurund::UI;

    class SearchFieldLayout:public WidgetLayout {
    private:
        TextBlock* hint;
        TextField* queryField;
        Button* clearButton;
        EventHandler<Control> stateHandler = [this](Control& control) {
            hint->Visible = queryField->Focused;
            return true;
        };

    public:
        SearchFieldLayout(Control* layout) {
            Root = layout;
            hint = (TextBlock*)layout->find("hint");
            queryField = (TextField*)layout->find("query");
            clearButton = (Button*)layout->find("clear");
            queryField->StateChanged.add(stateHandler);
        }

        ~SearchFieldLayout() {
            queryField->StateChanged.remove(stateHandler);
        }

        inline TextBlock* getHint() {
            return hint;
        }

        __declspec(property(get = getHint)) TextBlock* Hint;

        inline TextField* getQueryField() {
            return queryField;
        }

        __declspec(property(get = getQueryField)) TextField* QueryField;

        inline Button* getClearButton() {
            return clearButton;
        }

        __declspec(property(get = getClearButton)) Button* ClearButton;
    };
}