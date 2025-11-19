#pragma once

#include "DemoApplication.h"
#include "engine/application/GameWindow.h"
#include "ui/font/Font.h"
#include <engine/directx/mesh/DxMesh.h>
#include <engine/entity/camera/Camera.h>
#include <ui/font/FontLoader.h>

namespace Demo {
	using namespace Ghurund;
	using namespace Ghurund::Core;
	using namespace Ghurund::UI;

	class DemoWindow:public Ghurund::Engine::GameWindow {
	private:
		DemoApplication& app;

		Set<RenderGroup> renderGroups;

		IntrusivePointer<Resource> mesh;
		IntrusivePointer<IMaterial> basicMaterial;
		IntrusivePointer<Camera> camera;
		IntrusivePointer<Font> font;

		Float2Parameter* sizeParameter;
		Float4Parameter* backgroundColorParameter;
		Float4Parameter* borderColorParameter;
		TextureParameter* colorTextureParameter;
		IntrusivePointer<Texture> colorTexture;

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