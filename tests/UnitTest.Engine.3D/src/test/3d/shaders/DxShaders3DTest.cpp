#include "ute3dpch.h"
#include "CppUnitTest.h"

#include "core/object/IntrusivePointer.h"
#include "engine/directx/DxGraphics.h"
#include "engine/directx/shader/DxShaderLoader.h"

#include "test/utils/TestLogOutput.h"
#include "test/utils/TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::DirectX;
    using namespace UnitTest::Utils;
    using namespace std;

    TEST_CLASS(DxShaders3DTest) {
private:
    Timer timer;
    CoroutineThreadPool threadPool = CoroutineThreadPool(4);
    CoroutineScheduler coroutineScheduler = Ghurund::Core::CoroutineScheduler(threadPool, timer);
    ResourceManager resourceManager = ResourceManager(coroutineScheduler);

    bool tryLoadShader(DxShaderLoader& shaderLoader, const File& file) {
        Buffer buffer;
        file.read(buffer);
        MemoryInputStream stream(buffer.Data, buffer.Size);
        auto shader = makeIntrusive<DxShader>();
        shader->setPath(&file.Path);
        try {
            DirectoryPath workingDir = file.Path.Directory;
            runCoroutineBlocking(shaderLoader.load(shader.ref(), stream, workingDir));
        } catch (std::exception e) {
            return false;
        }
        return shader->IsValid;
    }

public:
    TEST_CLASS_INITIALIZE(DxShaders3DTest_initialize) {
        Ghurund::Core::Logger::init(make_unique<UnitTest::Utils::TestLogOutput>());
    }

    TEST_METHOD(DxShaders3D_loadAll) {
        DxGraphics graphics;
		graphics.init();

		DxShaderCompiler compiler(graphics);
		auto loader = makeIntrusive<DxShaderLoader>(resourceManager, compiler);
        loader->includeDirs.add(DirectoryPath(L"../../resources/shaders/DirectX/include").AbsolutePath);
        DirectoryPath shaderDirectory = DirectoryPath(L"../../resources/shaders/DirectX/3d").AbsolutePath;
		auto files = shaderDirectory.Files;
        if (files.Size == 0) {
            auto message = std::format(L"No files found in {}", shaderDirectory.toString().Data);
            Assert::Fail(message.c_str());
        }
		for (const File& file : files) {
            // TODO: compile single hlsl files too
			if (file.Path.Extension != L"xml")
                continue;
            if (!tryLoadShader(loader.ref(), File(shaderDirectory / file.Path))) {
                auto message = std::format(L"Failed to load shader {}", file.Path.toString().Data);
                Assert::Fail(message.c_str());
            }
        }
    }
    };
}
