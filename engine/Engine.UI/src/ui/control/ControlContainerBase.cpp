#include "ghuipch.h"
#include "ControlContainer.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "ui/constraint/ConstraintGraph.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& ControlContainerBase::GET_TYPE() {

		static const Ghurund::Core::Type TYPE = TypeBuilder<ControlContainerBase>(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(ControlContainerBase))
			.withModifier(TypeModifier::ABSTRACT)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	bool ControlContainerBase::focusNext() {
		if (__super::focusNext())
			return true;
		return child && child->focusNext();
	}

	bool ControlContainerBase::focusPrevious() {
		if (__super::focusPrevious())
			return true;
		return child && child->focusPrevious();
	}

	bool ControlContainerBase::focusUp() {
		if (__super::focusUp())
			return true;
		return child && child->focusUp();
	}

	bool ControlContainerBase::focusDown() {
		if (__super::focusDown())
			return true;
		return child && child->focusDown();
	}

	bool ControlContainerBase::focusLeft() {
		if (__super::focusLeft())
			return true;
		return child && child->focusLeft();
	}

	bool ControlContainerBase::focusRight() {
		if (__super::focusRight())
			return true;
		return child && child->focusRight();
	}

	void ControlContainerBase::dispatchStateChanged() {
		__super::dispatchStateChanged();
		if (child)
			child->dispatchStateChanged();
	}

	void ControlContainerBase::dispatchThemeChanged() {
		__super::dispatchThemeChanged();
		if (child)
			child->dispatchThemeChanged();
	}

	void ControlContainerBase::dispatchContextChanged() {
		__super::dispatchContextChanged();
		if (child)
			child->dispatchContextChanged();
	}

	void ControlContainerBase::onMeasure() {
		__super::onMeasure();

		if (child)
			child->measure();
	}

	bool ControlContainerBase::dispatchKeyEvent(const KeyEventArgs& event) {
		if (child && child->canReceiveEvent(event) && child->dispatchKeyEvent(event))
			return true;
		return __super::dispatchKeyEvent(event);
	}

	bool ControlContainerBase::dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
		if (child
			&& (capturedChild || child->canReceiveEvent(event))
			&& child->dispatchMouseButtonEvent(event.translate(-child->Position.x, -child->Position.y, true)))
			return true;
		return __super::dispatchMouseButtonEvent(event);
	}

	bool ControlContainerBase::dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
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

	bool ControlContainerBase::dispatchMouseWheelEvent(const MouseWheelEventArgs& event) {
		if (child && child->canReceiveEvent(event) && child->dispatchMouseWheelEvent(event.translate(-child->Position.x, -child->Position.y)))
			return true;
		return __super::dispatchMouseWheelEvent(event);
	}

	void ControlContainerBase::resolveConstraints(ConstraintGraph& graph) {
		__super::resolveConstraints(graph);
		if (child && child->Visible)
			child->resolveConstraints(graph);
	}

#ifdef _DEBUG
	void ControlContainerBase::validate() const {
		__super::validate();
		if (child)
			child->validate();
	}

	String ControlContainerBase::printTree() const {
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
#endif
}