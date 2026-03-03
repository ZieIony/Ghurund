#include "ghe2dpch.h"
#include "TileMapLoader.h"

#include <tinyxml2.h>

namespace Ghurund::Engine::_2D {
	TileMap* TileMapLoader::loadFromXmlInternal(
		const tinyxml2::XMLElement& xml,
		const DirectoryPath& workingDir,
		LoadOption options
	) {
		auto tileSetAttribute = xml.FindAttribute("tileSet");
		if (!tileSetAttribute)
			throw InvalidDataException();
		auto tileSetPath = FilePath(convertText<char, wchar_t>(AString(tileSetAttribute->Value())));
		auto tileSet = IntrusivePointer<TileSet>(resourceManager.load<TileSet>(tileSetPath, workingDir, ResourceFormat::AUTO, options));

		IntSize size = [&] {
			auto sizeAttribute = xml.FindAttribute("size");
			if (sizeAttribute) {
				return IntSize::parse(sizeAttribute->Value());
			} else {
				// TODO: load size from number of tiles
				throw InvalidDataException();
			}
		}();

		auto map = makeIntrusive<TileMap>();
		map->init(tileSet.ref(), size);

		auto tilesChild = xml.FirstChild();
		if (!tilesChild)
			throw InvalidDataException();
		auto tilesContent = AString(tilesChild->Value());
		auto tileRows = tilesContent.trim().split("\n");
		for (size_t y = 0; y < tileRows.Size; y++) {
			auto& row = tileRows[y];
			auto tiles = row.trim().split(" ");
			if (tiles.Size != size.Width)
				throw InvalidDataException();
			for (size_t x = 0; x < tiles.Size; x++) {
				auto& tile = tiles[x];
				map->set({ (uint32_t)x, (uint32_t)y }, parse<uint32_t>(tile));
			}
		}
		map->addReference();
		return map.get();
	}
}
