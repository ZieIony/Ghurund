#pragma once

#pragma warning(push, 0)
#include <dxgi1_4.h>
#pragma warning(pop)

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	class DisplayMode {
	private:
		uint32_t width, height;
		float refreshRate;
		DXGI_FORMAT format;

	public:
		DisplayMode(DXGI_MODE_DESC mode):width(mode.Width), height(mode.Height), format(mode.Format) {
			refreshRate = (float)mode.RefreshRate.Numerator / mode.RefreshRate.Denominator;
		}

		DisplayMode(const DisplayMode& other):
			width(other.Width), height(other.Height), refreshRate(other.refreshRate), format(other.Format) {}

		DisplayMode(DisplayMode&& other) noexcept;

		uint32_t getWidth() const {
			return width;
		}

		__declspec(property(get = getWidth)) uint32_t Width;

		uint32_t getHeight() const {
			return height;
		}

		__declspec(property(get = getHeight)) uint32_t Height;

		float getRefreshRate() const {
			return refreshRate;
		}

		__declspec(property(get = getRefreshRate)) float RefreshRate;

		DXGI_FORMAT getFormat() const {
			return format;
		}

		__declspec(property(get = getFormat)) DXGI_FORMAT Format;
	};
}