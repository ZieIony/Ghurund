#include "ControlContainer.h"
#include "ui/LayoutLoader.h"
#include "core/logging/Logger.h"

namespace Ghurund::UI {
    bool ControlContainer::focusNext() {
        if (__super::focusNext())
            return true;
        if (Focusable)
            return false;
        return child && child->focusNext();
    }

    bool ControlContainer::focusPrevious() {
        if (__super::focusPrevious())
            return true;
        if (Focusable)
            return false;
        return child && child->focusPrevious();
    }

    bool ControlContainer::focusUp() {
        if (__super::focusUp())
            return true;
        if (Focusable)
            return false;
        return child && child->focusUp();
    }

    bool ControlContainer::focusDown() {
        if (__super::focusDown())
            return true;
        if (Focusable)
            return false;
        return child && child->focusDown();
    }

    bool ControlContainer::focusLeft() {
        if (__super::focusLeft())
            return true;
        if (Focusable)
            return false;
        return child && child->focusLeft();
    }

    bool ControlContainer::focusRight() {
        if (__super::focusRight())
            return true;
        if (Focusable)
            return false;
        return child && child->focusRight();
    }

    void ControlContainer::dispatchContextChanged() {
        __super::dispatchContextChanged();
        if (child)
            child->dispatchContextChanged();
    }

    void ControlContainer::onMeasure(float parentWidth, float parentHeight) {
        if (child) {
            child->measure(
                PreferredSize.width >= 0 ? (float)PreferredSize.width : parentWidth,
                PreferredSize.height >= 0 ? (float)PreferredSize.height : parentHeight
            );
        }

        if (preferredSize.width >= 0) {
            measuredSize.width = std::max(minSize.width, (float)preferredSize.width);
        } else if (child) {
            if (child->PreferredSize.width >= 0) {
                measuredSize.width = std::max(child->MinSize.width, (float)child->PreferredSize.width);
            } else {
                measuredSize.width = child->MeasuredSize.width;
            }
        } else {
            measuredSize.width = minSize.width;
        }
        if (preferredSize.height >= 0) {
            measuredSize.height = std::max(minSize.height, (float)preferredSize.height);
        } else if (child) {
            if (child->PreferredSize.height >= 0) {
                measuredSize.height = std::max(child->MinSize.height, (float)child->PreferredSize.height);
            } else {
                measuredSize.height = child->MeasuredSize.height;
            }
        } else {
            measuredSize.height = minSize.height;
        }
    }

    bool ControlContainer::dispatchKeyEvent(const Ghurund::Input::KeyEventArgs& event) {
        if (child && child->dispatchKeyEvent(event))
            return true;
        return __super::dispatchKeyEvent(event);
    }

    bool ControlContainer::dispatchMouseButtonEvent(const Ghurund::Input::MouseButtonEventArgs& event) {
        if (child
            && (capturedChild || child->canReceiveEvent(event))
            && child->dispatchMouseButtonEvent(event.translate(-child->Position.x, -child->Position.y, true)))
            return true;
        return __super::dispatchMouseButtonEvent(event);
    }

    bool ControlContainer::dispatchMouseMotionEvent(const Ghurund::Input::MouseMotionEventArgs& event) {
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

    bool ControlContainer::dispatchMouseWheelEvent(const Ghurund::Input::MouseWheelEventArgs& event) {
        if (child && child->canReceiveEvent(event) && child->dispatchMouseWheelEvent(event.translate(-child->Position.x, -child->Position.y)))
            return true;
        return __super::dispatchMouseWheelEvent(event);
    }

    Control* ControlContainer::find(const String& name) {
        if (this->Name && this->Name->operator==(name))
            return this;
        if (child)
            return child->find(name);
        return nullptr;
    }

    Status ControlContainer::load(LayoutLoader& loader, ResourceContext& context, const tinyxml2::XMLElement& xml) {
        Status result = __super::load(loader, context, xml);
        if (result != Status::OK)
            return result;
        auto child = xml.FirstChildElement();
        if (child) {
            Control* control = loader.loadControl(context, *child);
            if (control) {
                Child = control;
                control->release();
            }
        }
        return Status::OK;
    }

#ifdef _DEBUG
    String ControlContainer::logTree() {
        String log = __super::logTree();
        if (child) {
            auto array = child->logTree().split(_T("\n"));
            if (!array.Empty) {
                String& s = array[0];
                log.add(fmt::format(_T(" + {}\n"), s).c_str());
            }
            for (size_t i = 1; i < array.Size; i++) {
                String& s = array[i];
                log.add(fmt::format(_T("   {}\n"), s).c_str());
            }
        }
        return log;
    }
#endif
}