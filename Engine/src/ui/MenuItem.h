#pragma once

#include "ui/gdi/GdiImage.h"

namespace Ghurund::UI {
    enum class MenuItemType {

    };

    class MenuItem {

    };

    class ButtonMenuItem:public MenuItem {
    private:
        GdiImage* image = nullptr;
        tchar* text = nullptr;

    public:
        ButtonMenuItem(GdiImage* image, const tchar* text) {
            if (image) {
                image->addReference();
                this->image = image;
            }
        }
    };

    class SeparatorMenuItem {

    };

    class ToolbarAdapter {

    };

    class Toolbar {

    };
}