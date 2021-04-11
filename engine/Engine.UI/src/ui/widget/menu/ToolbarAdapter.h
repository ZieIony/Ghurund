#pragma once

#include "ui/widget/menu/MenuItem.h"

namespace Ghurund::UI {
    class Theme;

    class ButtonToolbarAdapter :public ItemAdapter<MenuItem*, Control> {
    public:
        virtual Control* makeControl() const;

        virtual void bind(Control& control, MenuItem*& item, size_t position) const override;
    };

    class SeparatorToolbarAdapter :public ItemAdapter<MenuItem*, Control>{
    private:
        Theme& theme;

    public:
        SeparatorToolbarAdapter(Theme& theme);

    public:
        virtual Control* makeControl() const;
    };

}