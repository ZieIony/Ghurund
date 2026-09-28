#ifndef PBR_HLSLI
#define PBR_HLSLI

#include <common.hlsli>

float distributionGGX(float3 N, float3 H, float roughness) {
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float denominator = (NdotH * NdotH * (a2 - 1.0) + 1.0);
    return a2 / (PI * denominator * denominator);
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
    return F0 + (1.0 - F0) * pow(saturate(1.0 - cosTheta), 5.0);
}

float3 fresnelSchlickRoughness(float cosTheta, float3 F0, float roughness) {
    float3 rF0 = max(float3(1.0 - roughness, 1.0 - roughness, 1.0 - roughness), F0);
    return F0 + (rF0 - F0) * pow(saturate(1.0 - cosTheta), 5.0);
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
    float NdotV = max(dot(N, V), 0.0);
    float3 L = normalize(lightPosition - position);
    float3 H = normalize(V + L);
    float HdotV = max(dot(H, V), 0.0);
    
    //float distance = length(lightPosition - position);
    //float attenuation = 1.0 / (distance * distance);
    float3 radiance = lightColor; //lightColor * attenuation;
                
    // Cook-Torrance BRDF
    float3 F0 = lerp(float3(0.04, 0.04, 0.04), albedo, metallic);
    float NDF = distributionGGX(N, H, roughness);
    float G = geometrySmith(N, V, L, roughness);
    float3 F = fresnelSchlick(HdotV, F0);
    float kS = F;
    float3 kD = (1.0 - kS) * (1.0 - metallic);
                
    float NdotL = max(dot(N, L), 0.0);
    float3 numerator = NDF * G * F;
    float denominator = 4.0 * NdotV * NdotL;
    float3 specular = numerator / max(denominator, EPSILON);
                    
    float3 color = radiance * (kD * albedo / PI + specular + albedo * ambientColor * ao) * NdotL;
    return color;
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
    TextureCube environmentMap,
    TextureCube irradianceMap,
    SamplerState cubeSampler,
    Texture2D brdfLUT,
    SamplerState lutSampler,
    float ao
) {
    float3 N = normal;
    float3 V = normalize(cameraPosition - position);
    float NdotV = max(dot(N, V), 0.0);
    float3 R = reflect(-V, N);
    float3 F0 = lerp(float3(0.04, 0.04, 0.04), albedo, metallic);
    
    float3 color = 0;
    // diffuse
    {
        float3 L = normalize(lightPosition - position);
        float3 H = normalize(V + L);
        float HdotV = max(dot(H, V), 0.0);
        
        float3 radiance = lightColor; // maybe use attenuation?
        
        // Cook-Torrance BRDF
        float NDF = distributionGGX(N, H, roughness);
        float G = geometrySmith(N, V, L, roughness);
        float3 F = fresnelSchlick(HdotV, F0);
        float kS = F;
        float3 kD = (1.0 - kS) * (1.0 - metallic);

        float NdotL = max(dot(N, L), 0.0);
        float3 numerator = NDF * G * F;
        float denominator = 4.0 * NdotV * NdotL;
        float3 specular = numerator / max(denominator, EPSILON);

        color += (kD * albedo / PI + specular) * radiance * NdotL;
    }

    // ambient
    {
        float3 F = fresnelSchlickRoughness(NdotV, F0, roughness);
        float3 kS = F;
        float3 kD = (1.0 - kS) * (1.0 - metallic);
        float3 irradiance = irradianceMap.Sample(cubeSampler, N).rgb;
        
        const float MAX_REFLECTION_LOD = 1.0;   // use more levels if possible
        float3 prefilteredColor = environmentMap.SampleLevel(cubeSampler, R, roughness * MAX_REFLECTION_LOD).rgb;
        float2 brdf = brdfLUT.Sample(lutSampler, float2(NdotV, roughness)).rg;
        float3 specular = prefilteredColor * (F * brdf.x + brdf.y);
        
        color += (kD * irradiance * albedo + specular) * ao;
    }
    
    return color;
}

#endif