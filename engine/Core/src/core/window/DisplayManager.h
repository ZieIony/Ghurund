#pragma once

#include <core/collection/List.h>
#include <core/string/String.h>

namespace Ghurund::Core {
	struct DisplayMode {
		uint32_t bitsPerPx;
		IntSize size;
		uint32_t flags;
		uint32_t displayFrequency;
		IntPoint position;
	};

	struct DisplayDevice {
		String name;
		String userFriendlyName;
	};

	class DisplayManager {
	private:
		DisplayManager() = delete;

	public:
		static List<DisplayDevice> enumDisplayDevices();

		static DisplayMode getDisplayMode(const String* deviceName = nullptr);

		static List<DisplayMode> enumDisplayModes(const String* deviceName = nullptr);

		static void changeDisplayMode(const DisplayMode& mode);

		static void revertDisplayMode();
	};
}