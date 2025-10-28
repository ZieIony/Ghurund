#pragma once

#include "engine/application/GameWindow.h"
#include "DemoApplication.h"
#include <engine/directx/mesh/DxMesh.h>
#include <engine/entity/camera/Camera.h>

namespace Demo {
	using namespace Ghurund;
	using namespace Ghurund::Core;

	class DemoWindow:public Ghurund::Engine::GameWindow {
	private:
		DemoApplication& app;
		ParameterManager& parameterManager;
		IntrusivePointer<DxMesh> mesh;
		IntrusivePointer<Material> basicMaterial;
		IntrusivePointer<Camera> camera;

	public:
		DemoWindow(
			DemoApplication& app,
			Ghurund::Engine::DirectX::DxRenderer& renderer,
			ParameterManager& parameterManager
		);

		virtual bool onKeyEvent(const KeyEventArgs& args) override;

		virtual void onPaint(RenderingContext& renderingContext) override;
	};
}