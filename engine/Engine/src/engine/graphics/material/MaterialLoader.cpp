#include "ghepch.h"
#include "MaterialLoader.h"

namespace Ghurund::Engine {
	CoroutineTask<void> MaterialLoader::onLoadParameter(Material& material, const DirectoryPath& workingDir, MaterialInput& input, const AString& value) {
		if (input.Type == InputType::TEXTURE) {
			TextureInput& colorTextureInput = (TextureInput&)input;
			FilePath texturePath = FilePath(convertText<char, wchar_t>(value));
			auto texture = co_await resourceManager.load<ITexture>(texturePath, workingDir);
			colorTextureInput.Value = texture.get();
		} else if (input.Type == InputType::FLOAT4) {
			Float4Input& float4Input = (Float4Input&)input;
			// TODO: load theme attributes or do binding
			if (value.startsWith("#"))
				float4Input.Value = Color::parse(value).toVector();
		}
		co_return;
	}

	CoroutineTask<void> MaterialLoader::loadInternal(
		Material& resource,
		const XMLElement& xml,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		checkXmlRoot(xml, L"Material");
	
		WString* s = xml.findAttribute(L"shader");
		FilePath path = FilePath(*s);
		auto shader = co_await resourceManager.load<Shader>(path, workingDir, ResourceFormat::AUTO, LoadOption::DONT_CACHE);
		resource.init(memoryManager);
		resource.Shader = shader.get();
		for(const auto& child:xml.children){
			if (child->name == L"Parameter") {
				auto nameAttribute = child->findAttribute(L"name");
				auto valueAttribute = child->findAttribute(L"value");
				if (nameAttribute && valueAttribute) {
					AString name = convertText<wchar_t, char>(*nameAttribute);
					auto input = resource.getInputs().get(name);
					if (!input) {
						auto text = std::format(_T("Shader {} doesn't specify an input named '{}'\n"), path.toString(), convertText<char, tchar>(name));
						Logger::log(LogType::WARNING, text.c_str());
					} else {
						AString value = convertText<wchar_t, char>(*valueAttribute);
						co_await onLoadParameter(resource, workingDir, *input, value);
					}
				}
			}
		}
	}

	void MaterialLoader::saveInternal(
		Material& resource,
		MemoryOutputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		SaveOption options
	) const {
		//shaderLoader.save(stream, workingDir, *material.Shader, format, options);
	}
}