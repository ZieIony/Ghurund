#pragma once

#include "MenuItem.h"
#include "core/SharedPointer.h"
#include "ui/style/Theme.h"
#include "ui/control/DrawableView.h"
#include "ui/control/PaddingContainer.h"
#include "ui/layout/LinearLayout.h"
#include "ui/text/TextBlock.h"

namespace Ghurund::UI {
    class ButtonPopupMenuRow:public ClickableControl {
    private:
        SharedPointer<DrawableView> icon;
        SharedPointer<TextBlock> text;
        SharedPointer<PaddingContainer> padding;
        SharedPointer<HorizontalLayout> row;

    public:
        ButtonPopupMenuRow() {
            icon = ghnew DrawableView();
            icon->PreferredSize.width = 16;
            text = ghnew TextBlock();
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
//            icon->Image = item.Image;
            text->Text = item.Text;
            Clicked.clear();
            Clicked.add([&item](Control& sender, const MouseClickedEventArgs& args) {
                item.ClickEventHandler(sender);
                return true;
            });
        }
    };

    class ButtonPopupMenuAdapter:public ItemAdapter<MenuItem*, Control> {
    public:
        virtual Control* makeControl() const {
            return ghnew ButtonPopupMenuRow();
        }

        virtual void bind(Control& control, MenuItem* const& item, size_t position) const {
            ButtonPopupMenuRow& textButton = (ButtonPopupMenuRow&)control;
            ButtonMenuItem* menuItem = (ButtonMenuItem*)item;
            textButton.bind(*menuItem);
        }
    };

    class SeparatorPopupMenuAdapter:public ItemAdapter<MenuItem*, Control> {
    public:
        virtual Control* makeControl() const {
            Separator* separator = ghnew Separator();
            //SeparatorHorizontalStyle()
            separator->PreferredSize.width = PreferredSize::Width::FILL;
            return separator;
        }
    };

}