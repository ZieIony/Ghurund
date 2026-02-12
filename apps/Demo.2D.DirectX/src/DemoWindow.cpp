#include "DemoWindow.h"

#include "DemoApplication.h"

#include "core/Colors.h"
#include "core/window/DisplayManager.h"
#include <engine/graphics/mesh/SpriteMeshData.h>
#include <engine/2d/graphics/sprite/AnimatedSpriteComponent.h>
#include <engine/2d/physics/component/BoxComponent2D.h>
//#include "engine/2d/entity/CameraComponent2D.h"
#include "ui/theme/LightTheme.h"
#include <engine/2d/physics/component/CapsuleComponent2D.h>
#include <engine/2d/physics/component/SegmentComponent2D.h>

namespace Demo {
	DemoWindow::DemoWindow(
		DemoApplication& app,
		Ghurund::Engine::DirectX::DxRenderer& renderer
	):GameWindow(app), app(app) {
		closed += DEFAULT_QUIT_APP_WINDOW_CLOSED_HANDLER;
		Title = _T("Demo 3D DirectX");

		Renderer = &renderer;
		BackgroundColor = &Colors::BLACK;

		DxGraphicsFeature* graphicsFeature = app.Features.get<DxGraphicsFeature>();
		auto commandList = makeIntrusive<CommandList>();
		commandList->init(graphicsFeature->Graphics, graphicsFeature->Graphics.DirectQueue);

		camera = makeIntrusive<Camera2D>();
		camera->ViewSize = { 8, 6 };
		camera->setPositionUp({ 0, 0 });
		cameraComponent = makeIntrusive<CameraComponent2D>(camera.ref());

		world = makeShared<World2D>();
		scene = makeIntrusive<Scene2D>();

		initCaptain();

		{
			auto meshData = makeIntrusive<SpriteMeshData>();
			meshData->init();
			auto mesh = makeIntrusive<DxMesh>();
			mesh->init(meshData.ref(), graphicsFeature->MemoryManager);

			ground = makeIntrusive<Entity2D>();

			{
				auto groundMaterial = IntrusivePointer(app.ResourceManager.load<Material>(ResourceManager::ENGINE_LIB / FilePath(L"materials/DirectX/2d/box.xml")));
				auto groundBox = makeIntrusive<BoxComponent2D>(mesh.ref(), groundMaterial.ref());
				groundBox->init(world.ref());
				groundBox->Type = BodyType::STATIC;
				groundBox->Position = { 0, 0 };
				groundBox->Size = { 5, 1 };
				ground->RootComponent = groundBox.get();
			}

			{
				auto segmentMaterial = IntrusivePointer(app.ResourceManager.load<Material>(ResourceManager::ENGINE_LIB / FilePath(L"materials/DirectX/2d/segment.xml")));
				auto segmentBox = makeIntrusive<SegmentComponent2D>(mesh.ref(), segmentMaterial.ref());
				segmentBox->init(world.ref());
				segmentBox->Type = BodyType::STATIC;
				segmentBox->Position = { 0, -1.1 };
				segmentBox->Size = { 8, 1 };
				ground->RootComponent->Components.add(segmentBox.get());
			}

			scene->Entities.add(ground);
		}
	}

	void DemoWindow::initCaptain() {
		DxGraphicsFeature* graphicsFeature = app.Features.get<DxGraphicsFeature>();

		auto meshData = makeIntrusive<SpriteMeshData>();
		meshData->init();
		auto mesh = makeIntrusive<DxMesh>();
		mesh->init(meshData.ref(), graphicsFeature->MemoryManager);

		auto capsuleMaterial = IntrusivePointer(app.ResourceManager.load<Material>(ResourceManager::ENGINE_LIB / FilePath(L"materials/DirectX/2d/capsule.xml")));

		auto captainCapsule = makeIntrusive<CapsuleComponent2D>(mesh.ref(), capsuleMaterial.ref());
		captainCapsule->init(world.ref());
		captainCapsule->Type = BodyType::DYNAMIC;
		captainCapsule->IsRotationFixed = true;
		captainCapsule->Size = { 0.35, 0.7 };

		captain = makeIntrusive<Entity2D>();
		auto shader = IntrusivePointer(app.ResourceManager.load<DxShader>(ResourceManager::ENGINE_LIB / FilePath(L"shaders/DirectX/2d/sprite.xml")));
		auto material = makeIntrusive<Material>(graphicsFeature->MemoryManager);
		material->Shader = shader.get();
		auto captainSprite = OwnedNotNull<AnimatedSpriteComponent>(ghnew AnimatedSpriteComponent(mesh.ref(), material.ref()));
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
		captainSprite->Position = { 0, -0.025f * 2.0f };
		captainSprite->Size = { 1.6f, 1 };

		captainCapsule->Components.add(captainSprite.reset());
		captainCapsule->Components.add(cameraComponent.get());
		captain->RootComponent = captainCapsule.get();
		scene->Entities.add(captain);
		captain->RootComponent->Position = { 0, 2 };
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
			app.quit();
		} else if (args.KeyCode == 'f') {
			Style = WindowStyle::FULLSCREEN;
			auto currentMode = DisplayManager::getDisplayMode();
			ClientSize = currentMode.size;
			Position = { 0, 0 };
		} else if (args.KeyCode == 'w') {
			BodyComponent2D& body = (BodyComponent2D&)*captain->RootComponent;
			body.applyForce({ 0, 1000 });
		} else if (args.KeyCode == 'a') {
			BodyComponent2D& body = (BodyComponent2D&)*captain->RootComponent;
			body.applyForce({ -1000, 0 });
			captain->RootComponent->Scale = { -1, 1 };
		} else if (args.KeyCode == 'd') {
			BodyComponent2D& body = (BodyComponent2D&)*captain->RootComponent;
			body.applyForce({ 1000, 0 });
			captain->RootComponent->Scale = { 1, 1 };
		} else if (args.KeyCode == 't') {
			Logger::print(LogType::INFO, _T("\n"));
			Logger::print(LogType::INFO, captain->RootComponent->printTree().Data);
			Logger::print(LogType::INFO, _T("\n"));
		}
		return true;
	}

	void DemoWindow::update() {
		__super::update();
		world->simulate((float)Timer.FrameTime);
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
