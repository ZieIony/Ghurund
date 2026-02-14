#pragma once

#include "core/resource/Resource.h"
#include "core/math/Size.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	enum class TextureType {
		COLOR, OTHER
	};

	class ITexture:public Resource {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = ITexture::GET_TYPE();
#pragma endregion

	public:
		virtual const IntSize& getSize() const = 0;

		__declspec(property(get = getSize)) const IntSize& Size;
	};
}