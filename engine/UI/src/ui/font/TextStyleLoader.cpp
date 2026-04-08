#include "ghuipch.h"
#include "TextStyleLoader.h"

#include "TextStyle.h"

namespace Ghurund::UI {
	KerningPairs loadKerning(const XMLElement& xml) {
		KerningPairs kerning;
		for (auto& child:xml.children) {
			if (child->name != L"Pair")
				throw InvalidFormatException("Kerning can only contain Pair children");
			uint32_t first = parse<uint32_t>(convertText<wchar_t, char>(child->attributes[L"first"]));
			uint32_t second = parse<uint32_t>(convertText<wchar_t, char>(child->attributes[L"second"]));
			int32_t value = parse<int32_t>(convertText<wchar_t, char>(child->attributes[L"value"]));
			kerning.add(first, second, value);
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

	void saveKerning(const KerningPairs& kerning, XMLDocument& document, XMLElement& xml) {
		/*for (auto first : kerning.kerning) {
			for (auto second : first.value) {
				auto pairElement = document.NewElement("Pair");
				xml.InsertEndChild(pairElement);
				pairElement->SetAttribute("first", first.key);
				pairElement->SetAttribute("second", second.key);
				pairElement->SetAttribute("value", second.value);
			}
		}*/
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

	CoroutineTask<void> TextStyleLoader::loadFromXml(TextStyle& textStyle, const XMLElement& xml, const DirectoryPath& workingDir) {
		IntrusivePointer<FontAtlas> atlas;
		FontMetrics fontMetrics = {};
		KerningPairs kerning;
		bool kerningFound = false;
		for (const auto& child : xml.children) {
			if (child->name == L"Atlas") {
				if (atlas != nullptr)
					throw InvalidFormatException("Atlas can appear only once in TextStyle");
				// TODO: load using resourceManager
				//IntrusivePointer<FontAtlas> atlas = co_await resourceManager.load<FontAtlas>(atlas.ref(), child.ref(), workingDir);
			} else if (child->name == L"Kerning") {
				if (kerningFound)
					throw InvalidFormatException("Kerning can appear only once in TextStyle");
				kerningFound = true;
				kerning = loadKerning(child.ref());
			} else if (child->name == L"FontMetrics") {
				if (fontMetrics.height != 0)
					throw InvalidFormatException("FontMetrics can appear only once in TextStyle");
				fontMetrics.ascent = parse<uint32_t>(convertText<wchar_t, char>(*child->findAttribute(L"ascent")));
				fontMetrics.descent = parse<uint32_t>(convertText<wchar_t, char>(*child->findAttribute(L"descent")));
				fontMetrics.height = parse<uint32_t>(convertText<wchar_t, char>(*child->findAttribute(L"height")));
				fontMetrics.weight = parse<uint32_t>(convertText<wchar_t, char>(*child->findAttribute(L"weight")));
				fontMetrics.italic = *child->findAttribute(L"italic") == L"true";
			}
		}
		textStyle.init(fontMetrics, atlas.ref(), kerning);
		co_return;
	}

	CoroutineTask<void> TextStyleLoader::loadFromBin(TextStyle& textStyle, MemoryInputStream& stream, const DirectoryPath& workingDir) const {
		FilePath path = FilePath(stream.readUnicode());
		IntrusivePointer<FontAtlas> atlas = co_await resourceManager.load<FontAtlas>(path, workingDir);
		auto kerning = loadKerning(stream);
		FontMetrics fontMetrics = *(FontMetrics*)stream.readBytes(sizeof(FontMetrics));
		textStyle.init(fontMetrics, atlas.ref(), kerning);
	}

	void TextStyleLoader::saveToXml(TextStyle& textStyle, XMLDocument& document, XMLElement& xml, const DirectoryPath& workingDir) const {
		/*auto atlasElement = document.NewElement("Atlas");
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
		fontMetricsElement->SetAttribute("italic", textStyle.FontMetrics.italic);*/
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

	CoroutineTask<void> TextStyleLoader::loadInternal(
		TextStyle& resource,
		MemoryInputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		if (format == ResourceFormat::AUTO) {
			auto position = stream.Position;
			try {
				XMLDocument doc;
				doc.parse(stream.Data, stream.Size);
				co_await loadFromXml(resource, doc.Root, workingDir);
				co_return;
			} catch (...) {
			}
			stream.Position = position;
			co_await loadFromBin(resource, stream, workingDir);
		} else if (format == TextStyle::FORMAT_XML) {
			XMLDocument doc;
			doc.parse(stream.Data, stream.Size);
			co_await loadFromXml(resource, doc.Root, workingDir);
		} else {
			co_await loadFromBin(resource, stream, workingDir);
		}
		co_return;
	}

	void TextStyleLoader::saveInternal(
		TextStyle& resource,
		MemoryOutputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		SaveOption options
	) const {
		/*TextStyle& textStyle = castResource<TextStyle>(resource);
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
		}*/
	}
}