#pragma once

#include "parameter/Parameter.h"
#include "core/string/String.h"
#include "core/Object.h"
#include "ParameterCollection.h"

namespace Ghurund::Core {
	class ResourceManager;
}

namespace Ghurund::Core::DirectX {
	class Graphics;
	class CommandList;
}

namespace Ghurund {
	using namespace Ghurund::Core;
	using namespace Ghurund::Core::DirectX;

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

	public:
		ParameterManager();

		void initDefaultTextures(ResourceManager& manager, Graphics& graphics, CommandList& commandList);

		ParameterCollection& getParameters() {
			return parameters;
		}

		__declspec(property(get = getParameters)) ParameterCollection& Parameters;
	};
}