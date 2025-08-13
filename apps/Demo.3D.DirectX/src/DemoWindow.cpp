#include "DemoWindow.h"

#include "DemoApplication.h"
#include "core/Colors.h"

namespace Demo {
	DemoWindow::DemoWindow(
		NotNull<DemoApplication> app,
		NotNull<Ghurund::Engine::DirectX::DxRenderer> renderer
	):GameWindow(&app), app(*app) {
		closed += DEFAULT_QUIT_APP_WINDOW_CLOSED_HANDLER;
		Title = _T("Demo 3D DirectX");

		Renderer = &renderer;
		BackgroundColor = &Colors::LIGHT_SKY_BLUE;
	}
	
	bool DemoWindow::onKeyEvent(const KeyEventArgs& args) {
		bool result = __super::onKeyEvent(args);
		if (result)
			return true;

		if (args.Key == VK_SPACE) {
			//auto devices = DisplayManager::enumDisplayDevices();
			//auto modes = DisplayManager::enumDisplayModes(&devices[0].name);
			auto currentMode = DisplayManager::getDisplayMode();
			Ghurund::Core::DisplayMode copy = currentMode;
			copy.width = 800;
			copy.height = 600;
			DisplayManager::changeDisplayMode(copy);
		} else if (args.Key == VK_ESCAPE) {
			DisplayManager::revertDisplayMode();
		}
		return true;
	}
}
