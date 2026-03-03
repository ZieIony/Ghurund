#include "ghe2dpch.h"
#include "SpriteAnimationSetLoader.h"

namespace Ghurund::Engine::_2D {
	SpriteAnimationSet* SpriteAnimationSetLoader::loadFromXmlInternal(
		const tinyxml2::XMLElement& xml,
		const DirectoryPath& workingDir,
		LoadOption options
	) {
		auto animationSet = makeIntrusive<SpriteAnimationSet>();
		auto animationElement = xml.FirstChildElement("SpriteAnimation");
		while (animationElement) {
			auto nameAttribute = animationElement->FindAttribute("name");
			auto animation = makeIntrusive<SpriteAnimation>();
			if (nameAttribute)
				animation->Name = AString(nameAttribute->Value());
			auto frameElement = animationElement->FirstChildElement("SpriteAnimationFrame");
			while (frameElement) {
				auto textureAttribute = frameElement->FindAttribute("texture");
				if (!textureAttribute)
					throw InvalidFormatException();
				auto durationMsAttribute = frameElement->FindAttribute("durationMs");
				if (!durationMsAttribute)
					throw InvalidFormatException();
				auto texturePath = FilePath(convertText<char, wchar_t>(AString(textureAttribute->Value())));
				auto texture = IntrusivePointer<ITexture>(resourceManager.load<ITexture>(texturePath, workingDir, ResourceFormat::AUTO, options));
				animation->addFrame(texture.ref(), (uint64_t)durationMsAttribute->Int64Value());
				frameElement = frameElement->NextSiblingElement();
			}
			animationSet->add(animation.get());
			animationElement = animationElement->NextSiblingElement();
		}
		animationSet->addReference();
		return animationSet.get();
	}

	Resource* SpriteAnimationSetLoader::loadInternal(
		MemoryInputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		return loadFromXml<SpriteAnimationSet>(stream, workingDir, options);
	}

	void SpriteAnimationSetLoader::saveInternal(
		MemoryOutputStream& stream,
		const DirectoryPath& workingDir,
		Resource& resource,
		const ResourceFormat& format,
		SaveOption options
	) const {
		SpriteAnimationSet& animationSet = castResource<SpriteAnimationSet>(resource);
		tinyxml2::XMLDocument document;
		auto root = document.NewElement("SpriteAnimationSet");
		root->SetAttribute("version", SpriteAnimationSet::VERSION);
		for (auto& animation : animationSet) {
			auto animationElement = root->InsertNewChildElement("SpriteAnimation");
			if (animation->Name)
				animationElement->SetAttribute("name", animation->Name);
			for (auto& frame : animation->Frames) {
				auto frameElement = animationElement->InsertNewChildElement("SpriteAnimationFrame");
				frameElement->SetAttribute("texture", convertText<wchar_t, char>(frame.texture->Path->toString()).Data);
				frameElement->SetAttribute("durationMs", (long long)frame.durationMs);
			}
		}
		tinyxml2::XMLPrinter printer = {};
		tinyxml2::DynArray< char, 20 > _buffer;
		document.Print(&printer);
		stream.writeBytes(printer.CStr(), printer.CStrSize());
	}
}
