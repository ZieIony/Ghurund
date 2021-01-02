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
        WString text;

        TextTabItem(const WString& text, Control* content):TabItem(content), text(text) {}
    };

    class TabLayout:public WidgetLayout {
    protected:
        SelectableView* selectableView;

    public:
        inline SelectableView* getSelectableView() {
            return selectableView;
        }

        __declspec(property(get = getSelectableView)) SelectableView* SelectableView;
    };

    class Tab:public Widget<TabLayout> {
    private:
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Tab))
                .withSupertype(__super::TYPE);

            return TYPE;
        }

    public:
        Tab(TabLayout* layout):Widget(layout) {
            Focusable = true;
            Layout.SelectableView->OnStateChanged.add(OnStateChanged);
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}