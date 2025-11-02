struct DefaultPixel {
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float2 texCoord : TEXCOORD0;
};

cbuffer perObject : register(b1) {
    float alpha = 0.3f;
    float2 size = float2(0.5f, 0.5f);
    float3 up = float3(0, 1, 0);
    float3 dir = float3(0, 1, 0);
    float4 teamColor = float4(0.5f, 0, 1, 1);
}

float4 pixelMain(DefaultPixel input) : SV_Target {
    return teamColor + float4(size, size) + float4(up, alpha);
}
