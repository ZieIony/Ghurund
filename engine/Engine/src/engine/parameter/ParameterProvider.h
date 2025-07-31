#pragma once

#include "core/Event.h"
#include "ParameterManager.h"

namespace Ghurund::Core {
	class ResourceManager;
	class DirectoryPath;
	class MemoryInputStream;
	class MemoryOutputStream;

	enum class LoadOption;
	enum class SaveOption;
}

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class ParameterProvider {
	protected:
		ParameterCollection parameters;
	
		void loadParameters(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);
		void saveParameters(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const;

	public:
		Event<ParameterProvider> onParametersChanged = *this;

		virtual ~ParameterProvider() = default;

		virtual void updateParameters() {}

		inline const ParameterCollection& getParameters() const {
			return parameters;
		}

		__declspec(property(get = getParameters)) ParameterCollection& Parameters;
	};
}