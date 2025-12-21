#pragma once

#include "FontAtlas.h"

#include "core/resource/Loader.h"

#include <tinyxml2.h>

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	class FontAtlasLoader:public Loader {
	private:
		ResourceManager& resourceManager;

	protected:
		virtual Resource* loadInternal(
			MemoryInputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOption options
		) override;

		virtual void saveInternal(
			MemoryOutputStream& stream,
			const DirectoryPath& workingDir,
			Resource& resource,
			const ResourceFormat& format,
			SaveOption options
		) const override;

	public:
		FontAtlasLoader(ResourceManager& resourceManager):resourceManager(resourceManager) {}

		FontAtlas* loadFromBin(MemoryInputStream& stream, const DirectoryPath& workingDir);

		FontAtlas* loadFromXml(const tinyxml2::XMLElement& xml, const DirectoryPath& workingDir);

		void saveToXml(FontAtlas& atlas, tinyxml2::XMLDocument& document, tinyxml2::XMLElement& xml, const DirectoryPath& workingDir) const;

		void saveToBin(FontAtlas& atlas, MemoryOutputStream& stream, const DirectoryPath& workingDir) const;
	};
}