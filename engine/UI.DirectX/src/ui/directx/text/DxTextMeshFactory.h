#pragma once

#include "engine/directx/mesh/DxMesh.h"
#include "ui/text/ITextMeshFactory.h"
#include "ui/text/TextMesh.h"

namespace Ghurund::UI::DirectX {
	using namespace Ghurund::Engine::DirectX;

	class DxTextMeshFactory:public ITextMeshFactory {
	private:
		DxGraphics& graphics;
		CommandList& commandList;

	public:
		DxTextMeshFactory(DxGraphics& graphics, CommandList& commandList):graphics(graphics), commandList(commandList) {}

		virtual Resource* makeMesh(const List<CharacterInfo>& characters, const TextSpan& span) const {
			auto meshData = makeIntrusive<TextMesh>();
			meshData->init(characters, span);
			auto mesh = makeIntrusive<DxMesh>();
			mesh->init(meshData.ref(), graphics, commandList);
			mesh->addReference();
			return mesh.get();
		}
	};
}