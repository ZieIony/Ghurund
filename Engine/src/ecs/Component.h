#pragma once

#include "resource/Resource.h"

namespace Ghurund {
	class Component:public Resource {
	private:
        bool enabled = true;

		static const Ghurund::Type& GET_TYPE() {
			static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Component))
				.withModifiers(TypeModifier::ABSTRACT)
				.withSupertype(__super::TYPE);

			return TYPE;
		}

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