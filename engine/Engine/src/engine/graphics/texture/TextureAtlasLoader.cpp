#include "ghepch.h"
#include "TextureAtlasLoader.h"

#include <tinyxml2.h>

namespace Ghurund::Engine {
	TextureAtlas* TextureAtlasLoader::loadFromXmlInternal(
		const tinyxml2::XMLElement& xml,
		const DirectoryPath& workingDir,
		LoadOption options
	) {
		auto textureAttribute = xml.FindAttribute("texture");
		if (!textureAttribute)
			throw InvalidDataException();
		auto texturePath = FilePath(convertText<char, wchar_t>(AString(textureAttribute->Value())));
		auto texture = IntrusivePointer<ITexture>(resourceManager.load<ITexture>(texturePath, workingDir, ResourceFormat::AUTO, options));

		IntSize size = [&] {
			auto sizeAttribute = xml.FindAttribute("size");
			if (sizeAttribute) {
				return IntSize::parse(sizeAttribute->Value());
			} else {
				// TODO: load size for each atlas item separately
				throw InvalidDataException();
			}
		}();

		auto atlas = makeIntrusive<TextureAtlas>();
		atlas->init(texture.ref(), size);
		atlas->addReference();
		return atlas.get();
	}
}
