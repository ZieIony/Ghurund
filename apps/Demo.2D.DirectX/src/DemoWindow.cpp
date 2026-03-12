#include "DemoWindow.h"

#include "DemoApplication.h"

#include "core/Colors.h"
#include "core/window/DisplayManager.h"
#include <engine/2d/graphics/sprite/AnimatedSpriteComponent.h>
#include <engine/2d/physics/component/BoxComponent2D.h>
//#include "engine/2d/entity/CameraComponent2D.h"
#include "ui/theme/LightTheme.h"
#include <engine/2d/physics/component/CapsuleComponent2D.h>
#include <engine/2d/physics/component/SegmentComponent2D.h>
#include <engine/2d/scene/tiles/TileMapComponent.h>

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

		context2d = makeShared<DxGraphics2DContext>(graphicsFeature->MemoryManager, app.ResourceManager);

		camera = makeIntrusive<Camera2D>();
		camera->ViewSize = { 8, 6 };
		camera->setPositionUp({ 0, 0 });
		cameraComponent = makeIntrusive<CameraComponent2D>(camera.ref());

		world = makeShared<World2D>();
		scene = makeIntrusive<Scene2D>(context2d.ref());

		app.CoroutineScheduler.launch(initScene());
	}

	CoroutineTask DemoWindow::initScene() {
		co_await initGround();
		co_await initCaptain();
	}

	CoroutineTask DemoWindow::initGround() {
		ground = makeIntrusive<Entity2D>();
		ground->Context = context2d.get();

		{
			auto groundBox = makeIntrusive<BoxComponent2D>();
			groundBox->World = world.get();
			groundBox->Owner = ground.get();
			groundBox->init();
			groundBox->Type = BodyType::STATIC;
			groundBox->Position = { 0, 0 };
			groundBox->Size = { 5, 1 };
			ground->RootComponent = groundBox.get();
		}

		{
			auto segmentBox = makeIntrusive<SegmentComponent2D>();
			segmentBox->World = world.get();
			segmentBox->Owner = ground.get();
			segmentBox->init();
			segmentBox->Type = BodyType::STATIC;
			segmentBox->Position = { 0, -1.1f };
			segmentBox->Size = { 8, 1 };
			ground->RootComponent->Components.add(segmentBox.get());
		}

		{
			co_await app.CoroutineScheduler.mainThread();
		//	co_await app.CoroutineScheduler.backgroundThread();
			auto tileMap = IntrusivePointer<TileMap>(app.ResourceManager.load<TileMap>(ResourceManager::ENGINE_LIB / FilePath(L"test/images/terrainTileMap.xml")));
			co_await app.CoroutineScheduler.mainThread();
			auto tileMapComponent = makeIntrusive<TileMapComponent>();
			tileMapComponent->TileMap = tileMap.get();
			tileMapComponent->Owner = ground.get();
			tileMapComponent->init();
			tileMapComponent->Position = { 0.0f, -1.0f };
			ground->RootComponent->Components.add(tileMapComponent.get());
		}

		ground->init();
		scene->Entities.add(ground);
	}

	CoroutineTask DemoWindow::initCaptain() {
		DxGraphicsFeature* graphicsFeature = app.Features.get<DxGraphicsFeature>();

		captain = makeIntrusive<Entity2D>();
		captain->Context = context2d.get();

		auto captainCapsule = makeIntrusive<CapsuleComponent2D>();
		captainCapsule->World = world.get();
		captainCapsule->Owner = captain.get();
		captainCapsule->init();
		captainCapsule->Type = BodyType::DYNAMIC;
		captainCapsule->IsRotationFixed = true;
		captainCapsule->Size = { 0.35f, 0.7f };

		auto captainSprite = makeIntrusive<AnimatedSpriteComponent>();
		captainSprite->Owner = captain.get();
		captainSprite->init();

		co_await app.CoroutineScheduler.mainThread();
	//	co_await app.CoroutineScheduler.backgroundThread();
		auto animationSet = IntrusivePointer<SpriteAnimationSet>(app.ResourceManager.load<SpriteAnimationSet>(ResourceManager::ENGINE_LIB / FilePath(L"test/images/captain.xml")));
		co_await app.CoroutineScheduler.mainThread();
		captainSprite->Animation = animationSet->get(animationSet->find("idle"));

		captainSprite->Position = { 0, -0.025f * 2.0f };
		captainSprite->Size = { 1.6f, 1 };

		captainCapsule->Components.add(captainSprite.get());
		captainCapsule->Components.add(cameraComponent.get());
		captain->RootComponent = captainCapsule.get();
		captain->init();
		scene->Entities.add(captain);
		captain->RootComponent->Position = { 0, 2 };
	}

	CoroutineTask DemoWindow::jumpDelayed() {
		co_await app.CoroutineScheduler.delayedUpdate(1000);
		BodyComponent2D& body = (BodyComponent2D&)*captain->RootComponent;
		body.applyForce({ 0, 1000 });
		co_await app.CoroutineScheduler.delayedUpdate(1000);
		body.applyForce({ 1000, 0 });
		co_await app.CoroutineScheduler.delayedUpdate(1000);
		body.applyForce({ -1000, 0 });
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
		} else if (args.KeyCode == 'e') {
			jumpDelayed();
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
