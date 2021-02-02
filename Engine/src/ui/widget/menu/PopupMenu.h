#pragma once

#include "PopupMenuAdapter.h"

#include "application/SystemWindow.h"
#include "ui/adapter/RecyclerView.h"
#include "ui/control/ColorView.h"
#include "ui/layout/StackLayout.h"
#include "ui/layout/VerticalLayoutManager.h"

namespace Ghurund::UI {
    class PopupMenu:public StackLayout {
    private:
        Ghurund::PopupWindow* window;
        SharedPointer<ColorView> backgroundView;
        SharedPointer<RecyclerView> recyclerView;
        List<MenuItem*> items;

    public:
        PopupMenu(Ghurund::UI::Theme& theme, Ghurund::Window& parent) {
            window = ghnew Ghurund::PopupWindow(parent.Timer);
            window->RootView->Child = this;

            recyclerView = ghnew RecyclerView();
            recyclerView->LayoutManager = ghnew VerticalLayoutManager();
            auto provider = ghnew AdapterChildrenProvider<MenuItem*, Control>(*recyclerView);
            provider->Adapters.add(ghnew ButtonPopupMenuAdapter());
            provider->Adapters.add(ghnew SeparatorPopupMenuAdapter());
            provider->Items = ghnew ListItemSource<MenuItem*>(items);
            recyclerView->childrenProvider = provider;
            Children = { recyclerView };
            recyclerView->PreferredSize.width = PreferredSize::Width::WRAP;
            recyclerView->PreferredSize.height = PreferredSize::Height::WRAP;
            preferredSize.width = PreferredSize::Width::WRAP;
            preferredSize.height = PreferredSize::Height::WRAP;
        }

        ~PopupMenu() {
            delete window;
            items.deleteItems();
        }

        inline void setVisible(bool visible) {
            measure(100,100);   // TODO: pass parent window size or something
            window->setSize((unsigned int)MeasuredSize.width, (unsigned int)MeasuredSize.height);
            window->dispatchSizeChangedEvent();
            window->Visible = visible;
        }

        inline bool isVisible() {
            return window->Visible;
        }

        __declspec(property(put = setVisible, get = isVisible)) bool Visible;

        void setBackgroundColor(unsigned int color) {
            window->RootView->BackgroundColor = color;
        }

        unsigned int getBackgroundColor() {
            return window->RootView->BackgroundColor;
        }

        __declspec(property(get = getBackgroundColor, put = setBackgroundColor)) unsigned int BackgroundColor;

        inline List<MenuItem*>& getItems() {
            return items;
        }

        inline void setItems(const List<MenuItem*>& items) {
            this->items.clear();
            this->items.addAll(items);
        }

        __declspec(property(get = getItems, put = setItems)) List<MenuItem*>& Items;
    };
}