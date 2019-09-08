#pragma once

#include "resource/Resource.h"

namespace Ghurund {
	class Component:public Resource {
	private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Component);
        
        bool enabled = true;

	public:
		bool isEnabled() {
			return enabled;
		}

		void setEnabled(bool enabled) {
			this->enabled = enabled;
		}

		__declspec(property(get = isEnabled, put = setEnabled)) bool Enabled;

        inline static const Ghurund::Type& TYPE = TypeBuilder<Component>(NAMESPACE_NAME, CLASS_NAME)
            .withModifiers(TypeModifier::ABSTRACT)
            .withSupertype(Resource::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
	};
}