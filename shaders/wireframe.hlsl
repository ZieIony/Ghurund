cbuffer perCamera : register(b0) {
    row_major float4x4 viewProjection;
}

cbuffer perObject : register(b1) {
    row_major float4x4 world;
}

struct VsInput {
    float3 position : POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
    float2 texCoord : TEXCOORD0;
};

struct GsInput {
    float4 position : SV_POSITION;
};

struct PsInput {
    float4 position : SV_POSITION;
    float3 barycentric : COLOR;
};

GsInput vertexMain(VsInput input) {
    GsInput output;

    output.position = mul(mul(float4(input.position, 1), world), viewProjection);

    return output;
}

[maxvertexcount(3)]
void geometryMain(triangle GsInput input[3],
        inout TriangleStream<PsInput> outStream) {
    PsInput output;

    output.position = input[0].position;
    output.barycentric = float3(1, 0, 0);
    outStream.Append(output);

    output.position = input[1].position;
    output.barycentric = float3(0, 1, 0);
    outStream.Append(output);

    output.position = input[2].position;
    output.barycentric = float3(0, 0, 1);
    outStream.Append(output);

    outStream.RestartStrip();
}

float4 pixelMain(PsInput input): SV_Target{
    float barycentric = min(input.barycentric.x, min(input.barycentric.y, input.barycentric.z));
    if(barycentric>0.005)
        discard;
    return float4(1, 1, 1, 1);
}
