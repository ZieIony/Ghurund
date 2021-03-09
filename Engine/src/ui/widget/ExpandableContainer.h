#pragma once

#include "ContainerWidget.h"
#include "ExpandableContainerBinding.h"
#include "button/Button.h"
#include "button/CheckBox.h"
#include <ui/drawable/BitmapImageDrawable.h>
#include "ui/control/ImageView.h"

namespace Ghurund::UI {
    class ExpandableContainer:public ContainerWidget<ExpandableContainerBinding> {
    private:
        Event<ExpandableContainer> expandedChanged = *this;
        bool expanded;

    protected:
        static const Ghurund::Type& GET_TYPE();

        virtual void onLayoutChanged() override {
            if (!Layout)
                return;
            Layout->ExpandButton->Checked = expanded;
            Layout->ExpandButton->CheckedChanged.add([this](CheckBox& control) {
                Expanded = control.Checked;
                expandedChanged();
                return true;
            });
            dispatchStateChanged();
        }

    public:
        inline void setExpanded(bool expanded) {
            this->expanded = expanded;
            Layout->ExpandButton->Checked = expanded;
            onStateChanged();
        }

        inline bool isExpanded() {
            return expanded;
        }

        __declspec(property(get = isExpanded, put = setExpanded)) bool Expanded;

        inline Event<ExpandableContainer>& getExpandedChanged() {
            return expandedChanged;
        }

        __declspec(property(get = getExpandedChanged)) Event<ExpandableContainer>& ExpandedChanged;

        inline Control* getHeader() {
            return Layout->Header;
        }

        inline void setHeader(Control* header) {
            Layout->Header = header;
        }

        __declspec(property(get = getHeader, put = setHeader)) Control* Header;

        inline Control* getContent() {
            return Layout->Content;
        }

        inline void setHeader(Control* header) {
            Layout->Header = header;
        }

        __declspec(property(get = getHeader, put = setHeader)) Control* Header;

        virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;
        
        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    class ExpandableCheckBoxStyle:public CheckBoxRadioStyle {
    public:
        virtual void onStateChanged(Control& control) const override {
            Theme* theme = control.Theme;
            if (!theme)
                return;
            CheckBox& checkBoxRadio = (CheckBox&)control;
            CheckBoxBinding* layout = checkBoxRadio.Layout;
            if (layout->Selectable->Selected) {
                layout->Image->Image = makeShared<BitmapImageDrawable>(theme->Images[Theme::IMAGE_ARROWDOWN]);
            } else {
                layout->Image->Image = makeShared<BitmapImageDrawable>(theme->Images[Theme::IMAGE_ARROWRIGHT]);
            }
            __super::onStateChanged(control);
        }
    };
}