#pragma once

#include "control/SearchField.h"
#include "control/ToolWindow.h"

#include "ui/style/Theme.h"
#include "ui/control/TextBlock.h"
#include "ui/widget/tree/TreeView.h"
#include "ui/widget/menu/Toolbar.h"
#include <core/string/TextConversionUtils.h>

namespace Ghurund::Editor {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class WidgetHierarchyPanel:public VerticalLayout {
    private:
        SharedPointer<Toolbar> toolbar;
        SharedPointer<SearchField> searchField;
        SharedPointer<TextBlock> objectTypeText;
        TreeViewPtr treeView;
        BitmapImage* sortIcon, * categoryIcon;

    public:
        WidgetHierarchyPanel(ResourceContext& context, Ghurund::UI::Theme& theme) {
            objectTypeText = ghnew TextBlock(L"", theme.TextFormats[Theme::TEXTFORMAT_TEXT_SECONDARY]);
            toolbar = ghnew Toolbar();
            searchField = ghnew SearchField();
            sortIcon = BitmapImage::makeFromImage(context, L"icons/sort 18.png");
            categoryIcon = BitmapImage::makeFromImage(context, L"icons/category 18.png");
            toolbar->Items = {
                   ghnew ButtonMenuItem(sortIcon, L"sort", [](Ghurund::UI::Control&) {
                       Logger::log(LogType::INFO, "sort clicked\n");
                   }),
                   ghnew ButtonMenuItem(categoryIcon, L"category", [](Ghurund::UI::Control&) {
                       Logger::log(LogType::INFO, "category clicked\n");
                   })
            };
            treeView = ghnew TreeView();
            treeView->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
            /*SharedPointer<ColorView> separator = ghnew ColorView(theme.getColorForegroundDisabledOnBackground());
            separator->PreferredSize = { PreferredSize::Width::FILL, 1 };
            Children = {
                toolbar,
                searchField,
                separator,
                objectTypeText,
                treeView
            };*/
        }

        inline void setControl(Control* item) {
            //treeView->Item = item;
            objectTypeText->Text = convertText(item->Type.Name);
        }

        __declspec(property(put = setControl)) Control* Control;
    };
}
