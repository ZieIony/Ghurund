#include "ghuipch.h"
#include "ControlGroup.h"

#include "ui/Alignment.h"
#include "ui/constraint/ConstraintGraph.h"
#include "ui/loading/LayoutLoader.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& ControlGroup::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<ControlGroup>();
        static Ghurund::Core::Type TYPE = TypeBuilder<ControlGroup>(NAMESPACE_NAME, GH_STRINGIFY(ControlGroup))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void ControlGroup::onMeasure() {
        for (Control* c : children) {
            if (!c->Visible)
                continue;
            c->measure();
        }
    }

    void ControlGroup::onLayout(float x, float y, float width, float height) {
        for (Control* c : children) {
            if (!c->Visible)
                continue;
            c->layout(
                c->Left.Value,
                c->Top.Value,
                c->Width.Value,
                c->Height.Value
            );
        }
    }

    bool ControlGroup::focusNext() {
        if (__super::focusNext())
            return true;
        size_t i = 0;
        if (focusedChild)
            i = Children.indexOf(focusedChild);
        for (i; i < Children.Size; i++) {
            if (Children[i]->focusNext())
                return true;
        }
        return false;
    }

    bool ControlGroup::focusPrevious() {
        if (__super::focusPrevious())
            return true;
        size_t i = Children.Size - 1;
        if (focusedChild)
            i = Children.indexOf(focusedChild);
        for (i; i != -1; i--) {
            if (Children[i]->focusPrevious())
                return true;
        }
        return false;
    }

    bool ControlGroup::focusUp() {
        if (__super::focusUp())
            return true;
        return focusedChild && focusedChild->focusUp();
    }

    bool ControlGroup::focusDown() {
        if (__super::focusDown())
            return true;
        return focusedChild && focusedChild->focusDown();
    }

    bool ControlGroup::focusLeft() {
        if (__super::focusLeft())
            return true;
        return focusedChild && focusedChild->focusLeft();
    }

    bool ControlGroup::focusRight() {
        if (__super::focusRight())
            return true;
        return focusedChild && focusedChild->focusRight();
    }

    void ControlGroup::dispatchStateChanged() {
        __super::dispatchStateChanged();
        for (Control* child : Children)
            child->dispatchStateChanged();
    }

    void ControlGroup::dispatchThemeChanged() {
        __super::dispatchThemeChanged();
        for (Control* child : Children)
            child->dispatchThemeChanged();
    }

    void ControlGroup::dispatchContextChanged() {
        __super::dispatchContextChanged();
        for (Control* child : Children)
            child->dispatchContextChanged();
    }

    void ControlGroup::onDraw(ICanvas& canvas) {
        for (Control* c : children) {
            if (!c->Visible)
                continue;
            c->draw(canvas);
        }
    }

    bool ControlGroup::dispatchKeyEvent(const KeyEventArgs& event) {
        if (focusedChild)
            return focusedChild->dispatchKeyEvent(event);
        for (size_t i = 0; i < children.Size; i++) {
            Control* c = children.get(children.Size - i - 1);
            if (c->dispatchKeyEvent(event))
                return true;
        }
        return __super::dispatchKeyEvent(event);
    }

    bool ControlGroup::dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
        if (capturedChild) {
            auto e = event.translate(-capturedChild->Position.x, -capturedChild->Position.y, capturedChild->canReceiveEvent(event));
            return capturedChild->dispatchMouseButtonEvent(e);
        }

        for (size_t i = 0; i < children.Size; i++) {
            Control* c = children.get(children.Size - i - 1);
            if (c->canReceiveEvent(event) && c->dispatchMouseButtonEvent(event.translate(-c->Position.x, -c->Position.y, true)))
                return true;
        }
        return __super::dispatchMouseButtonEvent(event);
    }

    bool ControlGroup::dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
        if (capturedChild) {
            auto e = event.translate(-capturedChild->Position.x, -capturedChild->Position.y, capturedChild->canReceiveEvent(event));
            return capturedChild->dispatchMouseMotionEvent(e);
        }
        if (previousReceiver && !previousReceiver->canReceiveEvent(event)) {
            previousReceiver->dispatchMouseMotionEvent(event.translate(-previousReceiver->Position.x, -previousReceiver->Position.y, false));
            previousReceiver->release();
            previousReceiver = nullptr;
        }

        for (size_t i = 0; i < children.Size; i++) {
            Control* c = children.get(children.Size - i - 1);
            if (c->canReceiveEvent(event)) {
                setPointer(previousReceiver, c);
                if (c->dispatchMouseMotionEvent(event.translate(-c->Position.x, -c->Position.y, true)))
                    return true;
            }
        }
        return __super::dispatchMouseMotionEvent(event);
    }

    bool ControlGroup::dispatchMouseWheelEvent(const MouseWheelEventArgs& event) {
        for (size_t i = 0; i < children.Size; i++) {
            Control* c = children.get(children.Size - i - 1);
            if (c->canReceiveEvent(event) && c->dispatchMouseWheelEvent(event.translate(-c->Position.x, -c->Position.y)))
                return true;
        }
        return __super::dispatchMouseWheelEvent(event);
    }

    Control* ControlGroup::find(const AString& name) {
        if (this->Name && this->Name->operator==(name))
            return this;
        for (Control* child : children) {
            Control* result = child->find(name);
            if (result)
                return result;
        }
        return nullptr;
    }

    Control* ControlGroup::find(const Ghurund::Core::Type& type) {
        if (Type == type)
            return this;
        for (Control* child : children) {
            Control* result = child->find(type);
            if (result)
                return result;
        }
        return nullptr;
    }

    void ControlGroup::resolveConstraints(ConstraintGraph& graph) {
        __super::resolveConstraints(graph);
        for (Control* c : children)
            c->resolveConstraints(graph);
    }

    void ControlGroup::load(LayoutLoader& loader, ResourceManager& resourceManager, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) {
        __super::load(loader, resourceManager, workingDir, xml);
        Children.clear();
        Children.addAll(loader.loadControls(workingDir, xml));
    }
    
#ifdef _DEBUG
    void ControlGroup::validate() const {
        __super::validate();
        for (Control* child : children)
            child->validate();
    }

    String ControlGroup::printTree() const {
        String str = __super::printTree();
        size_t len = 4;
        for (Control* child : children) {
            auto childStr = child->printTree().split(_T("\n"));
            str.add(_T("\n"));
            for (size_t j = 0; j < len; j++)
                str.add(_T(" "));
            str.add(_T("\\-"));
            str.add(childStr[0]);
            for (size_t i = 1; i < childStr.Size; i++) {
                str.add(_T("\n"));
                for (size_t j = 0; j < len; j++)
                    str.add(_T(" "));
                str.add(child != children[children.Size - 1] ? _T("| ") : _T("  "));
                str.add(childStr[i]);
            }
        }
        return str;
    }
#endif
}