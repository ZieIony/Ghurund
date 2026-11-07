#include "SampleWindow.h"

#include "SampleApplication.h"

#include "core/Colors.h"
#include "engine/graphics/compute/ComputeShader.h"
#include <engine/3d/graphics/transform/TransformSystem3D.h>
#include <engine/3d/graphics/camera/CameraSystem3D.h>
#include "engine/directx/rendering/DxRenderer.h"
#include <LookAtEntityScript.h>
#include <engine/directx/imgui/ImGuiSystem.h>

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

		auto& scriptManager = app.Features.get<EngineFeature>()->ScriptManager;
		scriptManager.registerScript<LookAtEntityScript>();

		meshRenderingSystem = makeIntrusive<MeshRenderingSystem>(*world, ParameterManager);
		Systems.add(makeIntrusive<TransformSystem3D>(*world));
		Systems.add(meshRenderingSystem);
		Systems.add(makeIntrusive<CameraSystem3D>(*world));

		auto graphicsFeature = app.Features.get<DxGraphicsFeature>();
		imGuiSystem = makeIntrusive<ImGuiSystem>(graphicsFeature->Graphics);
		Systems.add(imGuiSystem);
		imGuiSystem->initWindow(*this);

		Systems.printGraph();

		app.CoroutineScheduler.launch(initScene());
	}

	CoroutineTask<void> SampleWindow::initScene() {
		auto scene = co_await app.ResourceManager.load<Scene>(ResourceManager::ENGINE_LIB_PATH / FilePath(L"test/models/spartan helmet/spartan helmet scene.xml"));
		world->Scene = scene.get();

		cameraController.Camera = (Camera3D*)world->Scene->Camera;
		cameraController.Window = this;
		meshRenderingSystem->Camera = world->Scene->Camera;

		/*{
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
		}*/

		auto computeShader = co_await app.ResourceManager.load<ComputeShader>(ResourceManager::ENGINE_LIB_PATH / FilePath(L"shaders/DirectX/compute/generateMipMaps.xml"));

		app.ResourceManager.Resources.printResources();
	}

	bool SampleWindow::onKeyEvent(const KeyEventArgs& args) {
		//bool result = __super::onKeyEvent(args);
		//if (result)
			//return true;

		if (args.KeyCode == VK_ESCAPE) {
			app.quit();
		} else if (args.KeyCode == 'b') {
			meshRenderingSystem->defaultMaterialType = MaterialVariantType::LIT;
		} else if (args.KeyCode == 'n') {
			meshRenderingSystem->defaultMaterialType = MaterialVariantType::DEPTH;
		} else if (args.KeyCode == 'm') {
			meshRenderingSystem->defaultMaterialType = MaterialVariantType::NORMALS;
		}
		return true;
	}

	bool SampleWindow::onSizeChanged() {
		__super::onSizeChanged();
		world->Scene->Camera->ViewSize = ClientSize;

		// recalculate horizontal fov based on current vertical fov and new aspect ratio
		((Camera3D*)world->Scene->Camera)->FOV = ((Camera3D*)world->Scene->Camera)->FOV.y;
		return true;
	}

	void SampleWindow::update() {
		__super::update();

		auto text = std::format(_T("fps: {:.2f}"), Timer.FramesPerSecond);
		Title = String(text.c_str());
	}
}
