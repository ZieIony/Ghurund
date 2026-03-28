#include "ghuipch.h"
#include "ControlGroup.h"

#include "ListControlProvider.h"
#include "ui/constraint/ConstraintGraph.h"
#include "ui/constraint/ContentConstraint.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/layout/LayoutManager.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& ControlGroup::GET_TYPE() {
		static Ghurund::Core::Type TYPE = TypeBuilder<ControlGroup>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void ControlGroup::loadInternal(LayoutLoader& loader, const DirectoryPath& workingDir, const XMLElement& xml) {
		__super::loadInternal(loader, workingDir, xml);
		Children.clear();
		for(const auto& childElement : xml.children){
			if (!childElement->name.contains(L".")) {
				try {
					ControlWithConstraints control = loader.loadControl(*this, workingDir, childElement.ref());
					children.add(control.control.get(), control.Constraints);
				} catch (...) {
					Logger::log(LogType::WARNING, std::format(_T("Failed to load control {}.\n"), childElement->name).c_str());
				}
			}
		}
	}

	void ControlGroup::onLayout(float x, float y, float width, float height) {
		for (ControlWithConstraints& c : children) {
			Control* control = c.control.get();
			if (!control->Visible)
				continue;
			ConstraintSet& constraintSet = c.Constraints;
			control->layout(
				constraintSet.Left.Value,
				constraintSet.Top.Value,
				constraintSet.Width.Value,
				constraintSet.Height.Value
			);
		}
	}

	bool ControlGroup::onKeyEvent(const KeyEventArgs& event) {
		if (focusedChild)
			return focusedChild->dispatchKeyEvent(event);
		for (size_t i = 0; i < children.Size; i++) {
			ControlWithConstraints& c = children[children.Size - i - 1];
			if (c.control->canReceiveEvent(event) && c.control->dispatchKeyEvent(event))
				return true;
		}
		return false;
	}

	bool ControlGroup::onMouseButtonEvent(const MouseButtonEventArgs& event) {
		if (capturedChild) {
			auto e = event.translate(-capturedChild->Position.x, -capturedChild->Position.y, capturedChild->canReceiveEvent(event));
			return capturedChild->dispatchMouseButtonEvent(e);
		}

		for (size_t i = 0; i < children.Size; i++) {
			ControlWithConstraints& c = children[children.Size - i - 1];
			if (c.control->canReceiveEvent(event) && c.control->dispatchMouseButtonEvent(event.translate(-c.control->Position.x, -c.control->Position.y, true)))
				return true;
		}
		return false;
	}

	bool ControlGroup::onMouseMotionEvent(const MouseMotionEventArgs& event) {
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
			ControlWithConstraints& c = children.get(children.Size - i - 1);
			if (c.control->canReceiveEvent(event)) {
				setPointer(previousReceiver, c.control.get());
				if (c.control->dispatchMouseMotionEvent(event.translate(-c.control->Position.x, -c.control->Position.y, true)))
					return true;
			}
		}
		return false;
	}

	bool ControlGroup::onMouseWheelEvent(const MouseWheelEventArgs& event) {
		for (size_t i = 0; i < children.Size; i++) {
			ControlWithConstraints& c = children[children.Size - i - 1];
			if (c.control->canReceiveEvent(event) && c.control->dispatchMouseWheelEvent(event.translate(-c.control->Position.x, -c.control->Position.y)))
				return true;
		}
		return false;
	}

	ControlGroup::ControlGroup():children(*this) {
		children.collectionChanged += [&](ControlCollection&) {
			needsLayout = true;
			return true;
		};
	}

	ControlGroup::~ControlGroup() {
		if (previousReceiver)
			previousReceiver->release();
		delete layoutManager;
	}

	bool ControlGroup::focusNext() {
		if (__super::focusNext())
			return true;
		size_t i = 0;
		if (focusedChild)
			i = Children.find(focusedChild);
		for (i; i < Children.Size; i++) {
			if (Children[i].control->focusNext())
				return true;
		}
		return false;
	}

	bool ControlGroup::focusPrevious() {
		if (__super::focusPrevious())
			return true;
		size_t i = Children.Size - 1;
		if (focusedChild)
			i = Children.find(focusedChild);
		for (i; i != -1; i--) {
			if (Children[i].control->focusPrevious())
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
		for (ControlWithConstraints& c : children)
			c.control->dispatchStateChanged();
	}

	void ControlGroup::dispatchThemeChanged() {
		__super::dispatchThemeChanged();
		for (ControlWithConstraints& c : children)
			c.control->dispatchThemeChanged();
	}

	void ControlGroup::dispatchContextChanged() {
		__super::dispatchContextChanged();
		for (ControlWithConstraints& c : children)
			c.control->dispatchContextChanged();
	}

	void ControlGroup::onUpdate(uint64_t time) {
		for (ControlWithConstraints& c : children)
			c.control->onUpdate(time);
	}

	void ControlGroup::onDraw(RenderGroup& group, const XMFLOAT2& parentPosition) {
		__super::onDraw(group, parentPosition);
		for (ControlWithConstraints& c : children) {
			if (!c.control->Visible)
				continue;
			c.control->draw(group, position + parentPosition);
		}
	}

	Control* ControlGroup::find(const AString& name) {
		if (this->Name && this->Name->operator==(name))
			return this;
		for (ControlWithConstraints& child : children) {
			Control* result = child.control->find(name);
			if (result)
				return result;
		}
		return nullptr;
	}

	Control* ControlGroup::find(const Ghurund::Core::Type& type) {
		if (Type == type)
			return this;
		for (ControlWithConstraints& child : children) {
			Control* result = child.control->find(type);
			if (result)
				return result;
		}
		return nullptr;
	}

	void ControlGroup::resolveConstraints(ConstraintGraph& graph, const Constraint& width, const Constraint& height) {
		__super::resolveConstraints(graph, width, height);
		for (ControlWithConstraints& c : children) {
			Control& control = *c.control.get();
			if (!control.Visible)
				continue;
			ConstraintSet& constraintSet = c.Constraints;
			if (constraintSet.Width.Constant && constraintSet.Height.Constant) {
				ConstraintGraph localGraph;
				control.resolveConstraints(localGraph, constraintSet.Width, constraintSet.Height);
				localGraph.sort();
				localGraph.evaluate();
			} else {
				control.resolveConstraints(graph, constraintSet.Width, constraintSet.Height);
			}
			constraintSet.resolve(control, graph);
		}
	}

	PartialConstraintSet ControlGroup::makeDefaultConstraints() const {
		if (layoutManager) {
			return layoutManager->makeDefaultConstraints();
		} else {
			return ConstraintSetInitializer{
				.width = makeIntrusive<ContentWidthConstraint>(),
				.height = makeIntrusive<ContentHeightConstraint>()
			};
		}
	}

#ifdef _DEBUG
	void ControlGroup::validate() const {
		__super::validate();
		for (ControlWithConstraints& c : children)
			c.control->validate();
	}

	String ControlGroup::printTree() const {
		String str = __super::printTree();
		size_t len = 4;
		for (auto it = children.begin(); it != children.end(); ++it) {
			ControlWithConstraints& c = *it;
			auto childStr = c.control->printTree().split(_T("\n"));
			for (size_t j = 0; j < len; j++)
				str.add(_T(" "));
			str.add(_T("\\-"));
			str.add(childStr[0]);
			for (size_t i = 1; i < childStr.Size; i++) {
				str.add(_T("\n"));
				for (size_t j = 0; j < len; j++)
					str.add(_T(" "));
				str.add(it != children.end() ? _T("| ") : _T("  "));
				str.add(childStr[i]);
			}
			str.add(_T("\n"));
		}
		return str;
	}
#endif
}