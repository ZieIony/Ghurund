#pragma once

#include "FontAtlasLoader.h"
#include "TextStyle.h"

#include "core/resource/Loader.h"

#include <tinyxml2.h>

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	class TextStyleLoader:public Loader {
	private:
		ResourceManager& resourceManager;
		FontAtlasLoader& fontAtlasLoader;

		TextStyle* loadFromXml(const tinyxml2::XMLElement& xml, const DirectoryPath& workingDir);

		TextStyle* loadFromBin(MemoryInputStream& stream, const DirectoryPath& workingDir) const;

		void saveToXml(TextStyle& textStyle, tinyxml2::XMLDocument& document, tinyxml2::XMLElement& xml, const DirectoryPath& workingDir) const;

		void saveToBin(TextStyle& textStyle, MemoryOutputStream& stream, const DirectoryPath& workingDir) const;

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
		TextStyleLoader(
			ResourceManager& resourceManager,
			FontAtlasLoader& fontAtlasLoader
		):resourceManager(resourceManager), fontAtlasLoader(fontAtlasLoader) {}
	};
}