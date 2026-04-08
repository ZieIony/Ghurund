#include "gheoglpch.h"
#include "OglShaderLoader.h"

namespace Ghurund::Engine::OpenGL {
	SharedPointer<OglShaderProgram> OglShaderLoader::loadShaderProgramFromXml(
		const XMLElement& xml,
		const DirectoryPath& workingDir,
		const OglShaderType& shaderType
	) {
		auto vertexElement = xml.findElement(convertText<char, wchar_t>(shaderType.TypeName));
		if (!vertexElement)
			throw InvalidFormatException();
		const WString* vertexPath = vertexElement->findAttribute(L"path");
		if (vertexPath) {
			FilePath shaderFilePath = workingDir / FilePath(*vertexPath);
			File shaderFile = shaderFilePath;
			if (!shaderFile.Exists)
				throw InvalidFormatException();
			Buffer shaderContents;
			shaderFile.read(shaderContents);
			AString sourceCode((const char*)shaderContents.Data, shaderContents.Size);
			return SharedPointer<OglShaderProgram>(compiler.compile(sourceCode, shaderType));
		} else {
			AString sourceCode = convertText<wchar_t, char>(vertexElement->value);
			return SharedPointer<OglShaderProgram>(compiler.compile(sourceCode, shaderType));
		}
	}

	CoroutineTask<void> OglShaderLoader::loadInternal(
		OglShader& resource,
		const XMLElement& xml,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		LoadOption options
	) {
		checkXmlRoot(xml, L"Shader");

		auto vertexProgram = loadShaderProgramFromXml(xml, workingDir, OglShaderType::VERTEX);
		auto fragmentProgram = loadShaderProgramFromXml(xml, workingDir, OglShaderType::FRAGMENT);
		compiler.build(resource, *vertexProgram.get(), *fragmentProgram.get());
		//bool isTransparencyEnabled = sourceCode.find("isTransparencyEnabled") != sourceCode.Size;
		co_return;
	}

	void OglShaderLoader::saveInternal(
		OglShader& resource,
		MemoryOutputStream& stream,
		const DirectoryPath& workingDir,
		const ResourceFormat& format,
		SaveOption options
	) const {
		writeHeader<OglShader>(stream);

		//stream.writeASCII(shader.sourceCode);
	}
}
