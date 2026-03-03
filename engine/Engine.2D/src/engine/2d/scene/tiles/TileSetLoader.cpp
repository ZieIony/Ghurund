#include "ghe2dpch.h"
#include "TileSetLoader.h"

#include <tinyxml2.h>

namespace Ghurund::Engine::_2D {
	TileSet* TileSetLoader::loadFromXmlInternal(
		const tinyxml2::XMLElement& xml,
		const DirectoryPath& workingDir,
		LoadOption options
	) {
		auto textureAttribute = xml.FindAttribute("texture");
		if (!textureAttribute)
			throw InvalidDataException();
		auto texturePath = FilePath(convertText<char, wchar_t>(AString(textureAttribute->Value())));
		auto texture = IntrusivePointer<ITexture>(resourceManager.load<ITexture>(texturePath, workingDir, ResourceFormat::AUTO, options));

		auto tileSizeAttribute = xml.FindAttribute("tileSize");
		if (!tileSizeAttribute)
			throw InvalidDataException();
		auto tileSize = IntSize::parse(tileSizeAttribute->Value());

		auto tileSet = makeIntrusive<TileSet>();
		tileSet->init(texture.ref(), tileSize);
		tileSet->addReference();
		return tileSet.get();
	}
}
