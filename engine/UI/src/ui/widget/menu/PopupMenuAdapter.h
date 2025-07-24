#pragma once

#include "MenuItem.h"
#include "core/object/SharedPointer.h"
#include "ui/style/Theme.h"
#include "ui/control/DrawableView.h"
#include "ui/control/PaddingContainer.h"
#include "ui/layout/LinearLayout.h"
#include "ui/text/TextBlock.h"

namespace Ghurund::UI {
    class ButtonPopupMenuRow:public ClickableControl {
    private:
        IntrusivePointer<DrawableView> icon;
        IntrusivePointer<TextBlock> text;
        IntrusivePointer<PaddingContainer> padding;
        IntrusivePointer<HorizontalLayout> row;

    public:
        ButtonPopupMenuRow() {
            icon = ghnew DrawableView();
            icon->ContentSize.width = 16;
            text = ghnew TextBlock();
            padding = ghnew PaddingContainer(4);
            row = ghnew HorizontalLayout();
            row->ContentSize.width = ContentSize::Width::WRAP;
            row->ContentSize.height = ContentSize::Height::WRAP;
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
            separator->ContentSize.width = ContentSize::Width::FILL;
            return separator;
        }
    };

}