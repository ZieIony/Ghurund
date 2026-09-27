#include "ghedxpch.h"
#include "DxTextureLoader.h"

namespace Ghurund::Engine::DirectX {
	CoroutineTask<void> DxTextureLoader::loadInternal(
		DxTexture& resource,
		const XMLElement& xml,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOptions options
	) {
		checkXmlRoot(xml, L"Texture");
	
		WString* imagePathAttribute = xml.findAttribute(L"image");
		if(!imagePathAttribute)
			Logger::logAndThrow<InvalidDataException>(_T("Required 'image' attribute on 'Texture' node is missing.\n"));

		FilePath path = FilePath(*imagePathAttribute);
		auto image = co_await resourceManager.load<Image>(path, workingDir);
		resource.init(image.ref(), memoryManager);
	}
}
