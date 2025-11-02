#include "utepch.h"
#include "CppUnitTest.h"

#include "core/object/IntrusivePointer.h"

#include "TestShaderSources.h"
#include <core/object/SharedPointer.h>
#include <engine/opengl/OglGraphics.h>
#include <engine/opengl/shader/OglShaderLoader.h>
#include "test/utils/TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
	using namespace Ghurund::Core;
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::OpenGL;
    using namespace std;

    TEST_CLASS(OglShaderLoaderTest) {
    public:

        TEST_METHOD(OglShaderLoader_loadUnknownFormat) {
            auto graphics = makeIntrusive<OglGraphics>();
            graphics->init();
            
            OglShaderCompiler compiler;
            IntrusivePointer<OglShaderLoader> loader(ghnew OglShaderLoader(compiler));
            Buffer data("asdf", 5);
            MemoryInputStream stream(data.Data, data.Size);

            Assert::ExpectException<InvalidFormatException>([&] {
                IntrusivePointer<OglShader> shader((OglShader*)loader->load(stream, DirectoryPath()));
            });
        }

        TEST_METHOD(OglShaderLoader_loadShader) {
            auto graphics = makeIntrusive<OglGraphics>();
            graphics->init();

            OglShaderCompiler compiler;
            IntrusivePointer<OglShaderLoader> loader(ghnew OglShaderLoader(compiler));
            MemoryInputStream stream(TEST_OPENGL_SHADER_SOURCE.Data, TEST_OPENGL_SHADER_SOURCE.Size);
            IntrusivePointer<OglShader> shader((OglShader*)loader->load(stream, DirectoryPath()));

            Assert::IsNotNull(shader.get());
        }

        /*TEST_METHOD(ShaderLoader_saveLoadNative) {
            IntrusivePointer<ShaderLoader> loader(ghnew ShaderLoader());

            auto outShader= makeIntrusive<Shader>();
            outShader->sourceCode = testShaderSource;
            MemoryOutputStream outStream;
            loader->save(outStream, DirectoryPath(), *outShader.get());

            MemoryInputStream inStream(outStream.Data, outStream.BytesWritten);
            IntrusivePointer<ShaderCode> inShaderCode(loader->load(inStream, DirectoryPath()));

            Assert::AreEqual(outShaderCode->sourceCode, inShaderCode->sourceCode);
        }*/
    };
}
