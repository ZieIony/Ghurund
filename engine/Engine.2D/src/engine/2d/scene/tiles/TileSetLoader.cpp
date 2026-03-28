#include "ghe2dpch.h"
#include "TileSetLoader.h"

namespace Ghurund::Engine::_2D {
	void TileSetLoader::loadInternal(
		TileSet& resource,
		const XMLElement& xml,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		checkXmlRoot(xml, L"TileSet");
	
		auto textureAttribute = xml.findAttribute(L"texture");
		if (!textureAttribute)
			throw InvalidDataException();
		auto texturePath = FilePath(*textureAttribute);
		auto texture = IntrusivePointer<ITexture>(resourceManager.load<ITexture>(texturePath, workingDir, ResourceFormat::AUTO, options));

		auto tileSizeAttribute = xml.findAttribute(L"tileSize");
		if (!tileSizeAttribute)
			throw InvalidDataException();
		auto tileSize = IntSize::parse(convertText<wchar_t, char>(*tileSizeAttribute));

		resource.init(texture.ref(), tileSize);
	}
}
