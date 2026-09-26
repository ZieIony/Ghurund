#ifndef PBR_HLSLI
#define PBR_HLSLI

#include <common.hlsli>

float distributionGGX(float3 N, float3 H, float roughness) {
    float a2 = roughness * roughness * roughness * roughness;
    float NdotH = max(dot(N, H), 0.0);
    float denom = (NdotH * NdotH * (a2 - 1.0) + 1.0);
    return a2 / (PI * denom * denom);
}

float geometrySchlickGGX(float NdotV, float roughness) {
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;
    return NdotV / (NdotV * (1.0 - k) + k);
}

float geometrySmith(float3 N, float3 V, float3 L, float roughness) {
    return geometrySchlickGGX(max(dot(N, L), 0.0), roughness) *
            geometrySchlickGGX(max(dot(N, V), 0.0), roughness);
}

float3 fresnelSchlick(float cosTheta, float3 F0) {
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float3 pbr(
    float3 position,
    float3 cameraPosition,
    float3 normal,
    float3 albedo,
    float metallic,
    float roughness,
    float3 lightPosition,
    float3 lightColor,
    float3 ambientColor,
    float ao
) {
    float3 N = normal;
    float3 V = normalize(cameraPosition - position);
    float3 L = normalize(lightPosition - position);
    float3 H = normalize(V + L);
    
    //float distance = length(lightPosition - position);
    //float attenuation = 1.0 / (distance * distance);
    float3 radiance = lightColor; //lightColor * attenuation;
                
    // Cook-Torrance BRDF
    float3 F0 = lerp(float3(0.04, 0.04, 0.04), albedo, metallic);
    float NDF = distributionGGX(N, H, roughness);
    float G = geometrySmith(N, V, L, roughness);
    float3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);
    float3 kD = 1.0 - F;
    kD *= 1.0 - metallic;
                
    float3 numerator = NDF * G * F;
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
    float3 specular = numerator / max(denominator, EPSILON);
                    
    float NdotL = max(dot(N, L), 0.0);
    float3 color = lightColor * (kD * albedo / PI + specular + albedo * ambientColor * ao) * NdotL * radiance;
    return color;
}

#endif