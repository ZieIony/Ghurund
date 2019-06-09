#include <common.hlsli>

cbuffer perCamera : register(b0) {
	row_major float4x4 viewProjectionInv;
	float2 viewportSize;
}

cbuffer perObject : register(b1) {
}

struct SkyPixel{
	float4 position:SV_Position;
};

SkyPixel vertexMain(ScreenVertex input) {
    SkyPixel output;

    output.position = float4(input.position.xy, 0.9999999, 1);

    return output;
}

float4 pixelMain(SkyPixel input): SV_Target{
	float4 screenPos = input.position;
	screenPos.x=screenPos.x/viewportSize.x*2-1;
	screenPos.y=1-screenPos.y/viewportSize.y*2;
	float4 worldPos = mul(screenPos, viewProjectionInv);
	worldPos/=worldPos.w;
    float4 sky = lerp(float4(0.55,0.8,1,1), float4(1,1,1,1), saturate(worldPos.y/10000));
	float4 skyGround = lerp(sky, float4(0.14,0.14,0.14,1), saturate(-worldPos.y/100));
	return skyGround;
}
