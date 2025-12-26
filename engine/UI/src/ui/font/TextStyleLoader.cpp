#include "ghuipch.h"
#include "TextStyleLoader.h"

#include "TextStyle.h"

#include <tinyxml2.h>

namespace Ghurund::UI {
	KerningPairs loadKerning(const tinyxml2::XMLElement& xml) {
		KerningPairs kerning;
		const tinyxml2::XMLElement* child = xml.FirstChildElement();
		while (child) {
			if (child->Name() != AString("Pair"))
				throw InvalidFormatException("Kerning can only contain Pair children");
			tchar first = child->FindAttribute("first")->UnsignedValue();
			tchar second = child->FindAttribute("second")->UnsignedValue();
			int value = child->FindAttribute("value")->IntValue();
			kerning.add(first, second, value);
			child = child->NextSiblingElement();
		}
		return kerning;
	}

	KerningPairs loadKerning(MemoryInputStream& stream) {
		KerningPairs kerning;
		while (true) {
			tchar first = stream.readUInt32();
			if (first == 0)
				return kerning;
			tchar second = stream.readUInt32();
			int16_t value = stream.readInt32();
			kerning.add(first, second, value);
		}
	}

	void saveKerning(const KerningPairs& kerning, tinyxml2::XMLDocument& document, tinyxml2::XMLElement& xml) {
		for (auto first : kerning.kerning) {
			for (auto second : first.value) {
				auto pairElement = document.NewElement("Pair");
				xml.InsertEndChild(pairElement);
				pairElement->SetAttribute("first", first.key);
				pairElement->SetAttribute("second", second.key);
				pairElement->SetAttribute("value", second.value);
			}
		}
	}

	void saveKerning(const KerningPairs& kerning, MemoryOutputStream& stream) {
		for (auto first : kerning.kerning) {
			for (auto second : first.value) {
				stream.writeUInt32(first.key);
				stream.writeUInt32(second.key);
				stream.writeInt32(second.value);
			}
		}
		stream.writeUInt32(0);
	}

	TextStyle* TextStyleLoader::loadFromXml(const tinyxml2::XMLElement& xml, const DirectoryPath& workingDir) {
		auto textStyle = makeIntrusive<TextStyle>();
		const tinyxml2::XMLElement* child = xml.FirstChildElement();
		IntrusivePointer<FontAtlas> atlas;
		FontMetrics fontMetrics = {};
		KerningPairs kerning;
		bool kerningFound = false;
		while (child) {
			if (child->Name() == AString("Atlas")) {
				if (atlas != nullptr)
					throw InvalidFormatException("Atlas can appear only once in TextStyle");
				IntrusivePointer<FontAtlas> atlas = IntrusivePointer<FontAtlas>(fontAtlasLoader.loadFromXml(*child, workingDir));
			} else if (child->Name() == AString("Kerning")) {
				if (kerningFound)
					throw InvalidFormatException("Kerning can appear only once in TextStyle");
				kerningFound = true;
				kerning = loadKerning(*child);
			} else if (child->Name() == AString("FontMetrics")) {
				if (fontMetrics.height != 0)
					throw InvalidFormatException("FontMetrics can appear only once in TextStyle");
				fontMetrics.ascent = child->FindAttribute("ascent")->UnsignedValue();
				fontMetrics.descent = child->FindAttribute("descent")->UnsignedValue();
				fontMetrics.height = child->FindAttribute("height")->UnsignedValue();
				fontMetrics.weight = child->FindAttribute("weight")->UnsignedValue();
				fontMetrics.italic = child->FindAttribute("italic")->BoolValue();
			}
			child = child->NextSiblingElement();
		}
		textStyle->init(fontMetrics, atlas.ref(), kerning);
		textStyle->addReference();
		return textStyle.get();
	}

	TextStyle* TextStyleLoader::loadFromBin(MemoryInputStream& stream, const DirectoryPath& workingDir) const {
		auto textStyle = makeIntrusive<TextStyle>();
		FilePath path = FilePath(stream.readUnicode());
		IntrusivePointer<FontAtlas> atlas = IntrusivePointer<FontAtlas>(resourceManager.load<FontAtlas>(path, workingDir));
		auto kerning = loadKerning(stream);
		FontMetrics fontMetrics = *(FontMetrics*)stream.readBytes(sizeof(FontMetrics));
		textStyle->init(fontMetrics, atlas.ref(), kerning);
		textStyle->addReference();
		return textStyle.get();
	}

