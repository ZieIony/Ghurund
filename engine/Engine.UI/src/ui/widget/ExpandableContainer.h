#pragma once

#include "Widget.h"
#include "ExpandableContainerBinding.h"
#include "button/Button.h"
#include "button/CheckBox.h"
#include "ui/control/ImageView.h"

namespace Ghurund::UI {
    class ExpandableContainer:public BindingWidget<ExpandableContainer, ExpandableContainerBinding<ExpandableContainer>> {
    private:
        friend class ExpandableContainerBinding<ExpandableContainer>;

        Event<ExpandableContainer> expandedChanged = *this;
        bool expanded;
        EventHandler<CheckBox> checkedChangedHandler = [this](CheckBox&) {
            Expanded = !Expanded;
            expandedChanged();
            return true;
        };

    protected:
        static const Ghurund::Type& GET_TYPE();

    public:
        inline void setExpanded(bool expanded) {
            this->expanded = expanded;
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

        inline void setContent(Control* content) {
            Layout->Content = content;
        }

        __declspec(property(get = getContent, put = setContent)) Control* Content;

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
            /*if (layout->Selectable->Selected) {
                layout->Image->Image = makeShared<BitmapDrawable>(theme->Images[Theme::IMAGE_ARROWDOWN]);
            } else {
                layout->Image->Image = makeShared<BitmapDrawable>(theme->Images[Theme::IMAGE_ARROWRIGHT]);
            }*/
            __super::onStateChanged(control);
        }
    };
}