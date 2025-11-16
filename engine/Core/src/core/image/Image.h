#pragma once

#pragma comment(lib, "Shlwapi.lib")

#include "core/reflection/Type.h"
#include "core/resource/Resource.h"

#pragma warning(push, 0)
#include <dxgi1_4.h>
#pragma warning(pop)

#include <wincodec.h>

namespace Ghurund::Core {
	template<>
	const Type& getType<DXGI_FORMAT>();

	class Image:public Resource {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Image::GET_TYPE();
#pragma endregion

	private:
		DXGI_FORMAT format = {};
		IntSize size;
		uint32_t pixelSize = 0, rowPitch = 0;
		Buffer imageData;

	public:
		void init(const Buffer& data, const IntSize& size, DXGI_FORMAT format);

		virtual void invalidate() override {
			format = {};
			size = {};
			pixelSize = 0, rowPitch = 0;
			imageData.resize(0);
		}

		virtual bool isValid() const override {
			return __super::isValid() && imageData.Size != 0;
		}

		Buffer& getData() {
			return imageData;
		}

		__declspec(property(get = getData)) Ghurund::Core::Buffer& Data;

		DXGI_FORMAT getFormat() {
			return format;
		}

		__declspec(property(get = getFormat)) DXGI_FORMAT Format;

		const IntSize& getSize() const {
			return size;
		}

		__declspec(property(get = getSize)) const IntSize& Size;

		uint32_t getPixelSize() {
			return pixelSize;
		}

		__declspec(property(get = getPixelSize)) uint32_t PixelSize;

		uint32_t getRowPitch() {
			return rowPitch;
		}

		__declspec(property(get = getRowPitch)) uint32_t RowPitch;

#pragma region formats
	protected:
		virtual const Array<ResourceFormat>& getFormatsImpl() const override {
			return Image::FORMATS;
		}

	public:
		static const inline ResourceFormat FORMAT_JPG = ResourceFormat(L"jpg", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_JPEG = ResourceFormat(L"jpeg", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_PNG = ResourceFormat(L"png", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);

		inline static const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& FORMATS = { FORMAT_JPG, FORMAT_JPEG, FORMAT_PNG };
#pragma endregion
	};
}