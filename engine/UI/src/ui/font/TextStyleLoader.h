#pragma once

#include "FontAtlasLoader.h"
#include "TextStyle.h"

#include "core/loading/Loader.h"
#include <core/xml/XMLElement.h>

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	class TextStyleLoader:public Loader<TextStyle> {
	private:
		ResourceManager& resourceManager;

		CoroutineTask<void> loadFromXml(TextStyle& textStyle, const XMLElement& xml, const DirectoryPath& workingDir);

		CoroutineTask<void> loadFromBin(TextStyle& textStyle, MemoryInputStream& stream, const DirectoryPath& workingDir) const;

		void saveToXml(TextStyle& textStyle, XMLDocument& document, XMLElement& xml, const DirectoryPath& workingDir) const;

		void saveToBin(TextStyle& textStyle, MemoryOutputStream& stream, const DirectoryPath& workingDir) const;

	protected:
		virtual CoroutineTask<void> loadInternal(
			TextStyle& resource,
			MemoryInputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOption options
		) override;

		virtual void saveInternal(
			TextStyle& resource,
			MemoryOutputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			SaveOption options
		) const override;

	public:
		TextStyleLoader(ResourceManager& resourceManager):resourceManager(resourceManager) {}
	};
}
