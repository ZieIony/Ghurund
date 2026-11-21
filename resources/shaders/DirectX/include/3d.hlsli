#ifndef _3D_HLSLI
#define _3D_HLSLI

#include <objectParameters.hlsli>

struct DefaultVertex3D {
    float3 position: POSITION;
    float3 normal: NORMAL;
    float3 tangent: TANGENT;
    float2 texCoord: TEXCOORD0;
    uint objectId: OBJECT_ID;
};

struct DefaultPixel3D {
    float4 screenPosition: SV_POSITION;
    float3 position: TEXCOORD0;
    float3 normal: NORMAL;
    float3 tangent: TANGENT;
    float2 texCoord: TEXCOORD1;
    nointerpolation uint objectId: OBJECT_ID;
};

DefaultPixel3D vertexMain(DefaultVertex3D input, ObjectParameters objectParameters);

DefaultPixel3D vertexMain(DefaultVertex3D input) {
    ObjectParameters parameters = gh_objectParameters[input.objectId];
    DefaultPixel3D output = vertexMain(input, parameters);
    output.objectId = input.objectId;
    return output;
}

float getDiffuseIntensity(float3 normalNormalized, float3 vertexToLightNormalized) {
    return saturate(dot(normalNormalized, vertexToLightNormalized));
}

float getSpecularIntensity(float3 vertexPos, float3 normalNormalized, float3 cameraPos, float3 vertexToLightNormalized, float power) {
    float3 v = normalize(cameraPos - vertexPos);
    float3 r = reflect(-vertexToLightNormalized, normalNormalized);
    return pow(saturate(dot(r, v)), power);
}

/*float3 sampleNormalMap(float3 normal, float3 tangent, float2 texCoord){
	float3x3 toWorld = float3x3(tangent, cross(tangent, normal), normal);
	float3 normalMap = u_NormalMap.Sample(u_NormalSampler, texCoord).rgb * 2.0 - 1.0;
	normalMap = mul(normalMap.rgb, toWorld);
	normalMap = normalize(normalMap);
	return normalMap;
}*/
	
float3x3 getWorldToTangent(float3 normal, float3 tangent, float4x4 world) {
    float3x3 worldToTangentSpace;
    worldToTangentSpace[0] = mul(tangent, (float3x3)world);
    worldToTangentSpace[1] = mul(cross(tangent, normal), (float3x3)world);
    worldToTangentSpace[2] = mul(normal, (float3x3)world);
    return worldToTangentSpace;
}

#endif