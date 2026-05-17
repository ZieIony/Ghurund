#include "DemoWindow.h"

#include "DemoApplication.h"

#include "core/Colors.h"
#include "core/window/DisplayManager.h"
#include <engine/directx/shader/DxShaderProvider.h>
#include <engine/graphics/material/MaterialProvider.h>
#include <engine/directx/texture/DxTextureProvider.h>

namespace Demo {
	DemoWindow::DemoWindow(
		DemoApplication& app,
		Ghurund::Engine::DirectX::DxRenderer& renderer
	):GameWindow(app), app(app) {
		closed += DEFAULT_QUIT_APP_WINDOW_CLOSED_HANDLER;
		Title = _T("Demo 3D DirectX");

		Renderer = &renderer;
		BackgroundColor = &Colors::LIGHT_SKY_BLUE;

		DxGraphicsFeature* graphicsFeature = app.Features.get<DxGraphicsFeature>();

		DxShaderProvider shaderProvider(app.ResourceManager);
		DxTextureProvider textureProvider(app.ResourceManager);
		MaterialProvider materialProvider(shaderProvider, textureProvider, graphicsFeature->MemoryManager);

		init();
	}

	void DemoWindow::init() {
		DxGraphicsFeature* graphicsFeature = app.Features.get<DxGraphicsFeature>();

		context3d = makeShared<DxGraphics3DContext>(graphicsFeature->MemoryManager, app.ResourceManager);

		world = ghnew World3D(app, context3d.ref());
		world->init();

		app.CoroutineScheduler.launch(initScene());
	}

	CoroutineTask<void> DemoWindow::initScene() {
		co_return;
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
		} else if (args.KeyCode == VK_ESCAPE) {
			app.quit();
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

	void DemoWindow::update() {
		__super::update();

		auto text = std::format(_T("fps: {:.2f}"), Timer.FramesPerSecond);
		Title = String(text.c_str());
	}

	void DemoWindow::onPaint(RenderingContext& renderingContext) {
		RenderGroup _3dGroup(DrawGroup(0, DrawOrder::FRONT_TO_BACK));
		_3dGroup.Camera = world->Scene.Camera;
		world->draw(_3dGroup);
		renderGroups.put(_3dGroup);

		renderingContext.clear(BackgroundColor);
		renderingContext.draw(renderGroups, ParameterManager);
	}
}
