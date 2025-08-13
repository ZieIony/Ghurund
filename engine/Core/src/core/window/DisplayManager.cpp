#include "ghcpch.h"
#include "DisplayManager.h"

#include <Windows.h>

namespace Ghurund::Core {
	List<DisplayDevice> DisplayManager::enumDisplayDevices() {
		size_t i = 0;
		List<DisplayDevice> devices;
		while (true) {
			DISPLAY_DEVICE device = {};
			device.cb = sizeof(DISPLAY_DEVICE);
			if (!EnumDisplayDevices(nullptr, i, &device, 0))
				break;
			if (device.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) {
				devices.add({
					device.DeviceName,
					device.DeviceString
				});
			}
			i++;
		}
		return devices;
	}

	DisplayMode DisplayManager::getDisplayMode(const String* deviceName) {
		size_t i = 0;
		const tchar* deviceNameStr = deviceName ? deviceName->Data : nullptr;
		DEVMODE devMode = {};
		devMode.dmSize = sizeof(DEVMODE);
		devMode.dmDriverExtra = 0;
		EnumDisplaySettings(deviceNameStr, ENUM_CURRENT_SETTINGS, &devMode);
		return {
			devMode.dmBitsPerPel,
			devMode.dmPelsWidth,
			devMode.dmPelsHeight,
			devMode.dmDisplayFlags,
			devMode.dmDisplayFrequency,
			{ devMode.dmPosition.x, devMode.dmPosition.y }
		};
	}

	List<DisplayMode> DisplayManager::enumDisplayModes(const String* deviceName) {
		size_t i = 0;
		List<DisplayMode> modes;
		const tchar* deviceNameStr = deviceName ? deviceName->Data : nullptr;
		while (true) {
			DEVMODE devMode = {};
			devMode.dmSize = sizeof(DEVMODE);
			devMode.dmDriverExtra = 0;
			if (!EnumDisplaySettings(deviceNameStr, i, &devMode))
				break;
			modes.add({
				devMode.dmBitsPerPel,
				devMode.dmPelsWidth,
				devMode.dmPelsHeight,
				devMode.dmDisplayFlags,
				devMode.dmDisplayFrequency,
				{ devMode.dmPosition.x, devMode.dmPosition.y }
			});
			i++;
		}
		return modes;
	}

	void DisplayManager::changeDisplayMode(const DisplayMode& mode) {
		DEVMODE devMode = {};
		devMode.dmSize = sizeof(DEVMODE);
		devMode.dmPosition = { mode.position.x, mode.position.y };
		devMode.dmBitsPerPel = mode.bitsPerPx;
		devMode.dmPelsWidth = mode.width;
		devMode.dmPelsHeight = mode.height;
		devMode.dmDisplayFlags = mode.flags;
		devMode.dmDisplayFrequency = mode.displayFrequency;
		devMode.dmFields =
			DM_POSITION | 
			DM_PELSWIDTH |
			DM_PELSHEIGHT |
			DM_BITSPERPEL |
			DM_DISPLAYFREQUENCY;
		auto result = ChangeDisplaySettings(&devMode, 0);
		if (result != DISP_CHANGE_SUCCESSFUL)
			throw CallFailedException();
	}

	void DisplayManager::revertDisplayMode() {
		ChangeDisplaySettings(nullptr, 0);
	}
}