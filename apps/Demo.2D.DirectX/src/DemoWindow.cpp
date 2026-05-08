#include "DemoWindow.h"

#include "DemoApplication.h"

#include "core/Colors.h"
#include "core/window/DisplayManager.h"

namespace Demo {
	DemoWindow::DemoWindow(
		DemoApplication& app,
		Ghurund::Engine::DirectX::DxRenderer& renderer
	):GameWindow(app), app(app) {
		closed += DEFAULT_QUIT_APP_WINDOW_CLOSED_HANDLER;
		Title = _T("Demo 3D DirectX");

		Renderer = &renderer;
		BackgroundColor = &Colors::BLACK;

		init();
	}

	void DemoWindow::init() {
		DxGraphicsFeature* graphicsFeature = app.Features.get<DxGraphicsFeature>();

		context2d = makeShared<DxGraphics2DContext>(graphicsFeature->MemoryManager, app.ResourceManager);

		simulation = makeShared<Simulation2D>();
		scene = makeIntrusive<Scene2D>(context2d.ref());

		AudioFeature* audioFeature = app.Features.get<AudioFeature>();
		audioWorld = makeShared<AudioWorld2D>(audioFeature->Audio);

		world.app = &app;
		world.audioWorld = audioWorld.get();
		world.simulation = simulation.get();
		world.scene = scene.get();
		world.context = context2d.get();

		app.CoroutineScheduler.launch(initScene());
	}

	CoroutineTask<void> DemoWindow::initScene() {
		ground = co_await world.spawnEntity<Ground>();
		captain = co_await world.spawnEntity<Captain>();
		captain->Components.get<BodyComponent2D>()->Position = {0, 2};
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
			captain->jump();
		} else if (args.KeyCode == 'q') {
			captain->playSound();
		} else if (args.KeyCode == 'a') {
			captain->moveLeft();
		} else if (args.KeyCode == 'd') {
			captain->moveRight();
		} else if (args.KeyCode == 't') {
			Logger::print(LogType::INFO, _T("\n"));
			//Logger::print(LogType::INFO, captain->printTree().Data);
			Logger::print(LogType::INFO, _T("\n"));
		} else if (args.KeyCode == 'p') {
			Timer.TimeScale = Timer.TimeScale == 1.0f ? 0.1f : 1.0f;
		}
		return true;
	}

	void DemoWindow::update() {
		__super::update();
		world.update(Timer);

		auto text = std::format(_T("fps: {:.2f}"), Timer.FramesPerSecond);
		Title = String(text.c_str());
	}

	void DemoWindow::onPaint(RenderingContext& renderingContext) {
		RenderGroup _2dGroup(0, DrawOrder::BACK_TO_FRONT);
		_2dGroup.Camera = scene->Camera;
		scene->draw(_2dGroup);
		renderGroups.put(_2dGroup);

		renderingContext.clear(BackgroundColor);
		renderingContext.draw(renderGroups, ParameterManager);
	}
}
