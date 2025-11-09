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
		IntrusivePointer<DxMesh> mesh;
		IntrusivePointer<Material> basicMaterial;
		IntrusivePointer<Camera> camera;

		IntrusivePointer<Float2Parameter> sizeParameter;
		IntrusivePointer<Float4Parameter> backgroundColorParameter;
		IntrusivePointer<Float4Parameter> borderColorParameter;

	public:
		DemoWindow(
			DemoApplication& app,
			Ghurund::Engine::DirectX::DxRenderer& renderer
		);

		virtual bool onMouseButtonEvent(const MouseButtonEventArgs& args) override;

		virtual bool onKeyEvent(const KeyEventArgs& args) override;

		virtual void onPaint(RenderingContext& renderingContext) override;
	};
}