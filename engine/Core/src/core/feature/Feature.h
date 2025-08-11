#pragma once

#include "core/object/Initializable.h"
#include "core/object/RefCountedObject.h"

namespace Ghurund::Core {
	using namespace Ghurund::Core;

	class Feature:public RefCountedObject, public Initializable {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Feature::GET_TYPE();
#pragma endregion
	};
}