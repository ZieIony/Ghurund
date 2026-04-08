#include "ghe2dpch.h"
#include "SpriteAnimationSetLoader.h"

namespace Ghurund::Engine::_2D {
	CoroutineTask<void> SpriteAnimationSetLoader::loadInternal(
		SpriteAnimationSet& resource,
		const XMLElement& xml,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		checkXmlRoot(xml, L"SpriteAnimationSet");
	
		for (const auto& animationElement : xml.children) {
			auto nameAttribute = animationElement->findAttribute(L"name");
			auto animation = makeIntrusive<SpriteAnimation>();
			if (nameAttribute)
				animation->Name = *nameAttribute;
			for(const auto& frameElement : animationElement->children){
				auto textureAttribute = frameElement->findAttribute(L"texture");
				if (!textureAttribute)
					throw InvalidFormatException();
				auto durationMsAttribute = frameElement->findAttribute(L"durationMs");
				if (!durationMsAttribute)
					throw InvalidFormatException();
				auto texturePath = FilePath(*textureAttribute);
				auto texture = co_await resourceManager.load<ITexture>(texturePath, workingDir, ResourceFormat::AUTO, options);
				animation->addFrame(texture.ref(), parse<uint32_t>(convertText<wchar_t, char>(*durationMsAttribute)));
			}
			resource.add(animation.get());
		}
	}

	void SpriteAnimationSetLoader::saveInternal(
		SpriteAnimationSet& resource,
		MemoryOutputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		SaveOption options
	) const {
		/*tinyxml2::XMLDocument document;
		auto root = document.NewElement("SpriteAnimationSet");
		root->SetAttribute("version", SpriteAnimationSet::VERSION);
		for (auto& animation : resource) {
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
		stream.writeBytes(printer.CStr(), printer.CStrSize());*/
	}
}
