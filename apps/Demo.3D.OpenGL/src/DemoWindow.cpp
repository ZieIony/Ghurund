#include "DemoWindow.h"

#include "DemoApplication.h"

namespace Demo {
	DemoWindow::DemoWindow(DemoApplication& app, Renderer& renderer):OpenGLWindow(app, renderer), app(app) {
		Style = WindowStyle{
			.hasMinimizeButton = true,
			.hasMaximizeButton = true,
			.hasTitle = true,
			.borderStyle = WindowBorderStyle::RESIZE,
			.showOnTaskbar = true
		};
	}
	
	void DemoWindow::init() {
		__super::init();

	}
}
