struct DefaultPixel {
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float2 texCoord : TEXCOORD0;
};

cbuffer perObject : register(b1) {
    row_major float4x4 view;
}

float4 pixelMain(DefaultPixel input) : SV_Target {
    return view._11_11_11_11;
}
