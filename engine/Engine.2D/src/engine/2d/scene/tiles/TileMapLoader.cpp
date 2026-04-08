#include "ghe2dpch.h"
#include "TileMapLoader.h"

namespace Ghurund::Engine::_2D {
	CoroutineTask<void> TileMapLoader::loadInternal(
		TileMap& resource,
		const XMLElement& xml,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		checkXmlRoot(xml, L"TileMap");
	
		auto tileSetAttribute = xml.findAttribute(L"tileSet");
		if (!tileSetAttribute)
			throw InvalidDataException();
		auto tileSetPath = FilePath(*tileSetAttribute);
		auto tileSet = co_await resourceManager.load<TileSet>(tileSetPath, workingDir, ResourceFormat::AUTO, options);

		IntSize size = [&] {
			auto sizeAttribute = xml.findAttribute(L"size");
			if (sizeAttribute) {
				return IntSize::parse(convertText<wchar_t, char>(*sizeAttribute));
			} else {
				// TODO: load size from number of tiles
				throw InvalidDataException();
			}
		}();

		resource.init(tileSet.ref(), size);

		if (xml.value.Empty)
			throw InvalidDataException();
		auto tilesContent = convertText<wchar_t, char>(xml.value);
		auto tileRows = tilesContent.trim().split("\n");
		for (size_t y = 0; y < tileRows.Size; y++) {
			auto& row = tileRows[y];
			auto tiles = row.trim().split(" ");
			if (tiles.Size != size.Width)
				throw InvalidDataException();
			for (size_t x = 0; x < tiles.Size; x++) {
				auto& tile = tiles[x];
				resource.set({ (uint32_t)x, (uint32_t)y }, parse<uint32_t>(tile));
			}
		}
		co_return;
	}
}
