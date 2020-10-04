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
        String text;

        TextTabItem(const String& text, Control* content):TabItem(content), text(text) {}
    };

    class TabLayout:public Layout {
    protected:
        SelectableView* selectableView;

    public:
        inline SelectableView* getSelectableView() {
            return selectableView;
        }

        __declspec(property(get = getSelectableView)) SelectableView* SelectableView;
    };

    class Tab:public Widget<Tab, TabLayout> {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Tab);

    public:
        Tab(Ghurund::UI::StyleWithLayout<Tab, TabLayout>* style);

        inline static const Ghurund::Type& TYPE = TypeBuilder<Tab>(NAMESPACE_NAME, CLASS_NAME)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}