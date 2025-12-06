#include <common.hlsli>
#include <ui.hlsli>

cbuffer perCamera: register(b0) {
    int2 viewportSize;
    float time;
}

cbuffer perObject: register(b1) {
    float2 position = float2(50, 350);
    float2 size = float2(300, 300);
    float alpha = 1.0f;
    float4 tint = float4(1, 1, 1, 1);
}

SamplerState linearSampler: register(s0);
Texture2D image: register(t0);

UIPixel vertexMain(UIVertex input) {
    UIPixel output;

    float2 pos = screenToClip(input.position.xy * size + position, viewportSize);
    output.position = float4(pos.xy, input.position.z, 1);
    output.texCoord = input.position.xy;

    return output;
}

matrix makeSaturationMatrix(float sat) {
    matrix m = MATRIX_IDENTITY;
    
    /*
    Where rwgt is 0.3086, gwgt is 0.6094, and bwgt is 0.0820.This is the luminance vector. Notice
    here that we do not usethe standard NTSC weights of 0.299, 0.587, and 0.114.The NTSC weights
    are only applicable to RGB colorsin a gamma 2.2 color space. For linear RGB colors the values
    above are better.
    */
    
    float invSat = 1 - sat;
    float R = 0.213f * invSat;
    float G = 0.715f * invSat;
    float B = 0.072f * invSat;

    m[0][0] = R + sat;
    m[1][0] = G;
    m[2][0] = B;
    m[0][1] = R;
    m[1][1] = G + sat;
    m[2][1] = B;
    m[0][2] = R;
    m[1][2] = G;
    m[2][2] = B + sat;
    
    return m;
}

matrix makeBrightnessMatrix(float b) {
    matrix m = MATRIX_IDENTITY;
    
    m[0][0] = b;
    m[1][1] = b;
    m[2][2] = b;
    
    return m;
}

float getInterpolatedValue(float t) {
    return cos((t + 1) * PI) / 2.0f + 0.5f;
}

float4 pixelMain(UIPixel input): SV_Target {
    float4 color = image.Sample(linearSampler, input.texCoord) * tint;
    float fraction = abs(2 * frac(time / 5) - 1);
    float saturation = getInterpolatedValue(fraction);
    matrix s = makeSaturationMatrix(saturation);
    float brightness = 2 - getInterpolatedValue(min(fraction * 4 / 3, 1));
    float alpha2 = getInterpolatedValue(min(fraction * 2, 1));
    color = saturate(mul(color, brightness));
    color = saturate(mul(color, s));
    return float4(color.rgb, color.a * alpha * alpha2);
}
