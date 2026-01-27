#include "utepch.h"
#include "CppUnitTest.h"

#include "core/Colors.h"
#include "core/io/File.h"
#include "core/object/IntrusivePointer.h"
#include "core/reflection/StandardTypes.h"
#include "engine/directx/DxGraphics.h"
#include "engine/directx/shader/compiler/DxShaderCompiler.h"
#include "engine/directx/shader/compiler/DxShaderProgram.h"
#include "engine/parameter/ParameterManager.h"
#include "engine/parameter/ValueParameter.h"
#include "test/utils/MemoryGuard.h"
#include "test/utils/TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::DirectX;
    using namespace std;

    TEST_CLASS(ParameterTest) {
private:
    WString resDir = RES_DIR;

    ResourceManager resourceManager;
    DxGraphics graphics;
    SharedPointer<DxShaderCompiler> shaderCompiler;

    AString loadShaderSource(const WString& path) {
        File file = FilePath(resDir + path);
        Buffer buffer;
        file.read(buffer);
        return AString((const char*)buffer.Data, buffer.Size);
    }

public:
    ParameterTest() {
        TestUtils::testClassInitialize();

        graphics.init();
        shaderCompiler = makeShared<DxShaderCompiler>(graphics);
    }

    TEST_METHOD(Parameter_defaultValue) {
        const AString playerIndexName = "playerIndex";
        const AString viewportSizeName = "viewportSize";
        const AString teamColorName = "teamColor";
        ParameterManager parameterManager;
        {
            auto playerIndexParameter = makeIntrusive<IntParameter>(playerIndexName, 3);
            parameterManager.Parameters.put(playerIndexParameter.get());

            auto viewportSizeParameter = makeIntrusive<Int2Parameter>(viewportSizeName, ::DirectX::XMINT2(800, 600));
            parameterManager.Parameters.put(viewportSizeParameter.get());

            auto teamColorParameter = makeIntrusive<Float4Parameter>(teamColorName, Colors::MINT_CREAM.toVector());
            parameterManager.Parameters.put(teamColorParameter.get());
        }

        MemoryGuard guard;
        {
            AString testShaderSource = loadShaderSource(L"/shaders/DirectX/defaultParams.hlsl");

            SharedPointer<DxShaderProgram> shaderProgram(shaderCompiler->compile(testShaderSource, "pixelMain", DxShaderType::PIXEL));
            List<ConstantBuffer*> constantBuffers;
            List<TextureConstant*> textures;
            List<Sampler*> samplers;
            //shaderCompiler->initConstants(*shaderProgram.get(), constantBuffers, textures, samplers);

            // not set anywhere
            /*auto time = (FloatParameter*)constantBuffers[0]->getParameter("time");
            Assert::IsNotNull(time->RawValue, L"raw value is null");
            Assert::IsTrue(time->IsEmpty, L"time is not empty");

            // set in the constant buffer
            auto playerIndex = (IntParameter*)constantBuffers[0]->getParameter(playerIndexName);
            playerIndex->Value = 1;
            auto expectedPlayerIndex = 1;
            Assert::IsTrue(memcmp(&expectedPlayerIndex, playerIndex->RawValue, playerIndex->Size) == 0);
            Assert::IsFalse(playerIndex->IsEmpty);

            // set in parameter manager (parameter manager doesn't provide defaults now)
            auto viewportSize = (Int2Parameter*)constantBuffers[0]->getParameter(viewportSizeName);
            auto expectedViewportSize = ::DirectX::XMINT2(800, 600);
            Assert::IsFalse(memcmp(&expectedViewportSize, viewportSize->RawValue, viewportSize->Size) == 0);
            Assert::IsTrue(viewportSize->IsEmpty);

            // set in both places
            auto teamColor = (Float4Parameter*)constantBuffers[0]->getParameter(teamColorName);
            teamColor->Value = Colors::AQUAMARINE.toVector();
            auto expectedTeamColor = Colors::AQUAMARINE.toVector();
            Assert::IsTrue(memcmp(&expectedTeamColor, teamColor->RawValue, teamColor->Size) == 0);
            Assert::IsFalse(teamColor->IsEmpty);*/

            constantBuffers.deleteItems();
            textures.deleteItems();
            samplers.deleteItems();
        }
    }

    TEST_METHOD(Parameter_differentTypes) {
        const AString teamColorName = "teamColor";
        ParameterManager parameterManager;
        {
            auto teamColorParameter = makeIntrusive<IntParameter>(teamColorName, 3);
            parameterManager.Parameters.put(teamColorParameter.get());
        }

        MemoryGuard guard;
        {
            AString testShaderSource = loadShaderSource(L"/shaders/DirectX/defaultParams.hlsl");
            SharedPointer<DxShaderProgram> shaderProgram(shaderCompiler->compile(testShaderSource, "pixelMain", DxShaderType::PIXEL));
            List<ConstantBuffer*> constantBuffers;
            List<TextureConstant*> textures;
            List<Sampler*> samplers;
            //shaderCompiler->initConstants(*shaderProgram.get(), constantBuffers, textures, samplers);

            /*auto teamColor = (Float4Parameter*)constantBuffers[0]->getParameter(teamColorName);
            Assert::IsNotNull(teamColor->RawValue);
            Assert::IsTrue(teamColor->IsEmpty);*/

            constantBuffers.deleteItems();
            textures.deleteItems();
            samplers.deleteItems();
        }
    }
    };
}
