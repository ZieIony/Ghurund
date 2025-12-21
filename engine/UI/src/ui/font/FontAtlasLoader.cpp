#include "ghuipch.h"
#include "FontAtlasLoader.h"

#include "core/math/Int.h"
#include "core/math/Float.h"
#include "core/math/Size.h"

namespace Ghurund::UI {
	FontAtlas* FontAtlasLoader::loadFromBin(MemoryInputStream& stream, const DirectoryPath& workingDir) {
		ResourcePath path = ResourcePath::parse(stream.readUnicode());
		auto image = IntrusivePointer<Image>(resourceManager.load<Image>(path, workingDir, ResourceFormat::AUTO));

		size_t glyphCount = stream.readUInt64();
		Map<wchar_t, GlyphMetrics> glyphs;
		for(size_t i=0;i<glyphCount;i++){
			wchar_t c = stream.readUInt32();
			GlyphMetrics g = stream.read<GlyphMetrics>();
			glyphs.put(c, g);
		}

		auto atlas = makeIntrusive<FontAtlas>();
		atlas->init(image.ref(), glyphs);
		atlas->addReference();
		return atlas.get();
	}

	FontAtlas* FontAtlasLoader::loadFromXml(const tinyxml2::XMLElement& xml, const DirectoryPath& workingDir) {
		AString s = xml.FindAttribute("image")->Value();
		s.replace(L'\\', L'/');
		ResourcePath path = ResourcePath::parse(convertText<char, wchar_t>(s));
		auto image = IntrusivePointer<Image>(resourceManager.load<Image>(path, workingDir, ResourceFormat::AUTO));

		const tinyxml2::XMLElement* child = xml.FirstChildElement();
		Map<wchar_t, GlyphMetrics> glyphs;
		while (child) {
			if (child->Name() == AString("Glyph")) {
				auto cAttribute = child->FindAttribute("c");
				auto shapeSizeAttribute = child->FindAttribute("shapeSize");
				auto bitmapSizeAttribute = child->FindAttribute("bitmapSize");
				auto shapeOriginAttribute = child->FindAttribute("shapeOrigin");
				auto bitmapPosAttribute = child->FindAttribute("bitmapPos");
				auto scaleAttribute = child->FindAttribute("scale");
				auto incrementAttribute = child->FindAttribute("increment");
				if (cAttribute && shapeSizeAttribute &&
					bitmapSizeAttribute && shapeOriginAttribute &&
					bitmapPosAttribute && scaleAttribute &&
					incrementAttribute) {
					wchar_t c = parse<uint32_t>(cAttribute->Value());
					auto shapeSize = parse<IntSize>(shapeSizeAttribute->Value());
					auto bitmapSize = parse<IntSize>(bitmapSizeAttribute->Value());
					auto shapeOrigin = parse<XMINT2>(shapeOriginAttribute->Value());
					auto bitmapPos = parse<XMINT2>(bitmapPosAttribute->Value());
					auto scale = parse<float>(scaleAttribute->Value());
					auto increment = parse<uint16_t>(incrementAttribute->Value());
					glyphs.put(c, { shapeSize, bitmapSize, shapeOrigin, bitmapPos, scale, increment });
				}
			}
			child = child->NextSiblingElement();
		}

		auto atlas = makeIntrusive<FontAtlas>();
		atlas->init(image.ref(), glyphs);
		atlas->addReference();
		return atlas.get();
	}

	void FontAtlasLoader::saveToXml(FontAtlas& atlas, tinyxml2::XMLDocument& document, tinyxml2::XMLElement& xml, const DirectoryPath& workingDir) const {
		// resourceManager.save(*atlas.Image, workingDir);
		xml.SetAttribute("image", atlas.Image->Path);
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
		}
	}

	void FontAtlasLoader::saveToBin(FontAtlas& atlas, MemoryOutputStream& stream, const DirectoryPath& workingDir) const {
		// resourceManager.save(*atlas.Image, workingDir);
		stream.writeUnicode(atlas.Image->Path->toString());
		stream.writeUInt64(atlas.Glyphs.Size);
		for (auto& glyph : atlas.Glyphs) {
			stream.writeUInt32(glyph.key);
			stream.write(glyph.value);
		}
	}

	Resource* FontAtlasLoader::loadInternal(
		MemoryInputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		AString xmlString((const char*)stream.Data, stream.Size);
		tinyxml2::XMLDocument doc;
		doc.Parse(xmlString.Data);
		return loadFromXml(*doc.RootElement(), workingDir);
	}

	void FontAtlasLoader::saveInternal(
		MemoryOutputStream& stream,
		const DirectoryPath& workingDir,
		Resource& resource,
		const ResourceFormat& format,
		SaveOption options
	) const {
		FontAtlas& fontAtlas = castResource<FontAtlas>(resource);
		if (format == ResourceFormat::AUTO || format == FontAtlas::FORMAT_XML) {
			//saveToXml(fontAtlas, document, xml, workingDir);
		} else {
			saveToBin(fontAtlas, stream, workingDir);
		}
	}
}