#pragma once

#include "ControlParent.h"
#include "ui/constraint/ParentConstraint.h"

namespace Ghurund::Core {
	class ResourceManager;
}

namespace Ghurund::UI {
	class ControlContainerBase: public ControlParent {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = ControlContainerBase::GET_TYPE();
#pragma endregion

	private:
		bool previousReceiver = false;

	protected:
		Control* child = nullptr;
		ConstraintSet constraints = ConstraintSet({});

		ControlContainerBase() {}

		// previousReceiver should be false in cloned instances
		ControlContainerBase(const ControlContainerBase& other):ControlParent(other),
			child(other.child ? (Control*)other.child->clone() : nullptr) {}

		~ControlContainerBase() {
			if (child) {
				child->Parent = nullptr;
				child->release();
			}
		}

		virtual void onChildChanged() {}

	public:
		Event<ControlContainerBase> childChanged = *this;

		inline Control* getChild() {
			return child;
		}

		inline const Control* getChild() const {
			return child;
		}

		void setChild(Control* child);

		void setChild(Control* child, const ConstraintSet& set);

		__declspec(property(get = getChild, put = setChild)) Control* Child;

		virtual const ConstraintSet& getConstraints(const Control& control) const override;

		virtual ConstraintSet& getConstraints(Control& control) override;

		virtual void setConstraints(const Control& control, const ConstraintSet& set) override {
			if (&control != child)
				throw InvalidParamException("control is not the child of this container");
			constraints = set;
		}

		virtual bool focusNext() override;

		virtual bool focusPrevious() override;

		virtual bool focusUp() override;

		virtual bool focusDown() override;

		virtual bool focusLeft() override;

		virtual bool focusRight() override;

		virtual void dispatchStateChanged() override;

		virtual void dispatchThemeChanged() override;

		virtual void dispatchContextChanged() override;

		virtual void onLayout(float x, float y, float width, float height) override;

		virtual void onUpdate(const uint64_t time) override {
			if (child)
				child->onUpdate(time);
		}

		virtual void onDraw(ICanvas& canvas) override;

		virtual bool dispatchKeyEvent(const KeyEventArgs& event) override;

		virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override;

		virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;

		virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event) override;

		virtual void resolveConstraints(ConstraintGraph& graph, const Constraint& width, const Constraint& height) override;

#ifdef _DEBUG
		virtual void validate() const override;

		virtual String printTree() const;
#endif
	};
}