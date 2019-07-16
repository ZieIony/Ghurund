#pragma once

#include "resource/Resource.h"

namespace Ghurund {
	class Component:public Resource {
	private:
		bool enabled = true;

	public:
		bool isEnabled() {
			return enabled;
		}

		void setEnabled(bool enabled) {
			this->enabled = enabled;
		}

		__declspec(property(get = isEnabled, put = setEnabled)) bool Enabled;
	};
}