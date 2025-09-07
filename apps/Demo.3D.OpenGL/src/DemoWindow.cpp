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

		actionMapping.add(GamepadButton::A, SharedPointer<GameAction>(ghnew CloseWindowAction(*this)));
	}

	bool DemoWindow::onGamepadButtonEvent(const GamepadButtonEventArgs& args) {
		bool result = __super::onGamepadButtonEvent(args);
		if (result)
			return true;

		if (actionMapping.onGamepadButtonEvent(args))
			return true;

		return false;
	}

	bool DemoWindow::onGamepadStickEvent(const GamepadStickEventArgs& args) {
		bool result = __super::onGamepadStickEvent(args);
		if (result)
			return true;

		if (args.Stick == GamepadStick::LEFT) {
			auto p = args.Point;
			if (std::sqrtf(std::powf(p.x, 2.0f) + std::powf(p.y, 2.0f)) > 0.1f) {
				double dt = Application->Timer->FrameTime;
				auto v = args.Point * dt * 1000;
				Position = Position + IntPoint{ (int32_t)v.x, -(int32_t)v.y };
			}
		}

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
