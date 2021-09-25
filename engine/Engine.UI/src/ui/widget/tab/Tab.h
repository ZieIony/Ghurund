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

    class TabLayout:public LayoutBinding {
    protected:
        SelectableView* selectableView;

    public:
        TabLayout(Control* control):LayoutBinding(control) {}

        inline SelectableView* getSelectableView() {
            return selectableView;
        }

        __declspec(property(get = getSelectableView)) SelectableView* SelectableView;
    };

    class Tab:public Widget<TabLayout> {
    private:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<Tab>(NAMESPACE_NAME, GH_STRINGIFY(Tab))
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        virtual void onLayoutChanged() override {
            if (Layout)
                Layout->SelectableView->StateChanged.add([this](Control& control) { return StateChanged(); });
        }

    public:
        Tab() {
            Focusable = true;
        }

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };
}