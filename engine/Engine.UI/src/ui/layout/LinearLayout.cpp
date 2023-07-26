#include "ghuipch.h"
#include "LinearLayout.h"

#include "ui/loading/LayoutLoader.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& LinearLayout::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<LinearLayout>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<LinearLayout>(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(LinearLayout))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool LinearLayout::focusUp() {
        if (__super::focusUp())
            return true;
        if (Focusable)
            return false;
        size_t i = Children.Size - 1;
        if (i == 0)
            return true;
        if (focusedChild) {
            if (Orientation != Orientation::VERTICAL)
                return focusedChild->focusUp();
            i = Children.indexOf(focusedChild);
        }
        for (i; i != -1; i--) {
            if (Children[i]->focusUp())
                return true;
        }
        return false;
    }
    
    bool LinearLayout::focusDown() {
        if (__super::focusDown())
            return true;
        if (Focusable)
            return false;
        size_t i = 0;
        if (i == Children.Size - 1)
            return true;
        if (focusedChild) {
            if (Orientation != Orientation::VERTICAL)
                return focusedChild->focusDown();
            i = Children.indexOf(focusedChild);
        }
        for (i; i < Children.Size; i++) {
            if (Children[i]->focusDown())
                return true;
        }
        return false;
    }
    
    bool LinearLayout::focusLeft() {
        if (__super::focusLeft())
            return true;
        if (Focusable)
            return false;
        size_t i = Children.Size - 1;
        if (i == 0)
            return true;
        if (focusedChild) {
            if (Orientation != Orientation::HORIZONTAL)
                return focusedChild->focusLeft();
            i = Children.indexOf(focusedChild);
        }
        for (i; i != -1; i--) {
            if (Children[i]->focusLeft())
                return true;
        }
        return false;
    }
    
    bool LinearLayout::focusRight() {
        if (Orientation != Orientation::HORIZONTAL)
            return __super::focusRight();
        if (__super::focusRight())
            return true;
        if (Focusable)
            return false;
        size_t i = 0;
        if (i == Children.Size - 1)
            return true;
        if (focusedChild) {
            if (Orientation != Orientation::HORIZONTAL)
                return focusedChild->focusRight();
            i = Children.indexOf(focusedChild);
        }
        for (i; i < Children.Size; i++) {
            if (Children[i]->focusRight())
                return true;
        }
        return false;
    }
    
    void LinearLayout::load(LayoutLoader& loader, ResourceManager& resourceManager, const tinyxml2::XMLElement& xml) {
        __super::load(loader, resourceManager, xml);
        auto orientationAttr = xml.FindAttribute("orientation");
        if (orientationAttr)
            Orientation = strcmp(orientationAttr->Value(), "horizontal") == 0 ? Orientation::HORIZONTAL : Orientation::VERTICAL;
        Ghurund::UI::Alignment a;
        if (loader.loadAlignment(xml, &a) == Status::OK)
            Alignment = a;
    }
}
