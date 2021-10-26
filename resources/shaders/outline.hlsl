#include <common.hlsli>

cbuffer perCamera : register(b0) {
    row_major float4x4 viewProjection;
	float2 viewportSize;
}

cbuffer perObject : register(b1) {
    row_major float4x4 world;
	float4 outlineColor;
}

SamplerState linearSampler : register(s0);
Texture2D diffuseTexture : register(t0);

static const float outlineThickness = 2.0f;

struct OutlinePixel{
	float4 position:SV_Position;
};

OutlinePixel vertexMain(DefaultVertex input) {
    OutlinePixel output;

    output.position = mul(mul(float4(input.position, 1), world), viewProjection);
	output.position/=output.position.w;
    float3 normal = mul(mul(input.normal, (float3x3)world), (float3x3)viewProjection);
	output.position.xy+=normalize(normal.xy)*2/viewportSize*outlineThickness;

    return output;
}

[maxvertexcount(3)]
void geometryMain(triangle OutlinePixel input[3], inout TriangleStream<OutlinePixel> outStream) {

	outStream.Append(input[0]);
	outStream.Append(input[2]);
	outStream.Append(input[1]);

	outStream.RestartStrip();
}

float4 pixelMain(OutlinePixel input): SV_Target{
    return outlineColor;
}
