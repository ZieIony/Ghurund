#include "SampleWindow.h"

#include "SampleApplication.h"

#include "core/Colors.h"
#include "core/window/DisplayManager.h"
#include "engine/3d/graphics/mesh/MeshComponent.h"
#include "engine/graphics/compute/ComputeShader.h"
#include <engine/3d/scene/transform/TransformComponent3D.h>
#include <engine/graphics/mesh/QuadMeshData.h>
#include <engine/3d/scene/transform/TransformSystem3D.h>
#include <engine/3d/graphics/camera/CameraSystem3D.h>
#include "engine/directx/rendering/DxRenderer.h"
#include <engine/3d/graphics/camera/CameraComponent3D.h>

namespace Sample {
	SampleWindow::SampleWindow(SampleApplication& app):GameWindow(app), app(app) {
		closed += DEFAULT_QUIT_APP_WINDOW_CLOSED_HANDLER;
		Title = _T("Sample 3D DirectX");

		Renderer = &app.Features.get<DxGraphicsFeature>()->Renderer;
		BackgroundColor = &Colors::BLACK;

		init();
	}

	void SampleWindow::init() {
		world = ghnew World3D(app);
		world->init();

		meshRenderingSystem = makeIntrusive<MeshRenderingSystem>(*world, ParameterManager);
		Systems.add(makeIntrusive<TransformSystem3D>(*world));
		Systems.add(meshRenderingSystem);
		Systems.add(makeIntrusive<CameraSystem3D>(*world));

		Systems.printGraph();

		app.CoroutineScheduler.launch(initScene());
	}

	CoroutineTask<void> SampleWindow::initScene() {
		BoundingOrientedBox bob, transformedBob;
		{
			auto entity = world->spawnEntity<Entity>();
			auto& meshComponent = entity.addComponent<MeshComponent>();
			auto mesh = co_await app.ResourceManager.load<Mesh>(ResourceManager::ENGINE_LIB_PATH / FilePath(L"test/models/spartan helmet/spartan helmet.fbx"));
			meshComponent.Mesh = mesh.get();

			auto& transformComponent = entity.addComponent<TransformComponent3D>();
			transformComponent.Position = { 10,0,0 };
			BoundingOrientedBox::CreateFromBoundingBox(bob, mesh->BoundingBox);
			transformComponent.update();
			auto transform = XMLoadFloat4x4(&transformComponent.WorldTransformation);
			bob.Transform(transformedBob, transform);

			auto material = co_await app.ResourceManager.load<Material>(ResourceManager::ENGINE_LIB_PATH / FilePath(L"test/models/spartan helmet/spartan helmet material.xml"));
			meshComponent.Material = material.get();
		}

		{
			auto entity = world->spawnEntity<Entity>();
			auto& transformComponent = entity.addComponent<TransformComponent3D>();
			auto& cameraComponent = entity.addComponent<CameraComponent3D>();
			world->Scene.Camera = cameraComponent.Camera;
			cameraComponent.Camera->setDirectionBoxUp({ -1, -0.2f, 1 }, transformedBob);
		}

		cameraController.Camera = world->Scene.Camera;
		cameraController.Window = this;
		meshRenderingSystem->Camera = world->Scene.Camera;

		{
			auto entity = world->spawnEntity<Entity>();
			auto& transformComponent = entity.addComponent<TransformComponent3D>();
			transformComponent.Position = { 0,0,-1000 };
			auto& quadComponent = entity.addComponent<MeshComponent>();
			
			DxGraphicsFeature* graphicsFeature = app.Features.get<DxGraphicsFeature>();
			auto quadMeshData = makeIntrusive<QuadMeshData>();
			quadMeshData->init();
			auto quadMesh = IntrusivePointer<Ghurund::Engine::Mesh>(graphicsFeature->ResourceFactory.makeMesh(quadMeshData.ref()));
			quadComponent.Mesh = quadMesh.get();
			auto material = co_await app.ResourceManager.load<Material>(ResourceManager::ENGINE_LIB_PATH / FilePath(L"materials/DirectX/3d/forward/cubeMap.xml"));
			quadComponent.Material = material.get();
		}

		auto computeShader = co_await app.ResourceManager.load<ComputeShader>(ResourceManager::ENGINE_LIB_PATH / FilePath(L"shaders/DirectX/compute/generateMipMaps.xml"));

		app.ResourceManager.Resources.printResources();
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
}
