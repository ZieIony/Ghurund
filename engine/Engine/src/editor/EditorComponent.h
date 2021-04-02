#pragma once

#include "ecs/Component.h"

namespace Ghurund {
	class EditorComponent:public Component {
	private:
		bool editMode = false;

	public:
		inline void setInEditMode(bool inEditMode) {
			this->editMode = inEditMode;
		}

		inline bool isInEditMode()const {
			return editMode;
		}

		__declspec(property(get = isInEditMode, put = setInEditMode)) bool InEditMode;

	};
}