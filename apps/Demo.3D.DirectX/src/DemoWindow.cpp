#include "DemoWindow.h"

#include "DemoApplication.h"
#include "core/Colors.h"
#include "core/window/DisplayManager.h"

#include <engine/graphics/mesh/CubeMesh.h>
#include <engine/directx/mesh/DxMesh.h>
#include <engine/directx/texture/TextureProvider.h>
#include <engine/directx/shader/ShaderProvider.h>
#include <engine/directx/material/MaterialProvider.h>

namespace Demo {
	DemoWindow::DemoWindow(
		NotNull<DemoApplication> app,
		NotNull<Ghurund::Engine::DirectX::DxRenderer> renderer,
		NotNull<ParameterManager> parameterManager
	):GameWindow(&app), app(&app), parameterManager(&parameterManager) {
		closed += DEFAULT_QUIT_APP_WINDOW_CLOSED_HANDLER;
		Title = _T("Demo 3D DirectX");

		Renderer = &renderer;
		BackgroundColor = &Colors::LIGHT_SKY_BLUE;

		auto meshData = makeIntrusive<CubeMesh>();
		meshData->init();
		mesh = makeIntrusive<DxMesh>();
		DxGraphics* graphics = app->Features->get<DxGraphics>();
		auto commandList = makeIntrusive<CommandList>();
		commandList->init(graphics, graphics->DirectQueue);

		mesh->init(meshData.ref(), *graphics, commandList.get());

		TextureProvider textureProvider(graphics, commandList.get(), app->ResourceManager);
		ShaderProvider shaderProvider(app->ResourceManager);
		MaterialProvider materialProvider(parameterManager, shaderProvider, textureProvider);

		basicMaterial = IntrusivePointer<Material>(materialProvider.makeBasic());

		camera = makeIntrusive<Camera>();
		camera->rebuild();
		camera->updateParameters();
		parameterManager->Parameters.putAll(camera->Parameters);
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
			close();
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
	
	void DemoWindow::onPaint(NotNull<RenderingContext> renderingContext) {
		auto dxContext = (DxRenderingContext*)&renderingContext;
		auto commandList = dxContext->SwapChain.CurrentFrame.CommandList;
		DxGraphics* graphics = app->Features->get<DxGraphics>();
		basicMaterial->set(*graphics, *commandList);
		mesh->draw(*commandList);
	}
}
