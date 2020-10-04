#pragma once

#include "MenuItem.h"
#include "ui/widget/button/TextButton.h"

namespace Ghurund::UI {
    class Theme;

    class ButtonMenuBarAdapter :public ItemAdapter<MenuItem*, Control> {
    private:
        Theme& theme;

    public:
        ButtonMenuBarAdapter(Theme& theme);

        virtual bool canHandleItem(MenuItem* const& item, size_t position) const override {
            return item->type == MenuItemType::BUTTON;
        }

        virtual Control* makeControl() const;

        virtual void bind(Control& control, MenuItem* const& item, size_t position) const;
    };

}