#include "SampleWindow.h"

#include "SampleApplication.h"

#include "core/Colors.h"
#include "core/window/DisplayManager.h"
#include <FpsSystem.h>
#include <engine/2d/scene/transform/TransformSystem.h>
#include <engine/2d/scene/tiles/TileMapSystem.h>
#include <engine/2d/graphics/sprite/animation/SpriteAnimationSystem.h>
#include <engine/2d/scene/camera/CameraSystem2D.h>

namespace Sample {
	SampleWindow::SampleWindow(SampleApplication& app):GameWindow(app), app(app) {
		closed += DEFAULT_QUIT_APP_WINDOW_CLOSED_HANDLER;
		Title = _T("Sample 3D DirectX");

		Renderer = &app.Features.get<DxGraphicsFeature>()->Renderer;
		BackgroundColor = &Colors::BLACK;
	}

	void SampleWindow::init() {
		auto fpsSystem = makeIntrusive<FpsSystem>(*this);
		Systems.add(fpsSystem);

		world = ghnew World2D(app);
		world->init();

		spriteRenderingSystem = makeIntrusive<SpriteRenderingSystem>(*world, ParameterManager);
		visualizationRenderingSystem = makeIntrusive<VisualizationRenderingSystem>(*world, ParameterManager);
		Systems.add(makeIntrusive<TransformSystem2D>(*world));
		Systems.add(makeIntrusive<PhysicsSystem2D>(*world));
		Systems.add(spriteRenderingSystem);
		Systems.add(visualizationRenderingSystem);
		Systems.add(makeIntrusive<TileMapSystem>(*world));
		Systems.add(makeIntrusive<SpriteAnimationSystem>(*world));
		Systems.add(makeIntrusive<CameraSystem2D>(*world));

		Application.CoroutineScheduler.launch(initScene());
	}

	CoroutineTask<void> SampleWindow::initScene() {
		ground = world->spawnEntity<Ground>();
		co_await ground.init(*Systems.get<PhysicsSystem2D>(), app.Features.get<GraphicsFeature>()->ResourceFactory, app.ResourceManager);
		captain = world->spawnEntity<Captain>();
		co_await captain.init(*Systems.get<PhysicsSystem2D>(), app.ResourceManager, *world);
		captain.CapsuleComponent.Position = {0, 2};

		spriteRenderingSystem->Camera = world->Scene.Camera;
		visualizationRenderingSystem->Camera = world->Scene.Camera;

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
		} else if (args.KeyCode == 'p') {
			Timer.TimeScale = Timer.TimeScale == 1.0f ? 0.1f : 1.0f;
		}
		return true;
	}
}
