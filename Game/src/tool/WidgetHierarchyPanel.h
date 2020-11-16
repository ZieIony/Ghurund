#pragma once

#include "control/SearchField.h"
#include "control/ToolWindow.h"

#include "ui/Theme.h"
#include "ui/control/TextBlock.h"
#include "ui/widget/tree/TreeView.h"
#include "ui/widget/menu/Toolbar.h"

namespace Ghurund::Editor {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class WidgetHierarchyPanel:public VerticalLayout {
    private:
        ScopedPointer<Toolbar> toolbar;
        ScopedPointer<SearchField> searchField;
        ScopedPointer<TextBlock> objectTypeText;
        TreeViewPtr treeView;
        Gdiplus::Image* sortIcon, * categoryIcon;

    public:
        WidgetHierarchyPanel(Theme& theme) {
            objectTypeText = ghnew TextBlock("", theme.getSecondaryTextFont());
            toolbar = ghnew Toolbar(theme);
            searchField = ghnew SearchField(theme);
            sortIcon = new Gdiplus::Image(L"icons/sort 18.png");
            categoryIcon = new Gdiplus::Image(L"icons/category 18.png");
            toolbar->Items.addAll({
                   ghnew ButtonMenuItem(sortIcon, "sort", [](Ghurund::UI::Control&) {
                       Logger::log(LogType::INFO, "sort clicked\n");
                   }),
                   ghnew ButtonMenuItem(categoryIcon, "category", [](Ghurund::UI::Control&) {
                       Logger::log(LogType::INFO, "category clicked\n");
                   })
                });
            treeView = ghnew TreeView();
            treeView->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
            ScopedPointer<ColorView> separator = ghnew ColorView(theme.getColorForegroundDisabledOnBackground());
            separator->PreferredSize = { PreferredSize::Width::FILL, 1 };
            Children = {
                toolbar,
                searchField,
                separator,
                objectTypeText,
                treeView
            };
        }

        inline void setControl(Control* item) {
            //treeView->Item = item;
            objectTypeText->Text = item->Type.Name;
        }

        __declspec(property(put = setControl)) Control* Control;
    };
}
