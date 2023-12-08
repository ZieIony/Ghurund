#pragma once

#include "Widget.h"
#include "button/Button.h"
#include "button/CheckBox.h"
#include "ui/control/DrawableView.h"

namespace Ghurund::UI {
    class ExpandableContainer:public ContentWidget {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ExpandableContainer::GET_TYPE();
#pragma endregion

    private:
        Control* header = nullptr;

        Event<ExpandableContainer> expandedChanged = *this;
        bool expanded;
        EventHandler<CheckBox> checkedChangedHandler = [this](CheckBox&) {
            Expanded = !Expanded;
            expandedChanged();
            return true;
        };

    public:
        inline void setExpanded(bool expanded) {
            this->expanded = expanded;
            dispatchStateChanged();
        }

        inline bool isExpanded() const {
            return expanded;
        }

        __declspec(property(get = isExpanded, put = setExpanded)) bool Expanded;

        inline Event<ExpandableContainer>& getExpandedChanged() {
            return expandedChanged;
        }

        __declspec(property(get = getExpandedChanged)) Event<ExpandableContainer>& ExpandedChanged;

        inline Control* getHeader() {
            return header;
        }

        inline void setHeader(Control* header) {
            header = header;
        }

        __declspec(property(get = getHeader, put = setHeader)) Control* Header;
    };

    /*class ExpandableCheckBoxStyle:public Style {
    public:
        virtual void onStateChanged(Control& control) const override {
            const Theme* theme = control.Theme;
            if (!theme)
                return;
            CheckBox& checkBoxRadio = (CheckBox&)control;
            /*if (layout->Selectable->Selected) {
                layout->Image->Image = makeShared<BitmapDrawable>(theme->Drawables[Theme::IMAGE_ARROWDOWN]);
            } else {
                layout->Image->Image = makeShared<BitmapDrawable>(theme->Drawables[Theme::IMAGE_ARROWRIGHT]);
            }* /
            __super::onStateChanged(control);
        }
    };*/
}