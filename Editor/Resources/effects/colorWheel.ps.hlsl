sampler2D implicitInput : register(s0);
float saturation : register(c0);
float lightness : register(c1);

float3 hueToRgb(in float h) {
    float r = abs(h * 6 - 3) - 1;
    float g = 2 - abs(h * 6 - 2);
    float b = 2 - abs(h * 6 - 4);
    return saturate(float3(r, g, b));
}

float3 hslToRgb(in float3 hsl) {
    float3 rgb = hueToRgb(hsl.x);
    float c = (1 - abs(2 * hsl.z - 1)) * hsl.y;
    return (rgb - 0.5) * c + hsl.z;
}

float4 main(float2 uv : TEXCOORD): COLOR{
    float4 color = tex2D(implicitInput, uv);
    float2 xy = uv*2 - 1;
    float l = sqrt(xy.x * xy.x + xy.y * xy.y);
    float a = atan2(xy.y, xy.x) / 3.14 / 2 + 0.5;
    return l<=1?float4(hslToRgb(float3(a, l, lightness)), 1) : color;
}