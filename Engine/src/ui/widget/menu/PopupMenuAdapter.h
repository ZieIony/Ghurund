#pragma once

#include "MenuItem.h"
#include "core/ScopedPointer.h"
#include "ui/Theme.h"
#include "ui/control/ImageView.h"
#include "ui/control/PaddingContainer.h"
#include "ui/control/LinearLayout.h"
#include "ui/control/TextView.h"

namespace Ghurund::UI {
    class ButtonPopupMenuRow:public ClickableView {
    private:
        ScopedPointer<ImageView> icon;
        ScopedPointer<TextView> text;
        ScopedPointer<PaddingContainer> padding;
        ScopedPointer<HorizontalLayout> row;

    public:
        ButtonPopupMenuRow(Theme& theme) {
            icon = ghnew ImageView();
            icon->PreferredSize.width = 16;
            text = ghnew TextView(theme.textViewPrimaryStyle);
            padding = ghnew PaddingContainer(4);
            row = ghnew HorizontalLayout();
            row->PreferredSize.width = PreferredSize::Width::WRAP;
            row->PreferredSize.height = PreferredSize::Height::WRAP;
            row->Children = {icon, text};
            padding->Child = row;
            Child = padding;
            MinSize.width = 150;
        }

        void bind(ButtonMenuItem& item) {
            icon->Image = item.Image;
            text->Text = item.Text;
            OnClicked.clear();
            OnClicked.add([&item](Control& sender, const MouseButton& args) {
                item.ClickEventHandler(sender);
                return true;
            });
        }
    };

    class ButtonPopupMenuAdapter:public ItemAdapter<MenuItem*, Control> {
    private:
        Theme& theme;

    public:
        ButtonPopupMenuAdapter(Theme& theme):theme(theme) {}

        virtual bool canHandleItem(MenuItem* const& item, size_t position) const override {
            return item->type == MenuItemType::BUTTON;
        }

        virtual Control* makeControl() const {
            return ghnew ButtonPopupMenuRow(theme);
        }

        virtual void bind(Control& control, MenuItem* const& item, size_t position) const {
            ButtonPopupMenuRow& textButton = (ButtonPopupMenuRow&)control;
            ButtonMenuItem* menuItem = (ButtonMenuItem*)item;
            textButton.bind(*menuItem);
        }
    };

    class SeparatorPopupMenuAdapter:public ItemAdapter<MenuItem*, Control> {
    private:
        Theme& theme;

    public:
        SeparatorPopupMenuAdapter(Theme& theme):theme(theme) {}

    public:
        virtual bool canHandleItem(MenuItem* const& item, size_t position) const override {
            return item->type == MenuItemType::SEPARATOR;
        }

        virtual Control* makeControl() const {
            ScopedPointer<Style<Separator>> style = ghnew HorizontalSeparatorStyle(theme);
            Separator* separator = ghnew Separator(style);
            separator->PreferredSize.width = PreferredSize::Width::FILL;
            return separator;
        }
    };

}