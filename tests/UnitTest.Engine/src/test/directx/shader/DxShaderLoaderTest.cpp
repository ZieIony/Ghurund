#include "utepch.h"
#include "CppUnitTest.h"

#include "core/object/IntrusivePointer.h"
#include "engine/directx/DxGraphics.h"
#include "engine/directx/shader/DxShaderLoader.h"

#include "test/utils/TestUtils.h"
#include "engine/directx/shader/compiler/DxEntrypointNotFoundException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	using namespace Ghurund::Core;
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::DirectX;
    using namespace std;

    TEST_CLASS(DxShaderLoaderTest) {
private:
    AString testShaderSource = R"(
struct DefaultVertex {
    float3 position : POSITION;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float2 texCoord : TEXCOORD0;
};

struct DefaultPixel {
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float2 texCoord: TEXCOORD0;
};

cbuffer perCamera : register(b0) {
    row_major float4x4 viewProjection;
}

cbuffer perObject : register(b1) {
    row_major float4x4 world;
}

SamplerState linearSampler : register(s0);
Texture2D diffuseTexture : register(t0);

DefaultPixel vertexMain(DefaultVertex input) {
    DefaultPixel output;

    output.position = mul(mul(float4(input.position, 1), world), viewProjection);
    output.normal = normalize(mul(input.normal, world)).xyz;
    output.tangent = normalize(mul(input.tangent, world)).xyz;
    output.texCoord = input.texCoord;

    return output;
}

float4 pixelMain(DefaultPixel input): SV_Target{
    float4 color = diffuseTexture.Sample(linearSampler, frac(input.texCoord*5));
    return color;
}
)";

    Timer timer;
    CoroutineThreadPool threadPool = CoroutineThreadPool(4);
    CoroutineScheduler coroutineScheduler = Ghurund::Core::CoroutineScheduler(threadPool, timer);
    ResourceManager resourceManager = coroutineScheduler;

    public:

        TEST_METHOD(DxShaderLoader_loadUnknownFormat) {
            DxGraphics graphics;
            graphics.init();

            DxShaderCompiler compiler(graphics);
            auto loader = makeIntrusive<DxShaderLoader>(resourceManager, compiler);
            Buffer data("test", 4);
            MemoryInputStream stream(data.Data, data.Size);

            Assert::ExpectException<DxEntrypointNotFoundException>([&] {
                auto shader = makeIntrusive<DxShader>();
                loader->load(shader.ref(), stream);
            });
        }

        TEST_METHOD(DxShaderLoader_loadHlsl) {
            DxGraphics graphics;
            graphics.init();

            DxShaderCompiler compiler(graphics);
            auto loader = makeIntrusive<DxShaderLoader>(resourceManager, compiler);
            MemoryInputStream stream(testShaderSource.Data, testShaderSource.Size);
            auto shader = makeIntrusive<DxShader>();
            loader->load(shader.ref(), stream);
  
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
