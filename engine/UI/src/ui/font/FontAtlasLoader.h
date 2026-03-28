#pragma once

#include "FontAtlas.h"

#include "core/loading/Loader.h"

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	class FontAtlasLoader:public Loader<FontAtlas> {
	private:
		ResourceManager& resourceManager;

	protected:
		virtual void loadInternal(
			FontAtlas& resource,
			MemoryInputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOption options
		) override;

		virtual void saveInternal(
			FontAtlas& resource,
			MemoryOutputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			SaveOption options
		) const override;

	public:
		FontAtlasLoader(ResourceManager& resourceManager):resourceManager(resourceManager) {}

		void loadFromBin(MemoryInputStream& stream, const DirectoryPath& workingDir, FontAtlas& fontAtlas);

		void loadFromXml(const XMLElement& xml, const DirectoryPath& workingDir, FontAtlas& fontAtlas);

		void saveToXml(FontAtlas& atlas, XMLDocument& document, XMLElement& xml, const DirectoryPath& workingDir) const;

		void saveToBin(FontAtlas& atlas, MemoryOutputStream& stream, const DirectoryPath& workingDir) const;
	};
}
