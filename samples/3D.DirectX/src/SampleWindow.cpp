#include "SampleWindow.h"

#include "SampleApplication.h"

#include "core/Colors.h"
#include "core/window/DisplayManager.h"
#include "engine/3d/graphics/MeshComponent.h"
#include "engine/3d/graphics/FullscreenQuadComponent.h"
#include "engine/graphics/compute/ComputeShader.h"
#include "engine/directx/rendering/DxRenderer.h"

namespace Sample {
	SampleWindow::SampleWindow(SampleApplication& app):GameWindow(app), app(app) {
		closed += DEFAULT_QUIT_APP_WINDOW_CLOSED_HANDLER;
		Title = _T("Sample 3D DirectX");

		Renderer = &app.Features.get<DxGraphicsFeature>()->Renderer;
		BackgroundColor = &Colors::BLACK;

		init();
	}

	void SampleWindow::init() {
		DxGraphicsFeature* graphicsFeature = app.Features.get<DxGraphicsFeature>();

		world = ghnew World3D(app);
		world->init();

		app.CoroutineScheduler.launch(initScene());
	}

	CoroutineTask<void> SampleWindow::initScene() {
		{
			auto entity = co_await world->spawnEntity<Entity3D>();
			auto meshComponent = entity->makeComponent<MeshComponent>();
			auto mesh = co_await app.ResourceManager.load<Mesh>(ResourceManager::ENGINE_LIB_PATH / FilePath(L"test/models/spartan helmet/spartan helmet.fbx"));
			meshComponent->Mesh = mesh.get();

			entity->Transform.Position = { 10,0,0 };
			BoundingOrientedBox bob, transformedBob;
			BoundingOrientedBox::CreateFromBoundingBox(bob, mesh->BoundingBox);
			entity->Transform.update(app.Timer);
			auto transform = XMLoadFloat4x4(&entity->Transform.WorldTransformation);
			bob.Transform(transformedBob, transform);
			world->Scene.Camera->setDirectionBoxUp({ -1, -0.2f, 1 }, transformedBob);

			auto material = co_await app.ResourceManager.load<Material>(ResourceManager::ENGINE_LIB_PATH / FilePath(L"test/models/spartan helmet/spartan helmet material.xml"));
			meshComponent->Material = material.get();
			entity->Components.add(meshComponent.ref());
			co_await entity->init();
		}

		cameraController.Camera = world->Scene.Camera;
		cameraController.Window = this;

		{
			auto entity = co_await world->spawnEntity<Entity3D>();
			entity->Transform.Position = { 0,0,-1000 };
			auto quadComponent = entity->makeComponent<FullscreenQuadComponent>();
			
			auto material = co_await app.ResourceManager.load<Material>(ResourceManager::ENGINE_LIB_PATH / FilePath(L"materials/DirectX/3d/forward/cubeMap.xml"));
			quadComponent->Material = material.get();
			quadComponent->drawOrder = -1;
			entity->Components.add(quadComponent.ref());
			co_await entity->init();
		}

		auto computeShader = co_await app.ResourceManager.load<ComputeShader>(ResourceManager::ENGINE_LIB_PATH / FilePath(L"shaders/DirectX/compute/generateMipMaps.xml"));

		app.ResourceManager.printResources();
	}

	bool SampleWindow::onKeyEvent(const KeyEventArgs& args) {
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
			app.quit();
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

	bool SampleWindow::onSizeChanged() {
		__super::onSizeChanged();
		world->Scene.Camera->ViewSize = ClientSize;

		// recalculate horizontal fov based on current vertical fov and new aspect ratio
		world->Scene.Camera->FOV = world->Scene.Camera->FOV.y;
		return true;
	}

	void SampleWindow::update() {
		__super::update();

		auto text = std::format(_T("fps: {:.2f}"), Timer.FramesPerSecond);
		Title = String(text.c_str());
	}

	void SampleWindow::onPaint(RenderingContext& renderingContext) {
		RenderGroup _3dGroup(DrawGroup(0, DrawOrder::BACK_TO_FRONT));
		_3dGroup.Camera = world->Scene.Camera;
		world->queueDraw(_3dGroup);
		renderGroups.put(_3dGroup);

		renderingContext.clear(BackgroundColor);
		renderingContext.draw(renderGroups, ParameterManager);
	}
}
