#include "DemoWindow.h"

#include "DemoApplication.h"
#include "core/Colors.h"
#include "core/window/DisplayManager.h"

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
		actionMapping.add(GamepadButton::A, closeWindow);

		moveWindow = makeIntrusive<MoveWindowAction>(*this, Application->Timer);
		actionMapping.add('w', moveWindow, [](float value) { return FloatPoint{ 0.0f, 1.0f }; });
		actionMapping.add('s', moveWindow, [](float value) { return FloatPoint{ 0.0f, -1.0f }; });
		actionMapping.add('a', moveWindow, [](float value) { return FloatPoint{ -1.0f, 0.0f }; });
		actionMapping.add('d', moveWindow, [](float value) { return FloatPoint{ 1.0f, 0.0f }; });
		actionMapping.add(GamepadStick::LEFT, moveWindow);
	}

	DemoWindow::~DemoWindow() {
		actionMapping.remove('w');
		actionMapping.clear();
	}

	bool DemoWindow::onGamepadButtonEvent(const GamepadButtonEventArgs& args) {
		bool result = __super::onGamepadButtonEvent(args);
		if (result)
			return true;

		if (actionMapping.dispatchGamepadButtonEvent(args))
			return true;

		return false;
	}

	bool DemoWindow::onGamepadStickEvent(const GamepadStickEventArgs& args) {
		bool result = __super::onGamepadStickEvent(args);
		if (result)
			return true;

		if (actionMapping.dispatchGamepadStickEvent(args))
			return true;

		if (args.Stick == GamepadStick::RIGHT) {
			auto p = args.Point;
			if (std::sqrtf(std::powf(p.x, 2.0f) + std::powf(p.y, 2.0f)) > 0.1f) {
				double dt = Application->Timer->FrameTime;
				auto v = args.Point * dt * 1000;
				Position = Position + IntPoint{ (int32_t)v.x, -(int32_t)v.y };
			}
		}
		return false;
	}

	bool DemoWindow::onKeyEvent(const KeyEventArgs& args) {
		bool result = __super::onKeyEvent(args);
		if (result)
			return true;

		if (actionMapping.dispatchKeyEvent(args))
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
