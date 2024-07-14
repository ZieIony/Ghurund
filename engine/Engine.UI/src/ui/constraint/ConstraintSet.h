#pragma once

#include "ui/constraint/ConstraintSetInitializer.h"

namespace tinyxml2 {
	class XMLElement;
}

namespace Ghurund::UI {
	class LayoutLoader;
	class ICanvas;

	// doesn't require all constraints to be set
	class PartialConstraintSet {
	public:
		IntrusivePointer<Constraint> left, width, right;
		IntrusivePointer<Constraint> top, height, bottom;

		PartialConstraintSet() {}

		PartialConstraintSet(const ConstraintSetInitializer& initializer)
			:left(initializer.left.get()), width(initializer.width.get()), right(initializer.right.get()),
			top(initializer.top.get()), height(initializer.height.get()), bottom(initializer.bottom.get()) {}

		void load(const Type& controlType, LayoutLoader& loader, const tinyxml2::XMLElement& xml);

		void merge(const PartialConstraintSet& other);

		inline bool operator==(const PartialConstraintSet& other) const {
			return left == other.left && width == other.width && right == other.right &&
				top == other.top && height == other.height && bottom == other.bottom;
		}
	};

	class ConstraintSet {
	private:
		IntrusivePointer<Constraint> left, width, right;
		IntrusivePointer<Constraint> top, height, bottom;

	public:
		ConstraintSet(const PartialConstraintSet& set);

		ConstraintSet(
			Constraint* left, Constraint* width, Constraint* right,
			Constraint* top, Constraint* height, Constraint* bottom
		):left(left), width(width), right(right), top(top), height(height), bottom(bottom) {
			left->addReference();
			width->addReference();
			right->addReference();
			top->addReference();
			height->addReference();
			bottom->addReference();
		}

		inline Constraint& getLeft() {
			return *left.get();
		}

		__declspec(property(get = getLeft)) Constraint& Left;

		inline Constraint& getRight() {
			return *right.get();
		}

		__declspec(property(get = getRight)) Constraint& Right;

		inline const Constraint& getWidth() const {
			return *width.get();
		}

		inline Constraint& getWidth() {
			return *width.get();
		}

		__declspec(property(get = getWidth)) Constraint& Width;

		inline Constraint& getTop() {
			return *top.get();
		}

		__declspec(property(get = getTop)) Constraint& Top;

		inline Constraint& getBottom() {
			return *bottom.get();
		}

		__declspec(property(get = getBottom)) Constraint& Bottom;

		inline const Constraint& getHeight() const {
			return *height.get();
		}

		inline Constraint& getHeight() {
			return *height.get();
		}

		__declspec(property(get = getHeight)) Constraint& Height;

		void resolve(Control& control, ConstraintGraph& graph);

		inline bool operator==(const ConstraintSet& other) const {
			return left == other.left && width == other.width && right == other.right &&
				top == other.top && height == other.height && bottom == other.bottom;
		}

#ifdef _DEBUG
		void draw(ICanvas& canvas);
#endif
	};

	inline ConstraintSet makeConstraints(const ConstraintSetInitializer& initializer) {
		return ConstraintSet(initializer);
	}
}