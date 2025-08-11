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
		BackgroundColor = &Colors::LIGHT_GRAY;
	}
}
