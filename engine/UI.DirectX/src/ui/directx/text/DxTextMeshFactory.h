#pragma once

#include "ui/text/ITextMeshFactory.h"
#include <ui/text/TextMesh.h>
#include "engine/directx/mesh/DxMesh.h"

namespace Ghurund::UI::DirectX {
	using namespace Ghurund::Engine::DirectX;

	class DxTextMeshFactory:public ITextMeshFactory {
	private:
		DxGraphics& graphics;
		CommandList& commandList;

	public:
		DxTextMeshFactory(DxGraphics& graphics, CommandList& commandList):graphics(graphics), commandList(commandList) {}

		virtual Resource* makeMesh(const WString& text, const Ghurund::UI::Font& font) const {
			auto meshData = makeIntrusive<TextMesh>();
			meshData->init(text, font);
			auto mesh = makeIntrusive<DxMesh>();
			mesh->init(meshData.ref(), graphics, commandList);
			mesh->addReference();
			return mesh.get();
		}
	};
}