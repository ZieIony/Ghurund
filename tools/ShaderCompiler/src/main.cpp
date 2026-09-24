#include "core/application/CommandLine.h"
#include "core/logging/Logger.h"
#include "core/logging/CallbackLogOutput.h"
#include "core/object/IntrusivePointer.h"
#include "engine/directx/DxGraphics.h"
#include "engine/directx/shader/compiler/DxCompilationException.h"
#include "engine/directx/shader/compiler/DxShaderCompiler.h"
#include "engine/directx/shader/DxShaderLoader.h"
#include "Ghurund.Engine.h"

using namespace Ghurund::Core;
using namespace Ghurund::Engine::DirectX;

int main() {
	CommandLine commandLine;
	Logger::init(std::unique_ptr<LogOutput>(ghnew CallbackLogOutput([](const Log& log) {
		_tprintf(log.message.Data);
	})));
	if (commandLine.Arguments.Size == 1) {
		Logger::print(LogType::WARNING, _T("Shader file path is required.\n"));
		return 1;
	}
	AString filePathArgument = commandLine.Arguments[1];
	filePathArgument.removeAll("\"");
	if (!filePathArgument.endsWith(".hlsl") && !filePathArgument.endsWith(".xml")) {
		auto message = std::format(_T("The provided file path ('{}') doesn't seem to be neither shader file path or shader program file path.\n"), filePathArgument);
		Logger::print(LogType::WARNING, message.c_str());
		return 2;
	}

	Timer timer;
	CoroutineThreadPool threadPool = CoroutineThreadPool(4);
	CoroutineScheduler coroutineScheduler = Ghurund::Core::CoroutineScheduler(threadPool, timer);
	ResourceManager resourceManager = ResourceManager(coroutineScheduler);
	DxGraphics graphics;
	graphics.init();
	DxShaderCompiler compiler(graphics);

	FilePath filePath = FilePath(convertText<char, wchar_t>(filePathArgument));
	File file(filePath);
	Buffer buffer;
	file.read(buffer);
	if (filePath.Extension == L"hlsl") {
		try {
			AString sourceCode = AString((const char*)buffer.Data, buffer.Size);
			AString sourceName = convertText<wchar_t, char>(filePath.toString());
			List<DirectoryPath> includeDirs;
			includeDirs.add(ResourceManager::ENGINE_LIB_PATH / DirectoryPath(L"/resources/shaders/DirectX/include"));
			CompilerInclude include(resourceManager, filePath.Directory, includeDirs);
			if (sourceCode.contains(DxShaderType::VERTEX.EntryPoint)) {
				auto shaderSource = DxShaderProgramSourceCode(DxShaderType::VERTEX, sourceCode, sourceName);
				compiler.compile(shaderSource, &include, true);
			} else if (sourceCode.contains(DxShaderType::PIXEL.EntryPoint)) {
				auto shaderSource = DxShaderProgramSourceCode(DxShaderType::PIXEL, sourceCode, sourceName);
				compiler.compile(shaderSource, &include, true);
			} else {
				Logger::print(LogType::ERR0R, _T("The provided file doesn't contain an expected entry point.\n"));
				return 3;
			}
		} catch (const DxCompilationException& exception) {
			AString message = exception.what();
			String tmessage = convertText<char, tchar>(message);
			Logger::print(LogType::ERR0R, tmessage.Data);
			return 4;
		}
	} else {
		try {
			auto loader = makeIntrusive<DxShaderLoader>(resourceManager, compiler);
			loader->includeDirs.add(DirectoryPath(L"./resources/shaders/DirectX/include").AbsolutePath);
			MemoryInputStream stream(buffer.Data, buffer.Size);
			auto shader = makeIntrusive<DxShader>();
			auto coroutine = loader->load(shader.ref(), stream);
			coroutine.resume();
		} catch (const DxCompilationException& exception) {
			AString message = exception.what();
			String tmessage = convertText<char, tchar>(message);
			Logger::print(LogType::ERR0R, tmessage.Data);
			return 5;
		}
	}
	Logger::print(LogType::INFO, _T("Compilation completed without erros.\n"));
	return 0;
}
