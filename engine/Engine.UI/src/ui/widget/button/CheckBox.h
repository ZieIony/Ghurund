#pragma once

#include "CheckBoxRadio.h"

namespace Ghurund::UI {
	class CheckBox:public CheckBoxRadio<CheckBox> {
	protected:
		virtual void onLayoutChanged() override;

		virtual void onStateChanged() override;

		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		__declspec(property(get = getType)) const Ghurund::Core::Type& Type;
	};
}