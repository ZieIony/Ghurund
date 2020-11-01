#pragma once

#include "ui/Theme.h"
#include "ui/control/TextBlock.h"
#include "ui/widget/SplitLayout.h"
#include "ui/widget/VerticalScrollBar.h"
#include "ui/widget/property/PropertyList.h"

using namespace Ghurund;
using namespace Ghurund::UI;

class PropertyWindow:public VerticalLayout {
private:
    TextBlockPtr objectTypeText;
    PropertyListPtr propertyList;

public:
    PropertyWindow(Theme& theme) {
        objectTypeText = ghnew TextBlock("", theme.getSecondaryTextFont());
        propertyList = ghnew PropertyList(theme);
        propertyList->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
        Children = { objectTypeText, propertyList };
    }

    inline void setItem(Object* item) {
        propertyList->Item = item;
        objectTypeText->Text = item->Type.Name;
    }

    __declspec(property(put = setItem)) Object* Item;
};

class LayoutEditorTab:public SplitLayout {
    ScopedPointer<PropertyWindow> propertyWindow;
    ScopedPointer<TextButton> editedControl;
    StackLayoutPtr layoutContent;

public:
    LayoutEditorTab(Theme& theme) {
        Name = "editor tab";
        HorizontalLayoutPtr horizontalLayout = ghnew HorizontalLayout();
        propertyWindow = ghnew PropertyWindow(theme);
        SeparatorPtr separator = ghnew Separator(ghnew VerticalSeparatorStyle(theme));
        separator->Padding.All = 0;
        horizontalLayout->Children = { separator, propertyWindow };
        editedControl = ghnew TextButton(theme);
        layoutContent = ghnew StackLayout();
        layoutContent->Alignment = { Alignment::Horizontal::CENTER, Alignment::Vertical::CENTER };
        layoutContent->Children = { editedControl };
        propertyWindow->Item = editedControl;

        Orientation = Orientation::HORIZONTAL;
        Child1 = layoutContent;
        Child2 = horizontalLayout;
    }
};