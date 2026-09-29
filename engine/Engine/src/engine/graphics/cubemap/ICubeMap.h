#pragma once

#include "core/resource/Resource.h"
#include "core/math/Size.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class ICubeMap:public Resource {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = ICubeMap::GET_TYPE();
#pragma endregion

	protected:
		IntSize size;

	public:
		inline const IntSize& getSize() const {
			return size;
		}

		__declspec(property(get = getSize)) const IntSize& Size;
	};
}
