#pragma once

#include "core/resource/Resource.h"

namespace Ghurund {
	class Component:public Resource {
	private:
        bool enabled = true;

	protected:
		static const Ghurund::Type& GET_TYPE();

	public:
		bool isEnabled() {
			return enabled;
		}

		void setEnabled(bool enabled) {
			this->enabled = enabled;
		}

		__declspec(property(get = isEnabled, put = setEnabled)) bool Enabled;

		inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
	};
}