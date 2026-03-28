#include "ghuipch.h"
#include "FontAtlasLoader.h"

#include "core/math/Int.h"
#include "core/math/Float.h"
#include "core/math/Size.h"

namespace Ghurund::UI {
	void FontAtlasLoader::loadFromBin(MemoryInputStream& stream, const DirectoryPath& workingDir, FontAtlas& fontAtlas) {
		FilePath path = FilePath(stream.readUnicode());
		auto image = IntrusivePointer<Image>(resourceManager.load<Image>(path, workingDir, ResourceFormat::AUTO));

		size_t glyphCount = stream.readUInt64();
		Map<wchar_t, GlyphMetrics> glyphs;
		for (size_t i = 0; i < glyphCount; i++) {
			wchar_t c = stream.readUInt32();
			GlyphMetrics g = stream.read<GlyphMetrics>();
			glyphs.put(c, g);
		}

		fontAtlas.init(image.ref(), glyphs);
	}

	void FontAtlasLoader::loadFromXml(const XMLElement& xml, const DirectoryPath& workingDir, FontAtlas& fontAtlas) {
		FilePath path = FilePath(*xml.findAttribute(L"image"));
		auto image = IntrusivePointer<Image>(resourceManager.load<Image>(path, workingDir, ResourceFormat::AUTO));

		Map<wchar_t, GlyphMetrics> glyphs;
		for(const auto& child: xml.children) {
			if (child->name == L"Glyph") {
				auto cAttribute = child->findAttribute(L"c");
				auto shapeSizeAttribute = child->findAttribute(L"shapeSize");
				auto bitmapSizeAttribute = child->findAttribute(L"bitmapSize");
				auto shapeOriginAttribute = child->findAttribute(L"shapeOrigin");
				auto bitmapPosAttribute = child->findAttribute(L"bitmapPos");
				auto scaleAttribute = child->findAttribute(L"scale");
				auto incrementAttribute = child->findAttribute(L"increment");
				if (cAttribute && shapeSizeAttribute &&
					bitmapSizeAttribute && shapeOriginAttribute &&
					bitmapPosAttribute && scaleAttribute &&
					incrementAttribute) {
					wchar_t c = parse<uint32_t>(convertText<wchar_t, char>(*cAttribute));
					auto shapeSize = parse<IntSize>(convertText<wchar_t, char>(*shapeSizeAttribute));
					auto bitmapSize = parse<IntSize>(convertText<wchar_t, char>(*bitmapSizeAttribute));
					auto shapeOrigin = parse<XMINT2>(convertText<wchar_t, char>(*shapeOriginAttribute));
					auto bitmapPos = parse<XMINT2>(convertText<wchar_t, char>(*bitmapPosAttribute));
					auto scale = parse<float>(convertText<wchar_t, char>(*scaleAttribute));
					auto increment = parse<uint16_t>(convertText<wchar_t, char>(*incrementAttribute));
					glyphs.put(c, { shapeSize, bitmapSize, shapeOrigin, bitmapPos, scale, increment });
				}
			}
		}

		fontAtlas.init(image.ref(), glyphs);
	}

	void FontAtlasLoader::saveToXml(FontAtlas& atlas, XMLDocument& document, XMLElement& xml, const DirectoryPath& workingDir) const {
		// resourceManager.save(*atlas.Image, workingDir);
		/*xml.SetAttribute("image", atlas.Image->Path);
		for (auto& glyph : atlas.Glyphs) {
			auto glyphElement = document.NewElement("Glyph");
			xml.InsertEndChild(glyphElement);
			glyphElement->SetAttribute("c", glyph.key);
			glyphElement->SetAttribute("shapeSize", glyph.value.shapeSize.toString().Data);
			glyphElement->SetAttribute("bitmapSize", glyph.value.bitmapSize.toString().Data);
			glyphElement->SetAttribute("shapeOrigin", Ghurund::Core::toString(glyph.value.shapeOrigin).Data);
			glyphElement->SetAttribute("bitmapPos", Ghurund::Core::toString(glyph.value.bitmapPos).Data);
			glyphElement->SetAttribute("scale", glyph.value.scale);
			glyphElement->SetAttribute("increment", glyph.value.increment);
		}*/
	}

	void FontAtlasLoader::saveToBin(FontAtlas& atlas, MemoryOutputStream& stream, const DirectoryPath& workingDir) const {
		DirectoryPath localDir = [&] {
			if (atlas.Path) {
				return ResourceManager::getLocalDir(*atlas.Path, workingDir);
			} else {
				return workingDir;
			}
		}();
		FilePath path = [&] {
			if (!atlas.Image->Path && atlas.Path) {
				auto pathStr = std::format(L"{}{}", atlas.Path->FileName.substring(0, atlas.Path->FileName.findLast(L'.')).Data, L".png");
				return FilePath(pathStr.c_str());
			} else if (atlas.Image->Path) {
				return *atlas.Image->Path;
			} else {
				Logger::log(LogType::ERR0R, _T("Font atlas could not be saved, because its path is null.\n"));
				throw InvalidDataException();
			}
		}();
		stream.writeUnicode(path.toString());
		resourceManager.save(*atlas.Image, path, localDir);
		stream.writeUInt64(atlas.Glyphs.Size);
		for (auto& glyph : atlas.Glyphs) {
			stream.writeUInt32(glyph.key);
			stream.write(glyph.value);
		}
	}

	void FontAtlasLoader::loadInternal(
		FontAtlas& resource,
		MemoryInputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		if (format == ResourceFormat::AUTO) {
			XMLDocument doc;
			try{
				doc.parse(stream.Data, stream.Size);
				loadFromXml(doc.Root, workingDir, resource);
			} catch(...) {
				loadFromBin(stream, workingDir, resource);
			}
		} else if (format == FontAtlas::FORMAT_XML) {
			XMLDocument doc;
			doc.parse(stream.Data, stream.Size);
			loadFromXml(doc.Root, workingDir, resource);
		} else {
			loadFromBin(stream, workingDir, resource);
		}
	}

	void FontAtlasLoader::saveInternal(
		FontAtlas& resource,
		MemoryOutputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		SaveOption options
	) const {
		if (format == ResourceFormat::AUTO || format == FontAtlas::FORMAT_XML) {
			//saveToXml(fontAtlas, document, xml, workingDir);
		} else {
			saveToBin(resource, stream, workingDir);
		}
	}
}