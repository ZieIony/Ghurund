#include "ghedxpch.h"
#include "DxMaterialLoader.h"

#include "DxMaterial.h"

namespace Ghurund::Engine::DirectX {
	Resource* DxMaterialLoader::loadInternal(
		MemoryInputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		auto shader = IntrusivePointer<DxShader>((DxShader*)shaderLoader.load(stream, workingDir, format, options));
		auto material = makeIntrusive<DxMaterial>();
		material->Shader = shader.get();
		material->addReference();
		return material.get();
	}

	void DxMaterialLoader::saveInternal(
		MemoryOutputStream& stream,
		const DirectoryPath& workingDir,
		Resource& resource,
		const ResourceFormat& format,
		SaveOption options
	) const {
		auto& material = castResource<DxMaterial>(resource);
		shaderLoader.save(stream, workingDir, *material.Shader, format, options);
	}
}
