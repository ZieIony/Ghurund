struct DefaultPixel {
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float2 texCoord : TEXCOORD0;
};

cbuffer perObject : register(b1) {
    float time;
    int playerIndex;
    int2 viewportSize;
    float4 teamColor;
}

float4 pixelMain(DefaultPixel input) : SV_Target {
    return float4(sin(time) * float2(1, 1) / viewportSize, playerIndex, 1) + teamColor;
}
