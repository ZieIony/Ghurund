#include <common.hlsli>

const static float fSamples = 3.0f;
const static uint nSamples = 3;
const static float scaleDepth = 0.25f;
const static float eSpace = 1.0f;
const static float eSun = 20.0f;
const static float kr = 0.0025f;
const static float km = 0.0010f;
const static float pi = 3.14159265;
const static float fKrESun = kr * eSun;
const static float fKmESun = km * eSun;
const static float fKr4PI = kr * 4 * pi;
const static float fKm4PI = km * 4 * pi;
const static float3 waveLength = float3(0.650f, 0.570f, 0.475f);
const static float3 waveLengthInv4 = 1 / pow(waveLength, 4);
const static float g = -0.99f;
const static float g2 = g * g;

float scale(float fCos) {
    float x = 1.0 - fCos;
    return scaleDepth * exp(-0.00287 + x * (0.459 + x * (3.83 + x * (-6.80 + x * 5.25))));
}

float getMiePhase(float fCos, float fCos2, float g, float g2) {
    return 1.5 * ((1.0 - g2) / (2.0 + g2)) * (1.0 + fCos2) / pow(1.0 + g2 - 2.0 * g * fCos, 1.5);
}

float getRayleighPhase(float fCos2) {
    return 0.75 + 0.75 * fCos2;
}

cbuffer constants : register(b0) {
    row_major float4x4 world;
    row_major float4x4 viewProjection;
    float2 viewportSize;
	float3 sunDirection;
	float3 cameraPosition;
	float innerRadius;
	float outerRadius;
}

struct SkyPixel {
    float4 position:SV_Position;
    float3 worldPosition:TexCoord0;
};

SkyPixel vertexMain(DefaultVertex input) {
    SkyPixel output;

	float4 posWorld = mul(float4(input.position.xyz,1), world);
	output.worldPosition = posWorld.xyz;
    output.position = mul(posWorld, viewProjection);

    return output;
}

[maxvertexcount(3)]
void geometryMain(triangle SkyPixel input[3], inout TriangleStream<SkyPixel> outStream) {
	outStream.Append(input[0]);
	outStream.Append(input[2]);
	outStream.Append(input[1]);

	outStream.RestartStrip();
}

float4 pixelMain(SkyPixel input): SV_Target{
    float3 v3Pos = input.worldPosition;
    float3 v3Ray = v3Pos - cameraPosition;
    float fFar = length(v3Ray);
    v3Ray /= fFar;

	float rscale = 1 / (outerRadius - innerRadius);
	float scaleOverScaleDepth = rscale / scaleDepth;

    float3 lightDir = normalize(sunDirection);

    float3 v3Start = cameraPosition;
    float fHeight = length(v3Start);
    float fDepth = exp(scaleOverScaleDepth * (innerRadius - cameraPosition.y));
    float fStartAngle = dot(v3Ray, v3Start) / fHeight;
    float fStartOffset = fDepth * scale(fStartAngle);

    float fSampleLength = fFar / fSamples;
    float fScaledLength = fSampleLength * rscale;
    float3 v3SampleRay = v3Ray * fSampleLength;
    float3 v3SamplePoint = v3Start + v3SampleRay * 0.5;

    float3 v3FrontColor = float3(0.0, 0.0, 0.0);
    for (int i = 0; i < nSamples; i++) {
        float fHeight = length(v3SamplePoint);
        float fDepth = exp(scaleOverScaleDepth * (innerRadius - fHeight));
        float fLightAngle = dot(lightDir, v3SamplePoint) / fHeight;
        float fCameraAngle = dot(v3Ray, v3SamplePoint) / fHeight;
        float fScatter = (fStartOffset + fDepth * (scale(fLightAngle) - scale(fCameraAngle)));
        float3 v3Attenuate = exp(-fScatter * (waveLengthInv4 * fKr4PI + fKm4PI));
        v3FrontColor += v3Attenuate * (fDepth * fScaledLength);
        v3SamplePoint += v3SampleRay;
    }

    float3 c0 = v3FrontColor * (waveLengthInv4 * fKrESun);
    float3 c1 = v3FrontColor * fKmESun;
    float3 v3Direction = cameraPosition - v3Pos;

    float fCos = dot(lightDir, v3Direction) / length(v3Direction);
    float fCos2 = fCos * fCos;
    float rp = getRayleighPhase(fCos2);
    float mp = getMiePhase(fCos, fCos2, g, g2);
    float3 color = rp * c0 + mp * c1;

    return float4(color, 1);
}
