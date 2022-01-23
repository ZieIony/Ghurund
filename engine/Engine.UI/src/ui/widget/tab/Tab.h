#pragma once

#include "ui/control/SelectableView.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class TabItem {
    public:
        Control* content = nullptr;

        TabItem(Control* content) {
            this->content = content;
            if (content)
                content->addReference();
        }

        virtual ~TabItem() {
            if (content)
                content->release();
        }
    };

    class TextTabItem:public TabItem {
    public:
        Ghurund::Core::WString text;

        TextTabItem(const Ghurund::Core::WString& text, Control* content):TabItem(content), text(text) {}
    };

    class Tab:public Widget {
    private:
        SelectableView* selectableView;
 
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<Tab>(NAMESPACE_NAME, GH_STRINGIFY(Tab))
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        virtual void bind() override {
            __super::bind();
            selectableView->stateChanged += [this](Control& control) { return stateChanged(); };
        }

    public:
        Tab() {
            Focusable = true;
        }

        inline void setSelected(bool selected) {
            selectableView->Selected = selected;
        }

        inline bool isSelected() const {
            return selectableView->Selected;
        }

        __declspec(property(get = isSelected, put = setSelected)) bool Selected;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };
}