cbuffer perCamera : register(b0) {
    row_major float4x4 viewProjection;
}

cbuffer perObject : register(b1) {
    row_major float4x4 world;
}

SamplerState linearSampler : register(s0);
Texture2D diffuseTexture : register(t0);

struct VsInput {
    float3 position : POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
    float2 texCoord : TEXCOORD0;
};

struct PsInput {
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float2 texCoord: TEXCOORD0;
};

PsInput vertexMain(VsInput input) {
    PsInput output;

    output.position = mul(mul(float4(input.position, 1), world), viewProjection);
	output.normal = normalize(mul(input.normal, world)).xyz;
	output.tangent = normalize(mul(input.tangent, world)).xyz;
	output.texCoord = input.texCoord;

    return output;
}

float4 pixelMain(PsInput input): SV_Target{
    return diffuseTexture.Sample(linearSampler, input.texCoord);
}
