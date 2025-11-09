#include "DemoWindow.h"

#include "DemoApplication.h"
#include "core/Colors.h"
#include "core/window/DisplayManager.h"

#include <engine/graphics/mesh/QuadMesh.h>
#include <engine/directx/mesh/DxMesh.h>
#include <engine/directx/texture/TextureProvider.h>
#include <engine/directx/shader/ShaderProvider.h>
#include <engine/directx/material/MaterialProvider.h>

namespace Demo {
	DemoWindow::DemoWindow(
		DemoApplication& app,
		Ghurund::Engine::DirectX::DxRenderer& renderer
	):GameWindow(app), app(app) {
		closed += DEFAULT_QUIT_APP_WINDOW_CLOSED_HANDLER;
		Title = _T("Demo 3D DirectX");

		Renderer = &renderer;
		BackgroundColor = &Colors::LIGHT_SKY_BLUE;

		auto meshData = makeIntrusive<QuadMesh>();
		meshData->init();
		mesh = makeIntrusive<DxMesh>();
		DxGraphics* graphics = app.Features.get<DxGraphics>();
		auto commandList = makeIntrusive<CommandList>();
		commandList->init(*graphics, graphics->DirectQueue);

		mesh->init(meshData.ref(), *graphics, *commandList.get());

		TextureProvider textureProvider(*graphics, *commandList.get(), app.ResourceManager);
		ShaderProvider shaderProvider(app.ResourceManager);
		MaterialProvider materialProvider(ParameterManager, shaderProvider, textureProvider);

		camera = makeIntrusive<Camera>();
		camera->setPositionTargetUp({ 10,10,-10 }, { 0,0,0 });
		camera->rebuild();
		camera->updateParameters();
		ParameterManager.Parameters.putAll(camera->Parameters);

		auto world = makeIntrusive<MatrixParameter>("world");
		XMFLOAT4X4 identity;
		XMStoreFloat4x4(&identity, XMMatrixIdentity());
		world->setValue(identity);
		ParameterManager.Parameters.put(world.get());

		basicMaterial = IntrusivePointer<Material>(materialProvider.makeUi());

		sizeParameter.set((Float2Parameter*)basicMaterial->Parameters.get("size"));
		backgroundColorParameter.set((Float4Parameter*)basicMaterial->Parameters.get("backgroundColor"));
		borderColorParameter.set((Float4Parameter*)basicMaterial->Parameters.get("borderColor"));
	}

	bool DemoWindow::onMouseButtonEvent(const MouseButtonEventArgs& args) {
		if (args.Action == MouseButtonAction::PRESSED) {
			backgroundColorParameter->Value = Colors::GRAY.toVector();
			borderColorParameter->Value = Colors::LIGHT_GRAY.toVector();
		} else if (args.Action == MouseButtonAction::RELEASED) {
			backgroundColorParameter->Value = Colors::LIGHT_GRAY.toVector();
			borderColorParameter->Value = Colors::WHITE.toVector();
		}
		return true;
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
	
	void DemoWindow::onPaint(RenderingContext& renderingContext) {
		auto& dxContext = (DxRenderingContext&)renderingContext;
		auto commandList = dxContext.SwapChain.CurrentFrame.CommandList;
		DxGraphics* graphics = app.Features.get<DxGraphics>();
		basicMaterial->set(*graphics, *commandList, ParameterManager);
		mesh->draw(*commandList);
	}
}
