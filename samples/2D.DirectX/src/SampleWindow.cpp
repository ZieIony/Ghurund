#include "SampleWindow.h"

#include "FpsSystem.h"
#include "SampleApplication.h"

#include "core/Colors.h"
#include "core/window/DisplayManager.h"
#include "engine/2d/graphics/camera/CameraComponent2D.h"
#include "engine/2d/graphics/camera/CameraSystem2D.h"
#include "engine/2d/graphics/sprite/animation/SpriteAnimationSystem.h"
#include "engine/2d/graphics/tiles/TileMapSystem.h"
#include "engine/2d/graphics/transform/TransformSystem2D.h"

namespace Sample {
	SampleWindow::SampleWindow(SampleApplication& app):GameWindow(app), app(app) {
		closed += DEFAULT_QUIT_APP_WINDOW_CLOSED_HANDLER;
		Title = _T("Sample 3D DirectX");

		Renderer = &app.Features.get<DxGraphicsFeature>()->Renderer;
		BackgroundColor = &Colors::BLACK;
	}

	void SampleWindow::init() {
		Systems.add(makeIntrusive<FpsSystem>(*this));

		world = ghnew World2D(app);
		world->init();

		spriteRenderingSystem = makeIntrusive<SpriteRenderingSystem>(*world);
		visualizationRenderingSystem = makeIntrusive<VisualizationRenderingSystem>(*world);
		Systems.add(makeIntrusive<TransformSystem2D>(*world));
		Systems.add(makeIntrusive<PhysicsSystem2D>(*world));
		Systems.add(spriteRenderingSystem);
		Systems.add(visualizationRenderingSystem);
		Systems.add(makeIntrusive<TileMapSystem>(*world));
		Systems.add(makeIntrusive<SpriteAnimationSystem>(*world));
		Systems.add(makeIntrusive<CameraSystem2D>(*world));

		Systems.printGraph();

		Application.CoroutineScheduler.launch(initScene());
	}

	CoroutineTask<void> SampleWindow::initScene() {
		auto graphicsFeature = app.Features.get<GraphicsFeature>();
		ground = world->Scene->spawnEntity<Ground>();
		co_await ground.init(*Systems.get<PhysicsSystem2D>(), graphicsFeature->ResourceFactory, app.ResourceManager, graphicsFeature->MemoryManager);
		captain = world->Scene->spawnEntity<Captain>();
		co_await captain.init(*Systems.get<PhysicsSystem2D>(), app.ResourceManager, graphicsFeature->MemoryManager, *world);
		captain.CapsuleComponent.Position = {0, 2};

		spriteRenderingSystem->Camera = captain.getComponent<CameraComponent2D>().Camera;
		visualizationRenderingSystem->Camera = captain.getComponent<CameraComponent2D>().Camera;

		app.ResourceManager.Resources.printResources();
	}

	bool SampleWindow::onKeyEvent(const KeyEventArgs& args) {
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
			Application.quit();
		} else if (args.KeyCode == 'f') {
			Style = WindowStyle::FULLSCREEN;
			auto currentMode = DisplayManager::getDisplayMode();
			ClientSize = currentMode.size;
			Position = { 0, 0 };
		} else if (args.KeyCode == 'w') {
			captain.jump();
		} else if (args.KeyCode == 'q') {
			captain.playSound();
		} else if (args.KeyCode == 'a') {
			captain.moveLeft();
		} else if (args.KeyCode == 'd') {
			captain.moveRight();
		} else if (args.KeyCode == 't') {
			Logger::print(LogType::INFO, _T("\n"));
			//Logger::print(LogType::INFO, captain->printTree().Data);
			Logger::print(LogType::INFO, _T("\n"));
		} else if (args.KeyCode == '0') {
			Timer.TimeScale = 0.0f;
			Timer.FixedFrameTime = 1.0f / 60 * Timer.TimeScale;
		} else if (args.KeyCode == '1') {
			Timer.TimeScale = 0.25f;
			Timer.FixedFrameTime = 1.0f / 60 * Timer.TimeScale;
		} else if (args.KeyCode == '2') {
			Timer.TimeScale = 0.5f;
			Timer.FixedFrameTime = 1.0f / 60 * Timer.TimeScale;
		} else if (args.KeyCode == '3') {
			Timer.TimeScale = 1.0f;
			Timer.FixedFrameTime = 1.0f / 60 * Timer.TimeScale;
		} else if (args.KeyCode == '4') {
			Timer.TimeScale = 2.0f;
			Timer.FixedFrameTime = 1.0f / 60 * Timer.TimeScale;
		}
		return true;
	}
}
