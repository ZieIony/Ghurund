#include "utepch.h"
#include "CppUnitTest.h"

#include "core/object/IntrusivePointer.h"

#include <test/TestUtils.h>
#include <engine/directx/shader/ShaderLoader.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	using namespace Ghurund::Core;
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::DirectX;
    using namespace std;

    TEST_CLASS(ShaderLoaderTest) {
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

    public:

        TEST_METHOD(ShaderLoader_loadUnknownFormat) {
            auto graphics = makeIntrusive<Graphics>();
            graphics->init();
            auto commandList = makeIntrusive<CommandList>();
            commandList->init(*graphics.get(), graphics->CopyQueue);

            ParameterManager parameterManager;
            ShaderCompiler compiler(graphics.ref(), parameterManager);
            IntrusivePointer<ShaderLoader> loader(ghnew ShaderLoader(compiler));
            Buffer data;
            MemoryInputStream stream(data.Data, data.Size);

            Assert::ExpectException<InvalidFormatException>([&]() {
                IntrusivePointer<Shader> shader((Shader*)loader->load(stream, DirectoryPath()));
            });
        }

        TEST_METHOD(ShaderLoader_loadHlsl) {
            auto graphics = makeIntrusive<Graphics>();
            graphics->init();
            auto commandList = makeIntrusive<CommandList>();
            commandList->init(*graphics.get(), graphics->CopyQueue);

            ParameterManager parameterManager;
            ShaderCompiler compiler(graphics.ref(), parameterManager);
            IntrusivePointer<ShaderLoader> loader(ghnew ShaderLoader(compiler));
            MemoryInputStream stream(testShaderSource.Data, testShaderSource.Size);
            IntrusivePointer<Shader> shader((Shader*)loader->load(stream, DirectoryPath()));
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
