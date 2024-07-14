#pragma once

#include "Constraint.h"

namespace Ghurund::UI {
	class ContentSize {
	private:
		IntrusivePointer<Constraint> width, height;

	public:
		ContentSize(
			Constraint* width, Constraint* height
		):width(width), height(height) {
			width->addReference();
			height->addReference();
		}

		inline Constraint& getWidth() {
			return *width.get();
		}

		__declspec(property(get = getWidth)) Constraint& Width;

		inline Constraint& getHeight() {
			return *height.get();
		}

		__declspec(property(get = getHeight)) Constraint& Height;

		inline void resolve(Control& control, ConstraintGraph& graph) {
			width->resolve(control, graph);
			height->resolve(control, graph);
		}
	};
}