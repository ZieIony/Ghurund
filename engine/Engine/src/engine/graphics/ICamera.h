#pragma once

#include "core/object/RefCountedObject.h"

namespace Ghurund::Engine {
	class ParameterManager;

	class ICamera:public Ghurund::Core::RefCountedObject {
	public:
		virtual void apply(ParameterManager& parameterManager) = 0;
	};
}
