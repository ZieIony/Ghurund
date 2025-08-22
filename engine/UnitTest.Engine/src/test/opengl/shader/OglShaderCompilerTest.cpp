#include "utepch.h"
#include "CppUnitTest.h"

#include <engine/opengl/shader/OglShaderCompiler.h>
#include <test/MemoryGuard.h>

#include <test/opengl/TestOglContext.h>
#include "TestShaderSources.h"
#include <engine/opengl/shader/OglCompilationException.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::OpenGL;
    using namespace std;

    TEST_CLASS(OglShaderCompilerTest) {
private:
    OglShaderCompiler shaderCompiler;

public:
    TEST_METHOD(OglShaderCompiler_compileVertex) {
        MemoryGuard guard;
        {
            TestOglContext context;

            SharedPointer<OglShaderProgram> shaderProgram(shaderCompiler.compile(TEST_VERTEX_SHADER_SOURCE, OglShaderType::VERTEX));
            Assert::IsNotNull(shaderProgram.get());
        }
    }

    TEST_METHOD(OglShaderCompiler_compileVertexNoMain) {
        MemoryGuard guard;
        {
            TestOglContext context;

            // shaders compile without main just fine, so this check needs to be done in another place
            SharedPointer<OglShaderProgram> shaderProgram(shaderCompiler.compile(TEST_VERTEX_SHADER_SOURCE_NO_MAIN, OglShaderType::VERTEX));
        }
    }

    TEST_METHOD(OglShaderCompiler_compileFragment) {
        MemoryGuard guard;
        {
            TestOglContext context;

            SharedPointer<OglShaderProgram> shaderProgram(shaderCompiler.compile(TEST_FRAGMENT_SHADER_SOURCE, OglShaderType::FRAGMENT));
            Assert::IsNotNull(shaderProgram.get());
        }
    }

    TEST_METHOD(OglShaderCompiler_compileFragmentAsVertex) {
        MemoryGuard guard;
        {
            TestOglContext context;

            Assert::ExpectException<OglCompilationException>([&]() {
                SharedPointer<OglShaderProgram> shaderProgram(shaderCompiler.compile(TEST_VERTEX_SHADER_SOURCE, OglShaderType::FRAGMENT));
            });
        }
    }
    };
}
