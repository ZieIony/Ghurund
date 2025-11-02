struct DefaultPixel {
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float2 texCoord : TEXCOORD0;
};

cbuffer perObject : register(b1) {
    int alpha = 5;
    int2 size = int2(30, 50);
    int2 prevSize = int2(0, 0);
}

float4 pixelMain(DefaultPixel input) : SV_Target {
    return float4(size / 100.0f, 0, alpha / 100.0f);
}
