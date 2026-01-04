#pragma once

#include "engine/directx/mesh/DxMesh.h"
#include "ui/text/ITextMeshFactory.h"
#include "ui/text/TextMesh.h"

namespace Ghurund::UI::DirectX {
	using namespace Ghurund::Engine::DirectX;

	class DxTextMeshFactory:public ITextMeshFactory {
	private:
		DxGPUMemoryManager& memoryManager;

	public:
		DxTextMeshFactory(DxGPUMemoryManager& memoryManager):memoryManager(memoryManager) {}

		virtual Resource* makeMesh(const List<CharacterInfo>& characters, const TextSpan& span) const {
			auto meshData = makeIntrusive<TextMesh>();
			meshData->init(characters, span);
			auto mesh = makeIntrusive<DxMesh>();
			mesh->init(meshData.ref(), memoryManager);
			mesh->addReference();
			return mesh.get();
		}
	};
}