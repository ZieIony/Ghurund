#pragma once

#include "control/SearchField.h"
#include "control/ToolWindow.h"

#include "ui/Theme.h"
#include "ui/control/TextBlock.h"
#include "ui/widget/property/PropertyList.h"
#include "ui/widget/menu/Toolbar.h"

using namespace Ghurund;
using namespace Ghurund::UI;

namespace Ghurund::Editor {
    class PropertyPanel:public VerticalLayout {
    private:
        ScopedPointer<Toolbar> toolbar;
        ScopedPointer<SearchField> searchField;
        ScopedPointer<TextBlock> objectTypeText;
        PropertyListPtr propertyList;
        BitmapImage* sortIcon, * categoryIcon;

    public:
        PropertyPanel(ResourceContext& context, Theme& theme) {
            objectTypeText = ghnew TextBlock("", theme.getSecondaryTextFont());
            toolbar = ghnew Toolbar(theme);
            searchField = ghnew SearchField(theme);
            sortIcon = BitmapImage::makeFromImage(context, L"icons/sort 18.png");
            categoryIcon = BitmapImage::makeFromImage(context, L"icons/category 18.png");
            toolbar->Items = {
                   ghnew ButtonMenuItem(sortIcon, "sort", [](Control&) {
                       Logger::log(LogType::INFO, "sort clicked\n");
                   }),
                   ghnew ButtonMenuItem(categoryIcon, "category", [](Control&) {
                       Logger::log(LogType::INFO, "category clicked\n");
                   })
            };
            propertyList = ghnew PropertyList(theme);
            propertyList->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
            ScopedPointer<ColorView> separator = makeScoped<ColorView>(theme.getColorForegroundDisabledOnBackground());
            separator->PreferredSize = { PreferredSize::Width::FILL, 1 };
            Children = {
                toolbar,
                searchField,
                separator,
                objectTypeText,
                propertyList
            };
        }

        inline void setItem(Object* item) {
            propertyList->Item = item;
            objectTypeText->Text = item->Type.Name;
        }

        __declspec(property(put = setItem)) Object* Item;
    };
}
