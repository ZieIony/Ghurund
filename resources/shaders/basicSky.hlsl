#include <common.hlsli>

cbuffer constants : register(b0) {
	row_major float4x4 world;
	row_major float4x4 viewProjection;
}

struct SkyPixel {
	float4 position:SV_Position;
	float height:TexCoord0;
};

SkyPixel vertexMain(ScreenVertex input) {
	SkyPixel output;

	output.position = mul(mul(float4(input.position.xyz, 1), world), viewProjection);
	output.height = input.position.y;

	return output;
}

[maxvertexcount(3)]
void geometryMain(triangle SkyPixel input[3], inout TriangleStream<SkyPixel> outStream) {
	outStream.Append(input[0]);
	outStream.Append(input[2]);
	outStream.Append(input[1]);

	outStream.RestartStrip();
}

float4 pixelMain(SkyPixel input) : SV_Target{
	float4 sky = lerp(float4(1, 1, 1, 1), float4(0.55,0.8,1,1), saturate(input.height*3));
	float4 skyGround = lerp(sky, float4(0,0,0,1), saturate(-input.height *50));
	return skyGround;
}