#pragma once

#include "core/object/Object.h"
#include "ParameterCollection.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class ParameterManager: public Object {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = ParameterManager::GET_TYPE();
#pragma endregion

	private:
		ParameterCollection parameters;

		ParameterManager& operator=(const ParameterManager& other) = delete;

	public:
		ParameterManager();

		ParameterCollection& getParameters() {
			return parameters;
		}

		__declspec(property(get = getParameters)) ParameterCollection& Parameters;
	};
}
