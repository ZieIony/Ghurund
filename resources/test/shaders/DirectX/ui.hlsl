struct UIVertex {
    float3 position: POSITION;
};

struct UIPixel {
    float4 position: SV_POSITION;
    float2 texCoord: TEXCOORD0;
};

cbuffer perObject: register(b0) {
    float4 color = float4(0, 0, 0, 0.15f);
}

UIPixel vertexMain(UIVertex input) {
    UIPixel output;

    float2 pos = input.position.xy;
    output.position = float4(pos.xy, input.position.z, 1);
    output.texCoord = output.position.xy;

    return output;
}

float4 pixelMain(UIPixel input): SV_Target {
    return color;
}
