#include "DemoWindow.h"

#include "DemoApplication.h"

#include "core/Colors.h"
#include "core/window/DisplayManager.h"
#include <engine/directx/shader/DxShaderProvider.h>
#include <engine/graphics/material/MaterialProvider.h>
#include <engine/directx/texture/DxTextureProvider.h>
#include <engine/graphics/mesh/SpriteMeshData.h>
#include <engine/2d/entity/sprite/AnimatedSpriteComponent.h>
#include <engine/2d/physics/BoxComponent2D.h>
//#include "engine/2d/entity/CameraComponent2D.h"

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

		auto meshData = makeIntrusive<SpriteMeshData>();
		meshData->init();
		auto mesh = makeIntrusive<DxMesh>();
		mesh->init(meshData.ref(), graphicsFeature->MemoryManager);

		camera = makeIntrusive<Camera2D>();
		camera->ViewSize = { 8, 6 };
		camera->setPositionUp({ 0, 0 });

		world = makeShared<World2D>();
		scene = makeIntrusive<Scene2D>();

		auto boxShader = IntrusivePointer(app.ResourceManager.load<DxShader>(ResourceManager::ENGINE_LIB / FilePath(L"shaders/DirectX/2d/box.xml")));

		{
			auto boxMaterial = makeIntrusive<Material>(graphicsFeature->MemoryManager);
			boxMaterial->Shader = boxShader.get();
			auto captainBox = std::unique_ptr<BoxComponent2D>(ghnew BoxComponent2D(mesh.ref(), boxMaterial.ref()));
			captainBox->init(world.ref());
			captainBox->Type = BodyType::DYNAMIC;
			captainBox->IsRotationFixed = true;
			captainBox->Size = { 1.6, 1 };

			captain = makeIntrusive<Entity2D>();
			auto shader = IntrusivePointer(app.ResourceManager.load<DxShader>(ResourceManager::ENGINE_LIB / FilePath(L"shaders/DirectX/2d/sprite.xml")));
			auto material = makeIntrusive<Material>(graphicsFeature->MemoryManager);
			material->Shader = shader.get();
			auto captainSprite = OwnedNotNull<AnimatedSpriteComponent>(ghnew AnimatedSpriteComponent(mesh.ref(), material.ref()));
			captainSprite->Size = { 1.6, 1 };
			auto captainIdle1 = IntrusivePointer(app.ResourceManager.load<DxTexture>(ResourceManager::ENGINE_LIB / FilePath(L"test/images/Idle Sword 01.png")));
			auto captainIdle2 = IntrusivePointer(app.ResourceManager.load<DxTexture>(ResourceManager::ENGINE_LIB / FilePath(L"test/images/Idle Sword 02.png")));
			auto captainIdle3 = IntrusivePointer(app.ResourceManager.load<DxTexture>(ResourceManager::ENGINE_LIB / FilePath(L"test/images/Idle Sword 03.png")));
			auto captainIdle4 = IntrusivePointer(app.ResourceManager.load<DxTexture>(ResourceManager::ENGINE_LIB / FilePath(L"test/images/Idle Sword 04.png")));
			auto captainIdle5 = IntrusivePointer(app.ResourceManager.load<DxTexture>(ResourceManager::ENGINE_LIB / FilePath(L"test/images/Idle Sword 05.png")));
			captainSprite->Animation.addFrames({
				captainIdle1.get(),
				captainIdle2.get(),
				captainIdle3.get(),
				captainIdle4.get(),
				captainIdle5.get()
			}, 100);

			captainBox->Components.add(captainSprite.reset());
			captain->RootComponent = std::move(captainBox);
			scene->Entities.add(captain);
			captain->Position = { 0, 2 };
		}

		{
			auto groundMaterial = makeIntrusive<Material>(graphicsFeature->MemoryManager);
			groundMaterial->Shader = boxShader.get();

			ground = makeIntrusive<Entity2D>();
			auto groundBox = std::unique_ptr<BoxComponent2D>(ghnew BoxComponent2D(mesh.ref(), groundMaterial.ref()));
			groundBox->init(world.ref());
			groundBox->Type = BodyType::STATIC;
			groundBox->Position = { 0, 0 };
			groundBox->Size = { 5, 1 };

			ground->RootComponent = std::move(groundBox);
			scene->Entities.add(ground);
		}
	}

	bool DemoWindow::onKeyEvent(const KeyEventArgs& args) {
		//bool result = __super::onKeyEvent(args);
		///if (result)
		//	return true;

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
			BodyComponent2D& body = (BodyComponent2D&)captain->RootComponent;
			body.applyForce({ 0, 100 });
		} else if (args.KeyCode == 'a') {
			BodyComponent2D& body = (BodyComponent2D&)captain->RootComponent;
			body.applyForce({ -100, 0 });
		} else if (args.KeyCode == 'd') {
			BodyComponent2D& body = (BodyComponent2D&)captain->RootComponent;
			body.applyForce({ 100, 0 });
		}
		return true;
	}

	void DemoWindow::update() {
		__super::update();
		world->simulate(Timer.FrameTime);
		scene->update(Timer.TimeMs);
	}
	
	void DemoWindow::onPaint(RenderingContext& renderingContext) {
		RenderGroup _2dGroup(0, DrawOrder::BACK_TO_FRONT);
		_2dGroup.Camera = camera.get();
		scene->draw(_2dGroup);
		renderGroups.put(_2dGroup);

		renderingContext.clear(BackgroundColor);
		renderingContext.draw(renderGroups, ParameterManager);
	}
}
