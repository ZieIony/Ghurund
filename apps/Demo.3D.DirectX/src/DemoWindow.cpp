#include "DemoWindow.h"

#include "DemoApplication.h"

#include "core/Colors.h"
#include "core/window/DisplayManager.h"
#include <engine/directx/shader/DxShaderProvider.h>
#include <engine/graphics/material/MaterialProvider.h>
#include <engine/directx/texture/DxTextureProvider.h>
#include <engine/graphics/mesh/QuadMeshData.h>

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
		auto commandList = makeIntrusive<CommandList>();
		commandList->init(graphicsFeature->Graphics, graphicsFeature->Graphics.DirectQueue);

		DxShaderProvider shaderProvider(app.ResourceManager);
		DxTextureProvider textureProvider(app.ResourceManager);
		MaterialProvider materialProvider(shaderProvider, textureProvider, graphicsFeature->MemoryManager);

		IntrusivePointer<DxShader> shader = IntrusivePointer(app.ResourceManager.load<DxShader>(ResourceManager::ENGINE_LIB / FilePath(L"shaders/DirectX/2d/sprite.xml")));
		IntrusivePointer<Material> material = makeIntrusive<Material>(graphicsFeature->MemoryManager);
		material->Shader = shader.get();

		IntrusivePointer<QuadMeshData> meshData = makeIntrusive<QuadMeshData>();
		meshData->init();
		IntrusivePointer<DxMesh> mesh = makeIntrusive<DxMesh>();
		mesh->init(meshData.ref(), graphicsFeature->MemoryManager);

		scene.set(ghnew Scene());
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

	void DemoWindow::update(uint64_t time) {
		__super::update(time);
		scene->update(time);
	}
	
	void DemoWindow::onPaint(RenderingContext& renderingContext) {
		RenderGroup _2dGroup(0, DrawOrder::BACK_TO_FRONT);
		scene->draw(_2dGroup);
		renderGroups.put(_2dGroup);

		renderingContext.clear(BackgroundColor);
		renderingContext.draw(renderGroups, ParameterManager);
	}
}
