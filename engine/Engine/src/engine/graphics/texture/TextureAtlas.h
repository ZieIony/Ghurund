#pragma once

#include "ITexture.h"

#include "core/math/Size.h"
#include "core/object/IntrusivePointer.h"
#include "core/object/NotNull.h"
#include "core/resource/Resource.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;
	using namespace ::DirectX;

	class TextureAtlas:public Resource {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<TextureAtlas>()
				.withSupertype(__super::GET_TYPE());

			return TYPE;
		}

		inline static const Ghurund::Core::Type& TYPE = TextureAtlas::GET_TYPE();
#pragma endregion

	private:
		ITexture* texture = nullptr;
		List<XMFLOAT4> coordinates;

	public:
		~TextureAtlas() {
			if (texture)
				texture->release();
		}

		/**
		* Init simply with the final atlas texture and the size of each texture
		**/
		void init(NotNull<ITexture> texture, IntSize singleSize);

		void init(NotNull<ITexture> texture, XMUINT2 gridSize);

		inline XMFLOAT4 get(size_t index) const {
			return coordinates[index];
		}

		inline size_t getSize() const {
			return coordinates.Size;
		}

		__declspec(property(get = getSize)) size_t Size;

		inline ITexture* get() const {
			return texture;
		}

#pragma region formats
	protected:
		virtual const Array<ResourceFormat>& getFormatsImpl() const override {
			return TextureAtlas::FORMATS;
		}

	public:
		static const inline ResourceFormat FORMAT_XML = ResourceFormat(L"xml", ResourceFormatOptions::CAN_LOAD | ResourceFormatOptions::CAN_SAVE);

		inline static const Array<ResourceFormat>& FORMATS = { FORMAT_XML };

		static const inline uint32_t VERSION = 1;
#pragma endregion
	};
}