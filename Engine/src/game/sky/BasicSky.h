#pragma once

#include "Sky.h"
#include "graphics/Materials.h"

namespace Ghurund {
	class BasicSky :public Sky {
	public:
		void init(ResourceContext& context, Ghurund::Camera* camera) {
			__super::init(context, camera);

			material = Materials::makeBasicSky(context);

			initParameters(context.ParameterManager);
			Valid = true;
		}
	};
}