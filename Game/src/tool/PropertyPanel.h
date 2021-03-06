#pragma once

#include "PropertyPanelBinding.h"
#include "control/SearchField.h"
#include "control/ToolWindow.h"

#include "ui/control/TextBlock.h"
#include "ui/widget/Widget.h"
#include "ui/widget/property/PropertyList.h"
#include "ui/widget/menu/Toolbar.h"

using namespace Ghurund;
using namespace Ghurund::UI;

namespace Ghurund::Editor {
    class PropertyPanel:public Widget<PropertyPanelBinding> {
    private:
        BitmapImage* sortIcon, * categoryIcon;

        virtual void onLayoutChanged() override {
            //sortIcon = BitmapImage::makeFromImage(context, L"icons/sort 18.png");
            //categoryIcon = BitmapImage::makeFromImage(context, L"icons/category 18.png");
            Layout->Toolbar->Items = {
                   ghnew ButtonMenuItem(sortIcon, L"sort", [](Control&) {
                       Logger::log(LogType::INFO, "sort clicked\n");
                   }),
                   ghnew ButtonMenuItem(categoryIcon, L"category", [](Control&) {
                       Logger::log(LogType::INFO, "category clicked\n");
                   })
            };
        }

    public:
        inline void setItem(Object* item) {
            Layout->PropertyList->Item = item;
            Layout->ObjectType->Text = toWideChar(AString(item->Type.Name));
        }

        __declspec(property(put = setItem)) Object* Item;
    };
}
