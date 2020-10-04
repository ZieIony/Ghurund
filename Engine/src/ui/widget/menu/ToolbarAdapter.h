#pragma once

#include "ui/widget/menu/MenuItem.h"

namespace Ghurund::UI {
    class Theme;

    class ButtonToolbarAdapter :public ItemAdapter<MenuItem*, Control> {
    private:
        Theme& theme;

    public:
        ButtonToolbarAdapter(Theme& theme);

        virtual bool canHandleItem(MenuItem* const& item, size_t position) const override {
            return item->type == MenuItemType::BUTTON;
        }

        virtual Control* makeControl() const;

        virtual void bind(Control& control, MenuItem* const& item, size_t position) const override;
    };

    class SeparatorToolbarAdapter :public ItemAdapter<MenuItem*, Control>{
    private:
        Theme& theme;

    public:
        SeparatorToolbarAdapter(Theme& theme);

    public:
        virtual bool canHandleItem(MenuItem* const& item, size_t position) const override {
            return item->type == MenuItemType::SEPARATOR;
        }

        virtual Control* makeControl() const;
    };

}