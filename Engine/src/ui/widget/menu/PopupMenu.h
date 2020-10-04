#pragma once

#include "PopupMenuAdapter.h"
#include "ui/UIWindow.h"
#include "ui/control/ColorView.h"
#include "ui/control/StackLayout.h"
#include "ui/control/AdapterView.h"
#include "ui/layout/VerticalLayoutManager.h"

namespace Ghurund::UI {
    class PopupMenu:public StackLayout {
    private:
        UIWindow* window;
        ScopedPointer<ColorView> backgroundView;
        ScopedPointer<AdapterView<MenuItem*>> adapterView;
        List<MenuItem*> items;

    public:
        PopupMenu(Theme& theme, const Ghurund::Window& parent) {
            window = ghnew UIWindow(WindowClass::POPUP, &parent);
            window->RootView->Child = this;

            backgroundView = ghnew ColorView(theme.getColorBackground());
            adapterView = ghnew AdapterView<MenuItem*>();
            adapterView->LayoutManager = ghnew VerticalLayoutManager<MenuItem*, Control>();
            adapterView->Adapters.add(ghnew ButtonPopupMenuAdapter(theme));
            adapterView->Adapters.add(ghnew SeparatorPopupMenuAdapter(theme));
            Children = { backgroundView, adapterView };
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
            window->Window.setSize((unsigned int)MeasuredSize.width, (unsigned int)MeasuredSize.height);
            window->Window.OnSizeChanged();
            window->Window.Visible = visible;
        }

        inline bool isVisible() {
            return window->Window.Visible;
        }

        __declspec(property(put = setVisible, get = isVisible)) bool Visible;

        void setBackgroundColor(unsigned int color) {
            backgroundView->Color = color;
        }

        unsigned int getBackgroundColor() {
            return backgroundView->Color;
        }

        __declspec(property(get = getBackgroundColor, put = setBackgroundColor)) unsigned int BackgroundColor;

        inline List<MenuItem*>& getItems() {
            return items;
        }

        __declspec(property(get = getItems)) List<MenuItem*>& Items;

        virtual Ghurund::Window* getWindow() const override {
            return &window->Window;
        }
    };
}