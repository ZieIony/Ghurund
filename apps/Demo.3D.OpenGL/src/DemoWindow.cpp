#include "DemoWindow.h"

#include "DemoApplication.h"
#include "core/Colors.h"
#include "core/window/DisplayManager.h"
#include "CloseWindowAction.h"
#include "MoveWindowAction.h"

namespace Demo {
	DemoWindow::DemoWindow(
		NotNull<DemoApplication> app,
		NotNull<Ghurund::Engine::OpenGL::OglRenderer> renderer
	):Ghurund::Engine::GameWindow(&app), app(*app) {
		closed += DEFAULT_QUIT_APP_WINDOW_CLOSED_HANDLER;
		Title = _T("Demo 3D OpenGL");
		Renderer = &renderer;
		BackgroundColor = &Colors::LIGHT_CORAL;

		closeWindow = makeIntrusive<CloseWindowAction>(*this);
		ActionMapping->add(0, GamepadButton::A, closeWindow.get());
		ActionMapping->add(0, GamepadTrigger::LEFT, NotNull<GameAction<bool>>(closeWindow.get()), [](float value) { return value > 0.5f; });

		moveWindow = makeIntrusive<MoveWindowAction>(*this, Application->Timer);
		ActionMapping->add<FloatPoint>('w', moveWindow.get(), [](float value) { return FloatPoint{ 0.0f, 1.0f }; });
		ActionMapping->add<FloatPoint>('s', moveWindow.get(), [](float value) { return FloatPoint{ 0.0f, -1.0f }; });
		ActionMapping->add<FloatPoint>('a', moveWindow.get(), [](float value) { return FloatPoint{ -1.0f, 0.0f }; });
		ActionMapping->add<FloatPoint>('d', moveWindow.get(), [](float value) { return FloatPoint{ 1.0f, 0.0f }; });
		ActionMapping->add(0, GamepadStick::LEFT, moveWindow.get());
		ActionMapping->add(1, GamepadStick::RIGHT, moveWindow.get());
	}

	DemoWindow::~DemoWindow() {
		ActionMapping->remove('w');
		ActionMapping->clear();
	}

	bool DemoWindow::onKeyEvent(const KeyEventArgs& args) {
		bool result = __super::onKeyEvent(args);
		if (result)
			return true;

		if (args.KeyCode == VK_SPACE) {
			//auto devices = DisplayManager::enumDisplayDevices();
			//auto modes = DisplayManager::enumDisplayModes(&devices[0].name);
			auto currentMode = DisplayManager::getDisplayMode();
			Ghurund::Core::DisplayMode copy = currentMode;
			copy.size = { 800, 600 };
			DisplayManager::changeDisplayMode(copy);
		} else if (args.KeyCode == VK_BACK) {
			DisplayManager::revertDisplayMode();
		} else if (args.KeyCode == 'f') {
			Style = WindowStyle::FULLSCREEN;
			auto currentMode = DisplayManager::getDisplayMode();
			ClientSize = currentMode.size;
			Position = { 0, 0 };
		} else if (args.KeyCode == 'w') {
			Style = DEFAULT_WINDOW_STYLE;
			ClientSize = { 800, 600 };
		}
		return true;
	}

}
