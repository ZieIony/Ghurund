#pragma once

#include "control/ToolWindow.h"
#include "tool/PropertyPanel.h"
#include "tool/WidgetHierarchyPanel.h"

#include "ui/Theme.h"
#include "ui/control/TextBlock.h"
#include "ui/widget/SplitLayout.h"
#include "ui/widget/VerticalScrollBar.h"
#include "ui/widget/property/PropertyList.h"

using namespace Ghurund;
using namespace Ghurund::UI;

namespace Ghurund::Editor {
    class LayoutEditorTab:public ControlContainer {
        SharedPointer<ToolWindow> propertiesWindow;
        SharedPointer<PropertyPanel> propertiesPanel;
        SharedPointer<ToolWindow> widgetHierarchyWindow;
        SharedPointer<WidgetHierarchyPanel> widgetHierarchyPanel;
        SharedPointer<TextButton> editedControl;
        StackLayoutPtr layoutContent;

    public:
        LayoutEditorTab(ResourceContext& context, Ghurund::UI::Theme& theme) {
            Name = "editor tab";

            propertiesPanel = ghnew PropertyPanel(context, theme);
            propertiesWindow = ghnew ToolWindow(theme);
            propertiesWindow->Title = "Properties";
            propertiesWindow->Content = propertiesPanel;
            propertiesWindow->PreferredSize.width = 200;
            widgetHierarchyPanel = ghnew WidgetHierarchyPanel(context, theme);
            widgetHierarchyWindow = ghnew ToolWindow(theme);
            widgetHierarchyWindow->Title = "Widget";
            widgetHierarchyWindow->Content = widgetHierarchyPanel;
            widgetHierarchyWindow->PreferredSize.width = 200;

            editedControl = ghnew TextButton();
            layoutContent = ghnew StackLayout();
            layoutContent->Alignment = { Alignment::Horizontal::CENTER, Alignment::Vertical::CENTER };
            layoutContent->Children = { editedControl };
            propertiesPanel->Item = editedControl;

            SharedPointer<SplitLayout> widgetHierarchySplit = ghnew SplitLayout();
            widgetHierarchySplit->Orientation = Orientation::HORIZONTAL;
            SharedPointer<SplitLayout> propertiesSplit = ghnew SplitLayout();
            propertiesSplit->Orientation = Orientation::HORIZONTAL;
            widgetHierarchySplit->Child1 = widgetHierarchyWindow;
            widgetHierarchySplit->Child2 = propertiesSplit;
            widgetHierarchySplit->LockedChild = LockedChild::CHILD_1;
            propertiesSplit->Child1 = layoutContent;
            propertiesSplit->Child2 = propertiesWindow;
            propertiesSplit->LockedChild = LockedChild::CHILD_2;
            Child = widgetHierarchySplit;
        }
    };
}
