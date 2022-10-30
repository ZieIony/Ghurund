#include "ghuipch.h"
#include "ControlContainer.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/control/InvalidControl.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& ControlContainer::GET_TYPE() {

        static auto PROPERTY_CHILD = Property<ControlContainer, Control*>("Child", (Control * (ControlContainer::*)()) & getChild, (void(ControlContainer::*)(Control*)) & setChild);

        static const auto CONSTRUCTOR = Constructor<ControlContainer>();

        static const Ghurund::Core::Type TYPE = TypeBuilder<ControlContainer>(Ghurund::UI::NAMESPACE_NAME, "ControlContainer")
            .withProperty(PROPERTY_CHILD)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool ControlContainer::focusNext() {
        if (__super::focusNext())
            return true;
        return child && child->focusNext();
    }

    bool ControlContainer::focusPrevious() {
        if (__super::focusPrevious())
            return true;
        return child && child->focusPrevious();
    }

    bool ControlContainer::focusUp() {
        if (__super::focusUp())
            return true;
        return child && child->focusUp();
    }

    bool ControlContainer::focusDown() {
        if (__super::focusDown())
            return true;
        return child && child->focusDown();
    }

    bool ControlContainer::focusLeft() {
        if (__super::focusLeft())
            return true;
        return child && child->focusLeft();
    }

    bool ControlContainer::focusRight() {
        if (__super::focusRight())
            return true;
        return child && child->focusRight();
    }

    void ControlContainer::dispatchStateChanged() {
        __super::dispatchStateChanged();
        if (child)
            child->dispatchStateChanged();
    }

    void ControlContainer::dispatchThemeChanged() {
        __super::dispatchThemeChanged();
        if (child)
            child->dispatchThemeChanged();
    }

    void ControlContainer::dispatchContextChanged() {
        __super::dispatchContextChanged();
        if (child)
            child->dispatchContextChanged();
    }

    void ControlContainer::onMeasure(float parentWidth, float parentHeight) {
        __super::onMeasure(parentWidth, parentHeight);

        if (child) {
            child->measure(
                preferredSize.width.Type == PreferredSize::Type::PIXELS ? preferredSize.width.Value : parentWidth,
                preferredSize.height.Type == PreferredSize::Type::PIXELS ? preferredSize.height.Value : parentHeight
            );
            float childWidth = child->PreferredSize.width.Type == PreferredSize::Type::PIXELS ? child->PreferredSize.width.Value : child->MeasuredSize.Width;
            measuredSize.Width = std::max(measuredSize.Width, childWidth);
            float childHeight = child->PreferredSize.height.Type == PreferredSize::Type::PIXELS ? child->PreferredSize.height.Value : child->MeasuredSize.Height;
            measuredSize.Height = std::max(measuredSize.Height, childHeight);
        }
    }

    bool ControlContainer::dispatchKeyEvent(const KeyEventArgs& event) {
        if (child && child->dispatchKeyEvent(event))
            return true;
        return __super::dispatchKeyEvent(event);
    }

    bool ControlContainer::dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
        if (child
            && (capturedChild || child->canReceiveEvent(event))
            && child->dispatchMouseButtonEvent(event.translate(-child->Position.x, -child->Position.y, true)))
            return true;
        return __super::dispatchMouseButtonEvent(event);
    }

    bool ControlContainer::dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
        if (child) {
            if (capturedChild || child->canReceiveEvent(event)) {
                previousReceiver = true;
                if (child->dispatchMouseMotionEvent(event.translate(-child->Position.x, -child->Position.y, true)))
                    return true;
            } else if (previousReceiver) {
                previousReceiver = false;
                if (child->dispatchMouseMotionEvent(event.translate(-child->Position.x, -child->Position.y, false)))
                    return true;
            }
        }
        return __super::dispatchMouseMotionEvent(event);
    }

    bool ControlContainer::dispatchMouseWheelEvent(const MouseWheelEventArgs& event) {
        if (child && child->canReceiveEvent(event) && child->dispatchMouseWheelEvent(event.translate(-child->Position.x, -child->Position.y)))
            return true;
        return __super::dispatchMouseWheelEvent(event);
    }

    Control* ControlContainer::find(const AString& name) {
        if (Name && *Name == name)
            return this;
        if (child)
            return child->find(name);
        return nullptr;
    }

    Control* ControlContainer::find(const Ghurund::Core::Type& type) {
        if (Type == type)
            return this;
        if (child)
            return child->find(type);
        return nullptr;
    }

    void ControlContainer::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        __super::load(loader, xml);
        auto child = xml.FirstChildElement();
        if (child) {
            Control* control = loader.loadControl(*child);
            if (control) {
                Child = control;
            } else {
                Child = ghnew InvalidControl();
            }
            Child->release();
        }
    }

    void ControlContainer::validate() const {
        __super::validate();
        if (child)
            child->validate();
    }

    String ControlContainer::printTree() const {
        String str = __super::printTree();
        size_t len = 4;
        if (child) {
            auto childStr = child->printTree().split(_T("\n"));
            str.add(_T("\n"));
            for (size_t j = 0; j < len; j++)
                str.add(_T(" "));
            str.add(_T("\\-"));
            str.add(childStr[0]);
            for (size_t i = 1; i < childStr.Size; i++) {
                str.add(_T("\n"));
                for (size_t j = 0; j < len + 2; j++)
                    str.add(_T(" "));
                str.add(childStr[i]);
            }
        }
        return str;
    }
}