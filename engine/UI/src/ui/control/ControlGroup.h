#pragma once

#include "ControlParent.h"
#include "ListControlProvider.h"
#include "ControlCollection.h"
#include "ui/layout/LayoutManager.h"

namespace Ghurund::Core {
	class ResourceManager;
}

namespace Ghurund::UI {
	class LayoutManager;

	class ControlGroup:public ControlParent {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = ControlGroup::GET_TYPE();
#pragma endregion

	private:
		ControlCollection children;
		Control* previousReceiver = nullptr;

	protected:
		LayoutManager* layoutManager = nullptr;

		virtual void loadInternal(LayoutLoader& loader, const DirectoryPath& workingDir, const XMLElement& xml) override;

		virtual void onLayout(float x, float y, float width, float height) override;

		virtual bool onKeyEvent(const KeyEventArgs& event) override;

		virtual bool onMouseButtonEvent(const MouseButtonEventArgs& event) override;

		virtual bool onMouseMotionEvent(const MouseMotionEventArgs& event) override;

		virtual bool onMouseWheelEvent(const MouseWheelEventArgs& event) override;

	public:
		ControlGroup();

		~ControlGroup();

		inline ControlCollection& getChildren() {
			return children;
		}

		inline const ControlCollection& getChildren() const {
			return children;
		}

		inline void setChildren(const std::initializer_list<Control*>& controls) {
			children.clear();
			children.addAll(controls);
		}

		__declspec(property(get = getChildren, put = setChildren)) ControlCollection& Children;

		inline LayoutManager* getLayoutManager() {
			return layoutManager;
		}

		inline void setLayoutManager(std::unique_ptr<LayoutManager> layoutManager) {
			delete this->layoutManager;
			this->layoutManager = layoutManager.release();
			//if (this->LayoutManager && childrenProvider)
			  //  this->layoutManager->setGroup(*this, *childrenProvider);
		}

		__declspec(property(get = getLayoutManager, put = setLayoutManager)) LayoutManager* LayoutManager;

		virtual bool focusNext() override;

		virtual bool focusPrevious() override;

		virtual bool focusUp() override;

		virtual bool focusDown() override;

		virtual bool focusLeft() override;

		virtual bool focusRight() override;

		virtual void dispatchStateChanged() override;

		virtual void dispatchThemeChanged() override;

		virtual void dispatchContextChanged() override;

		virtual void onUpdate(uint64_t time) override;

		virtual void onDraw(RenderGroup& group, const XMFLOAT2& parentPosition) override;

		using Control::find;

		virtual Control* find(const Ghurund::Core::AString& name) override;

		virtual Control* find(const Ghurund::Core::Type& type) override;

		virtual const ConstraintSet& getConstraints(const Control& child) const override {
			size_t index = children.find(&child);
			if (index == children.Size)
				throw InvalidParamException("control is not the child of this container");
			return children[index].Constraints;
		}

		virtual ConstraintSet& getConstraints(Control& child) override {
			size_t index = children.find(&child);
			if (index == children.Size)
				throw InvalidParamException("control is not the child of this container");
			return children[index].Constraints;
		}


		virtual void setConstraints(const Control& child, const ConstraintSet& set) override {
			size_t index = children.find(&child);
			if (index == children.Size)
				throw InvalidParamException("control is not the child of this container");
			children[index].Constraints = set;
		}

		virtual void resolveConstraints(ConstraintGraph& graph, const Constraint& width, const Constraint& height) override;

		virtual PartialConstraintSet makeDefaultConstraints() const override;

#ifdef _DEBUG
		virtual void validate() const override;

		virtual String printTree() const;
#endif
	};
}