	void TextStyleLoader::saveToXml(TextStyle& textStyle, tinyxml2::XMLDocument& document, tinyxml2::XMLElement& xml, const DirectoryPath& workingDir) const {
		auto atlasElement = document.NewElement("Atlas");
		xml.InsertEndChild(atlasElement);
		fontAtlasLoader.saveToXml(*textStyle.Atlas, document, *atlasElement, workingDir);

		auto kerningElement = document.NewElement("Kerning");
		xml.InsertEndChild(kerningElement);
		saveKerning(textStyle.Kerning, document, *kerningElement);

		auto fontMetricsElement = document.NewElement("FontMetrics");
		xml.InsertEndChild(fontMetricsElement);
		fontMetricsElement->SetAttribute("ascent", textStyle.FontMetrics.ascent);
		fontMetricsElement->SetAttribute("descent", textStyle.FontMetrics.descent);
		fontMetricsElement->SetAttribute("height", textStyle.FontMetrics.height);
		fontMetricsElement->SetAttribute("weight", textStyle.FontMetrics.weight);
		fontMetricsElement->SetAttribute("italic", textStyle.FontMetrics.italic);
	}

	void TextStyleLoader::saveToBin(TextStyle& textStyle, MemoryOutputStream& stream, const DirectoryPath& workingDir) const {
		DirectoryPath localDir = [&] {
			if (textStyle.Path) {
				return ResourceManager::getLocalDir(*textStyle.Path, workingDir);
			} else {
				return workingDir;
			}
		}();
		FilePath path = [&] {
			if (!textStyle.Atlas->Path && textStyle.Path) {
				auto pathStr = std::format(L"{}{}", textStyle.Path->FileName.substring(0, textStyle.Path->FileName.findLast(L'.')).Data, L"_atlas.bin");
				return FilePath(pathStr.c_str());
			} else if (textStyle.Atlas->Path) {
				return *textStyle.Atlas->Path;
			} else {
				Logger::log(LogType::ERR0R, _T("Font atlas could not be saved, because its path is null.\n"));
				throw InvalidDataException();
			}
		}();
		stream.writeUnicode(path.toString());
		resourceManager.save(*textStyle.Atlas, path, localDir, FontAtlas::FORMAT_BIN);
		saveKerning(textStyle.Kerning, stream);
		stream.writeBytes(&textStyle.FontMetrics, sizeof(FontMetrics));
	}

	Resource* TextStyleLoader::loadInternal(
		MemoryInputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		if (format == ResourceFormat::AUTO) {
			tinyxml2::XMLDocument doc;
			auto error = doc.Parse(AString((const char*)stream.Data, stream.Size).Data);
			if (error == tinyxml2::XML_SUCCESS) {
				return loadFromXml(*doc.RootElement(), workingDir);
			} else {
				return loadFromBin(stream, workingDir);
			}
		} else if (format == TextStyle::FORMAT_XML) {
			tinyxml2::XMLDocument doc;
			doc.Parse(AString((const char*)stream.Data, stream.Size).Data);
			return loadFromXml(*doc.RootElement(), workingDir);
		} else {
			return loadFromBin(stream, workingDir);
		}
	}

	void TextStyleLoader::saveInternal(
		MemoryOutputStream& stream,
		const DirectoryPath& workingDir,
		Resource& resource,
		const ResourceFormat& format,
		SaveOption options
	) const {
		TextStyle& textStyle = castResource<TextStyle>(resource);
		if (format == ResourceFormat::AUTO || format == TextStyle::FORMAT_XML) {
			tinyxml2::XMLDocument xml;
			auto element = xml.NewElement("TextStyle");
			xml.InsertEndChild(element);

			saveToXml(textStyle, xml, *element, workingDir);
			tinyxml2::XMLPrinter printer;
			xml.Print(&printer);
			stream.writeBytes(printer.CStr(), printer.CStrSize());
		} else {
			saveToBin(textStyle, stream, workingDir);
		}
	}
}