#pragma once

#include "PopupMenuAdapter.h"

#include "application/Window.h"
#include "ui/adapter/AdapterView.h"
#include "ui/control/ColorView.h"
#include "ui/layout/StackLayout.h"
#include "ui/layout/VerticalLayoutManager.h"

namespace Ghurund::UI {
    class PopupMenu:public StackLayout {
    private:
        Ghurund::PopupWindow* window;
        ScopedPointer<ColorView> backgroundView;
        ScopedPointer<AdapterView<MenuItem*>> adapterView;
        List<MenuItem*> items;

    public:
        PopupMenu(Theme& theme, Ghurund::Window& parent) {
            window = ghnew Ghurund::PopupWindow();
            window->RootView->Child = this;

            adapterView = ghnew AdapterView<MenuItem*>();
            adapterView->LayoutManager = ghnew VerticalLayoutManager<MenuItem*, Control>();
            adapterView->Adapters.add(ghnew ButtonPopupMenuAdapter(theme));
            adapterView->Adapters.add(ghnew SeparatorPopupMenuAdapter(theme));
            Children = { adapterView };
            adapterView->PreferredSize.width = PreferredSize::Width::WRAP;
            adapterView->PreferredSize.height = PreferredSize::Height::WRAP;
            adapterView->Items = ghnew ListItemSource<MenuItem*>(items);
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
            window->OnSizeChanged();
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

        __declspec(property(get = getItems)) List<MenuItem*>& Items;

        virtual Ghurund::Window* getWindow() const override {
            return window;
        }
    };
}