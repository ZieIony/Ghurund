#include "DemoWindow.h"

#include "DemoApplication.h"

#include "core/Colors.h"
#include "core/io/File.h"
#include "core/math/Matrix.h"
#include "core/window/DisplayManager.h"
#include "engine/directx/mesh/DxMesh.h"
#include "engine/graphics/mesh/QuadMeshData.h"
#include "ui/directx/shader/DxUIShaderProvider.h"
#include "ui/directx/text/DxTextMeshFactory.h"
#include "ui/material/ControlMaterialParameters.h"
#include "ui/material/UIMaterialProvider.h"

namespace Demo {
	using namespace Ghurund::UI::DirectX;

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

		DxUIShaderProvider shaderProvider(app.ResourceManager);
		UIMaterialProvider materialProvider(shaderProvider, graphicsFeature->MemoryManager);

		camera = makeIntrusive<Camera>();
		camera->setPositionTargetUp({ 10,10,-10 }, { 0,0,0 });
		camera->rebuild();
		camera->updateParameters();
		ParameterManager.Parameters.putAll(camera->Parameters);

		auto world = makeIntrusive<MatrixParameter>("world", MATRIX_IDENTITY);
		ParameterManager.Parameters.put(world.get());

		auto textStylePath = FilePath(L"resources/textStyles/lato_regular_12.bin");
		if (File(textStylePath).exists()) {
			textStyle.set(app.ResourceManager.load<TextStyle>(textStylePath, DirectoryPath(), TextStyle::FORMAT_BIN));
		} else {
			auto font = IntrusivePointer<Font>(app.ResourceManager.load<Font>(FilePath(L"resources/fonts/lato_regular.ttf")));
			textStyle.set(ghnew TextStyle());
			textStyle->init(font.ref(), 12);
			auto atlasPath = FilePath(L"resources/textStyles/lato_regular_12.png");
			app.ResourceManager.save(*textStyle->Atlas->Image, atlasPath, DirectoryPath(), Image::FORMAT_PNG);
			app.ResourceManager.save(textStyle.ref(), textStylePath, DirectoryPath(), TextStyle::FORMAT_BIN);
		}

		DxTextMeshFactory textMeshfactory(graphicsFeature->MemoryManager);
		DxTextureFactory textureFactory(graphicsFeature->Graphics, commandList.ref());

		RenderGroup uiGroup(0, DrawOrder::BACK_TO_FRONT);
		{
			basicMaterial = IntrusivePointer<Material>(materialProvider.makeText());
			colorTexture = makeIntrusive<DxTexture>();
			colorTexture->init(graphicsFeature->Graphics, commandList.ref(), *textStyle->Atlas->Image);
			colorTextureParameter = (TextureParameter*)basicMaterial->Parameters.get("colorTexture");
			colorTextureParameter->Value = colorTexture.get();

			textLayout.Document = makeIntrusive<TextDocument>(
				L"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.",
				textStyle.ref(),
				Colors::BLACK
			).get();
			textLayout.PreferredSize = { 200, 200 };
			textLayout.refresh();
			textLayout.initMeshes(textMeshfactory, textureFactory, basicMaterial.get());
		}
		{
			auto mesh = ghnew DxMesh();
			auto meshData = makeIntrusive<QuadMeshData>();
			meshData->init();
			shadowMesh = IntrusivePointer<Resource>(mesh);
			mesh->init(meshData.ref(), graphicsFeature->MemoryManager);

			controlMaterial = IntrusivePointer<Material>(materialProvider.makeControl());
			ControlMaterialParameters parameters(controlMaterial.ref());
			parameters.Size = { (float)textLayout.Size.Width, (float)textLayout.Size.Height };
			parameters.BackgroundColor = Colors::WHITE;

		}
		uiGroup.objects.add(DrawPacket{ shadowMesh, controlMaterial });
		textLayout.draw(uiGroup, { 50, 100 });
		renderGroups.put(uiGroup);
	}

	bool DemoWindow::onMouseButtonEvent(const MouseButtonEventArgs& args) {
		if (args.Action == MouseButtonAction::PRESSED) {
			//backgroundColorParameter->Value = Colors::GRAY.toVector();
			//borderColorParameter->Value = Colors::LIGHT_GRAY.toVector();
		} else if (args.Action == MouseButtonAction::RELEASED) {
			//backgroundColorParameter->Value = Colors::LIGHT_GRAY.toVector();
			//borderColorParameter->Value = Colors::WHITE.toVector();
		}
		return __super::onMouseButtonEvent(args);
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
		renderingContext.clear(BackgroundColor);
		renderingContext.draw(renderGroups, ParameterManager);
	}
}
