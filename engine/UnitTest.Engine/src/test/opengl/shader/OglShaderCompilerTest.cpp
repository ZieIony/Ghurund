#include "utepch.h"
#include "CppUnitTest.h"

#include <engine/opengl/shader/OglShaderCompiler.h>
#include <test/MemoryGuard.h>

#include "TestShaderSources.h"
#include <engine/opengl/shader/OglCompilationException.h>
#include <engine/opengl/OglGraphics.h>

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
            auto graphics = makeIntrusive<OglGraphics>();
            graphics->init();

            SharedPointer<OglShaderProgram> shaderProgram(shaderCompiler.compile(TEST_VERTEX_SHADER_SOURCE, OglShaderType::VERTEX));
            Assert::IsNotNull(shaderProgram.get());
        }
    }

    TEST_METHOD(OglShaderCompiler_compileVertexNoMain) {
        MemoryGuard guard;
        {
            auto graphics = makeIntrusive<OglGraphics>();
            graphics->init();

            // shaders compile without main just fine, so this check needs to be done in another place
            SharedPointer<OglShaderProgram> shaderProgram(shaderCompiler.compile(TEST_VERTEX_SHADER_SOURCE_NO_MAIN, OglShaderType::VERTEX));
        }
    }

    TEST_METHOD(OglShaderCompiler_compileFragment) {
        MemoryGuard guard;
        {
            auto graphics = makeIntrusive<OglGraphics>();
            graphics->init();

            SharedPointer<OglShaderProgram> shaderProgram(shaderCompiler.compile(TEST_FRAGMENT_SHADER_SOURCE, OglShaderType::FRAGMENT));
            Assert::IsNotNull(shaderProgram.get());
        }
    }

    TEST_METHOD(OglShaderCompiler_compileFragmentAsVertex) {
        MemoryGuard guard;
        {
            auto graphics = makeIntrusive<OglGraphics>();
            graphics->init();

            Assert::ExpectException<OglCompilationException>([&] {
                SharedPointer<OglShaderProgram> shaderProgram(shaderCompiler.compile(TEST_VERTEX_SHADER_SOURCE, OglShaderType::FRAGMENT));
            });
        }
    }
    };
}
