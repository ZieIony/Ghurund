#include "ghuipch.h"
#include "ToolbarItemAdapter.h"

#include <ui/widget/button/Button.h>
#include "core/resource/ResourceManager.h"

namespace Ghurund::UI {
    Control* ToolbarItemAdapter::makeControl(size_t type) const {
        Button* button = ghnew Button();
        auto layoutPath = ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/layouts/ButtonIconLayout.xml");
        Control* layout = resourceManager.load<Control>(layoutPath);
        button->Layout = std::make_unique<LayoutValue>(LayoutValue(layout));
        //DrawableView* drawableView = ghnew DrawableView();
        //drawableView->Name = "drawableView";
        //button->Content = drawableView;
        layout->release();
        return button;
    }
    
    void ToolbarItemAdapter::bind(Control& control, size_t position) const {
        Button& button = (Button&)control;
        //DrawableView* drawableView = (DrawableView*)control.find("drawableView");
        auto& menuItem = (SharedPointer<ButtonMenuItem>&)Items[position];
        button.Name = convertText<wchar_t, char>(menuItem->Text);
        //drawableView->Drawable = menuItem->Image;
        button.clicked.clear();
        button.clicked.add([&](Control& sender, const MouseClickedEventArgs& args) {
            menuItem->ClickEventHandler(sender);
            return true;
        });
    }
}
