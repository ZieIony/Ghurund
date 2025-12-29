#include "utepch.h"
#include "CppUnitTest.h"

#include "core/io/File.h"
#include "core/object/IntrusivePointer.h"
#include "core/reflection/StandardTypes.h"
#include "engine/directx/DxGraphics.h"
#include "engine/directx/shader/DxShaderLoader.h"
#include "engine/parameter/ValueParameter.h"
#include "test/utils/MemoryGuard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::DirectX;
    using namespace std;

    TEST_CLASS(DxParameterTest) {
private:
    WString resDir = RES_DIR;

    DxGraphics graphics;
    SharedPointer<DxShaderCompiler> shaderCompiler;

    template<typename T>
    void verifyParameter(Parameter* parameter, const char* name, const T& value) {
        Assert::AreEqual(name, parameter->Name.Data);
        Assert::IsTrue(Ghurund::Core::getType<T>() == parameter->Type.TemplateParams[0]);
        Assert::IsNotNull(dynamic_cast<ValueParameter<T>*>(parameter));
        ValueParameter<T>* typedParameter = (ValueParameter<T>*)parameter;
        Assert::AreEqual(sizeof(T), typedParameter->Size);
        auto paramValue = typedParameter->Value;
		Assert::IsTrue(memcmp(&paramValue, &value, sizeof(T)) == 0);
    }

    AString loadShaderSource(const WString& path) {
        File file = FilePath(resDir + path);
        Buffer buffer;
        file.read(buffer);
        return AString((const char*)buffer.Data, buffer.Size);
    }

public:
    DxParameterTest() {
        graphics.init();
        shaderCompiler = makeShared<DxShaderCompiler>(graphics);
    }

    TEST_METHOD(DxParameter_intParams) {
        MemoryGuard guard;
        {
            AString testShaderSource = loadShaderSource(L"/shaders/DirectX/intParams.hlsl");

            /*SharedPointer<DxShaderProgram> shaderProgram(shaderCompiler->compile(testShaderSource, DxShaderType::PIXEL));
            List<ConstantBuffer*> constantBuffers;
            List<TextureConstant*> textures;
            List<Sampler*> samplers;
            shaderCompiler->initConstants(*shaderProgram.get(), constantBuffers, textures, samplers);

            auto alpha = constantBuffers[0]->getParameter("alpha");
            verifyParameter<int32_t>(alpha, "alpha", 5);

            auto size = constantBuffers[0]->getParameter("size");
            verifyParameter<::DirectX::XMINT2>(size, "size", ::DirectX::XMINT2(30, 50));

            auto prevSize = constantBuffers[0]->getParameter("prevSize");
            Assert::IsNull(prevSize);

            constantBuffers.deleteItems();
            textures.deleteItems();
            samplers.deleteItems();*/
        }
    }

    TEST_METHOD(DxParameter_floatParams) {
        MemoryGuard guard;
        {
            AString testShaderSource = loadShaderSource(L"/shaders/DirectX/floatParams.hlsl");

            SharedPointer<DxShaderProgram> shaderProgram(shaderCompiler->compile(testShaderSource, DxShaderType::PIXEL));
            List<ConstantBuffer*> constantBuffers;
            List<TextureConstant*> textures;
            List<Sampler*> samplers;
            shaderCompiler->initConstants(*shaderProgram.get(), constantBuffers, textures, samplers);

            /*auto alpha = constantBuffers[0]->getParameter("alpha");
            verifyParameter<float>(alpha, "alpha", 0.3f);

            auto size = constantBuffers[0]->getParameter("size");
            verifyParameter<::DirectX::XMFLOAT2>(size, "size", ::DirectX::XMFLOAT2(0.5f, 0.5f));

            auto up = constantBuffers[0]->getParameter("up");
            verifyParameter<::DirectX::XMFLOAT3>(up, "up", ::DirectX::XMFLOAT3(0, 1, 0));

            auto dir = constantBuffers[0]->getParameter("dir");
            Assert::IsNull(dir);

            auto teamColor = constantBuffers[0]->getParameter("teamColor");
            verifyParameter<::DirectX::XMFLOAT4>(teamColor, "teamColor", ::DirectX::XMFLOAT4(0.5f, 0, 1, 1));*/

            constantBuffers.deleteItems();
            textures.deleteItems();
            samplers.deleteItems();
        }
    }

    TEST_METHOD(DxParameter_matrixParams) {
        MemoryGuard guard;
        {
            AString testShaderSource = loadShaderSource(L"/shaders/DirectX/matrixParams.hlsl");

            SharedPointer<DxShaderProgram> shaderProgram(shaderCompiler->compile(testShaderSource, DxShaderType::PIXEL));
            List<ConstantBuffer*> constantBuffers;
            List<TextureConstant*> textures;
            List<Sampler*> samplers;
            shaderCompiler->initConstants(*shaderProgram.get(), constantBuffers, textures, samplers);

            //auto view = constantBuffers[0]->getParameter("view");
            //verifyParameter<::DirectX::XMFLOAT4X4>(view, "view", ::DirectX::XMFLOAT4X4());

            constantBuffers.deleteItems();
            textures.deleteItems();
            samplers.deleteItems();
        }
    }
    };
}
