#pragma once

#include "DemoApplication.h"
#include "engine/application/GameWindow.h"
#include "ui/material/UIMaterial.h"
#include "ui/text/TextLayout.h"

namespace Demo {
	using namespace Ghurund;
	using namespace Ghurund::Core;
	using namespace Ghurund::UI;

	class DemoWindow:public Ghurund::Engine::GameWindow {
	private:
		DemoApplication& app;

		Set<RenderGroup> renderGroups;

		IntrusivePointer<Mesh> shadowMesh;
		IntrusivePointer<UIMaterial> basicMaterial, controlMaterial;
		IntrusivePointer<TextStyle> textStyle;

		TextureInput* colorTextureInput;
		IntrusivePointer<DxTexture> colorTexture;

		TextLayout textLayout;

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