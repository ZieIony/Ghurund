#include "utepch.h"
#include "CppUnitTest.h"

#include "engine/graphics/mesh/MeshData.h"
#include <engine/directx/mesh/DxMesh.h>
#include "test/utils/MemoryGuard.h"
#include <engine/directx/shader/compiler/DxShaderCompiler.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::DirectX;
    using namespace ::DirectX;
    using namespace std;

    TEST_CLASS(DxShaderCompilerTest) {
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

    ResourceManager resourceManager;
    DxGraphics graphics;
    SharedPointer<DxShaderCompiler> shaderCompiler;

public:
    DxShaderCompilerTest() {
        graphics.init();
        shaderCompiler = makeShared<DxShaderCompiler>(graphics);
    }

    TEST_METHOD(DxShaderCompiler_compileVertex) {
        MemoryGuard guard;
        {
            SharedPointer<DxShaderProgram> shaderProgram(shaderCompiler->compile(testShaderSource, DxShaderType::VERTEX));
            Assert::IsNotNull(shaderProgram.get());
        }
    }

    TEST_METHOD(DxShaderCompiler_compilePixel) {
        MemoryGuard guard;
        {
            SharedPointer<DxShaderProgram> shaderProgram(shaderCompiler->compile(testShaderSource, DxShaderType::PIXEL));
            Assert::IsNotNull(shaderProgram.get());
        }
    }
    };
}
