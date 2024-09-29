struct DefaultVertex {
    float3 position : POSITION;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float2 texCoord : TEXCOORD0;
};

struct ScreenVertex {
    float3 position : POSITION;
    float2 texCoord : TEXCOORD0;
};

struct DefaultPixel {
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float2 texCoord: TEXCOORD0;
};

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
	
float3x3 getWorldToTangent(float3 normal, float3 tangent, float4x4 world){
    float3x3 worldToTangentSpace;
    worldToTangentSpace[0] = mul(tangent, world);
    worldToTangentSpace[1] = mul(cross(tangent, normal), world);
    worldToTangentSpace[2] = mul(normal, world);
	return worldToTangentSpace;
}