#include "DemoWindow.h"

#include "DemoApplication.h"

namespace Demo {
	DemoWindow::DemoWindow(DemoApplication& app, DxRenderer& renderer):DirectXWindow(app, DEMO_WINDOW_STYLE, renderer), app(app) {
		closed += DEFAULT_QUIT_APP_WINDOW_CLOSED_HANDLER;
		Title = _T("Demo 3D DirectX");
	}
}
