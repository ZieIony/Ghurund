#include "ghuipch.h"
#include "MenuBarItemAdapter.h"

#include "core/resource/ResourceManager.h"
#include "ui/widget/button/Button.h"

namespace Ghurund::UI {
    Control* MenuBarItemAdapter::makeControl(size_t type) const {
        Button* button = ghnew Button();
        auto layoutPath = ResourceManager::ENGINE_LIB / FilePath(L"/layouts/ButtonIconLayout.xml");
        Control* layout = resourceManager.load<Control>(layoutPath);
        button->Layout = std::make_unique<LayoutValue>(LayoutValue(layout));
        //DrawableView* drawableView = ghnew DrawableView();
        //drawableView->Name = "drawableView";
        //button->Content = drawableView;
        layout->release();
        return button;
    }
    
    void MenuBarItemAdapter::bind(Control& control, size_t position) const {
        Button& button = (Button&)control;
        //DrawableView* drawableView = (DrawableView*)control.find("drawableView");
        auto& menuItem = (SharedPointer<ButtonMenuItem>&)Items[position];
        //button.Name = convertText<wchar_t, char>(menuItem->Text);
        //drawableView->Drawable = menuItem->Image;
        button.clicked.clear();
        button.clicked.add([&](Control& sender, const MouseClickedEventArgs& args) {
            //menuItem->ClickEventHandler(sender);
            return true;
        });
    }
}
