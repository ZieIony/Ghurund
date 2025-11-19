#pragma once

#include "engine/graphics/mesh/ITextMeshFactory.h"
#include <engine/graphics/mesh/TextMesh.h>
#include "DxMesh.h"

namespace Ghurund::Engine::DirectX {
	class DxTextMeshFactory:public ITextMeshFactory {
	private:
		DxGraphics& graphics;
		CommandList& commandList;

	public:
		DxTextMeshFactory(DxGraphics& graphics, CommandList& commandList):graphics(graphics), commandList(commandList) {}

		virtual Resource* makeMesh(const WString& text, const Ghurund::UI::Font& font) const {
			auto meshData = makeIntrusive<TextMesh>();
			meshData->init(L"Heylo wórld.", font);
			auto mesh = makeIntrusive<DxMesh>();
			mesh->init(meshData.ref(), graphics, commandList);
			mesh->addReference();
			return mesh.get();
		}
	};
}