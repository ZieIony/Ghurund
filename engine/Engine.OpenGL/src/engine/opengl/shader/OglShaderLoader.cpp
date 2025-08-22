#include "gheoglpch.h"
#include "OglShaderLoader.h"

#include <tinyxml2.h>

namespace Ghurund::Engine::OpenGL {
	SharedPointer<OglShaderProgram> OglShaderLoader::loadShaderProgramFromXml(const tinyxml2::XMLElement& xml, const OglShaderType& shaderType) {
		const tinyxml2::XMLElement* vertexElement = xml.FirstChildElement(shaderType.TypeName.Data);
		if (!vertexElement)
			throw InvalidFormatException();
		const tinyxml2::XMLAttribute* vertexPath = vertexElement->FindAttribute("path");
		if (vertexPath) {
			FilePath shaderFilePath = FilePath(convertText<char, wchar_t>(AString(vertexPath->Value())));
			File shaderFile = shaderFilePath;
			if (!shaderFile.Exists)
				throw InvalidFormatException();
			Buffer shaderContents;
			shaderFile.read(shaderContents);
			AString sourceCode((const char*)shaderContents.Data, shaderContents.Size);
			return SharedPointer<OglShaderProgram>(compiler.compile(sourceCode, shaderType));
		} else {
			AString sourceCode = vertexElement->GetText();
			return SharedPointer<OglShaderProgram>(compiler.compile(sourceCode, shaderType));
		}
	}

	OglShader* OglShaderLoader::loadXml(const tinyxml2::XMLElement& xml) {
		if (AString("Shader") != xml.Name())
			throw InvalidFormatException();

		auto vertexProgram = loadShaderProgramFromXml(xml, OglShaderType::VERTEX);
		auto fragmentProgram = loadShaderProgramFromXml(xml, OglShaderType::FRAGMENT);
		auto shader = compiler.build(vertexProgram, fragmentProgram);
		return &shader;
		//bool supportsTransparency = sourceCode.find("supportsTransparency") != sourceCode.Size;
	}

	Resource* OglShaderLoader::loadInternal(
		NotNull<MemoryInputStream> stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		AString streamContents = stream->readASCII();
		tinyxml2::XMLDocument document;
		document.Parse(streamContents.Data);
		const tinyxml2::XMLElement* root = document.RootElement();
		if(!root)
			throw InvalidFormatException();
		return loadXml(*root);
	}

	void OglShaderLoader::saveInternal(
		NotNull<MemoryOutputStream> stream,
		const DirectoryPath& workingDir,
		Resource& resource,
		const ResourceFormat& format,
		SaveOption options
	) const {
		OglShader& shader = castResource<OglShader>(resource);

		writeHeader<OglShader>(stream);

		//stream.writeASCII(shader.sourceCode);
	}
}
