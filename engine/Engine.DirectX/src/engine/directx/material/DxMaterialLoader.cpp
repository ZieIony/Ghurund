#include "ghedxpch.h"
#include "DxMaterialLoader.h"

#include "DxMaterial.h"

#include <tinyxml2.h>

namespace Ghurund::Engine::DirectX {
	Resource* DxMaterialLoader::loadInternal(
		MemoryInputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		tinyxml2::XMLDocument doc;
		doc.Parse((const char*)stream.Data, stream.Size);
		tinyxml2::XMLElement* xml = doc.RootElement();
		if (AString("Material") != xml->Name())
			throw InvalidFormatException();
		
		return loadFromXml(*xml, workingDir);
	}

	void DxMaterialLoader::saveInternal(
		MemoryOutputStream& stream,
		const DirectoryPath& workingDir,
		Resource& resource,
		const ResourceFormat& format,
		SaveOption options
	) const {
		auto& material = castResource<DxMaterial>(resource);
		//shaderLoader.save(stream, workingDir, *material.Shader, format, options);
	}
}
