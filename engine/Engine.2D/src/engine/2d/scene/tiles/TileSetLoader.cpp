#include "ghe2dpch.h"
#include "TileSetLoader.h"

namespace Ghurund::Engine::_2D {
	CoroutineTask<void> TileSetLoader::loadInternal(
		TileSet& resource,
		const XMLElement& xml,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOptions options
	) {
		checkXmlRoot(xml, L"TileSet", format);
	
		auto textureAttribute = xml.requireAttribute(L"texture");
		auto texturePath = FilePath(textureAttribute);
		auto texture = co_await resourceManager.load<ITexture>(texturePath, workingDir, ResourceFormat::AUTO, nullptr, options);

		auto tileSizeAttribute = xml.requireAttribute(L"tileSize");
		auto tileSize = IntSize::parse(convertText<wchar_t, char>(tileSizeAttribute));

		resource.init(texture.ref(), tileSize);
	}
}
