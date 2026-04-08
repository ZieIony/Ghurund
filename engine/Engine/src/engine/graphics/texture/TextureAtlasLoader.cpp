#include "ghepch.h"
#include "TextureAtlasLoader.h"

namespace Ghurund::Engine {
	CoroutineTask<void> TextureAtlasLoader::loadInternal(
		TextureAtlas& resource,
		const XMLElement& xml,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		checkXmlRoot(xml, L"TextureAtlas");
	
		auto textureAttribute = xml.findAttribute(L"texture");
		if (!textureAttribute)
			throw InvalidDataException();
		auto texturePath = FilePath(*textureAttribute);
		auto texture = co_await resourceManager.load<ITexture>(texturePath, workingDir, ResourceFormat::AUTO, options);

		IntSize size = [&] {
			auto sizeAttribute = xml.findAttribute(L"size");
			if (sizeAttribute) {
				return IntSize::parse(convertText<wchar_t, char>(*sizeAttribute));
			} else {
				// TODO: load size for each atlas item separately
				throw InvalidDataException();
			}
		}();

		resource.init(texture.ref(), size);
		co_return;
	}
}
