cbuffer perCamera : register(b0) {
    row_major float4x4 viewProjection;
    float4x4 gMVP;
    float4x4 gInvPV;
    float3 gCamPos;
    float3 gLightPos;
}

cbuffer perObject : register(b1) {
    row_major float4x4 world;
}

Texture2D gAlbedoTexture : register(t0);
Texture2D gNormalTexture : register(t1);
Texture2D gSpecularGlossTexture : register(t2);
Texture2D gDepth: register(t3);
sampler gLinearSample;


struct VsInput {
    float3 position : POSITION;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float2 texCoord : TEXCOORD0;
};

struct PsInput {
    float4 position : SV_POSITION;
    float2 texCoord: TEXCOORD0;
};

float G_Smith(float roughness, float NoV, float NoL) {
    float  k = (roughness + 1) * (roughness + 1) / 8;
    return  (NoV / (NoV * (1 - k) + k)) *  (NoL / (NoL * (1 - k) + k));
}

float3 GGXBRDF(float3 lightDir, float3 lightPos, float3 albedo, float3 normal, float3 viewDir, float3 specular, float gloss) {
    const  float pi = 3.14159;
    float3 h = normalize(viewDir + lightDir);


    float NdotL = max(0, dot(normal, lightDir));
    float NdotH = max(0, dot(normal, h));
    float LdotH = max(0, dot(lightDir, h));
    float VdotH = max(0, dot(viewDir, h));
    float NdotV = max(0, dot(normal, viewDir));
    float roughness = gloss;

    //D
    float alpha = roughness *  roughness;
    float alphaSqr = alpha*alpha;
    float denom = ((NdotH * NdotH) * (alphaSqr - 1.0f) + 1.0f);
    float D = alphaSqr / (pi * denom* denom);
    float FV;

    //fersnel & V
    float F_b = pow((1 - VdotH), 5);
    float F_a = 1;
    float k = alpha / 2;
    float	vis = G_Smith(roughness, NdotV, NdotL);
    float2 FV_helper = float2(F_a*vis, F_b*vis);
    float3 col = specular*FV_helper.x + (1 - specular)*FV_helper.y;

    col = (NdotL*D*col + NdotL*albedo);

    return float4(col, 1);
}

PsInput vertexMain(VsInput input) {
    PsInput output;

    output.position = float4(input.position,1);
    output.texCoord = input.texCoord;

    return output;
}

float4 pixelMain(PsInput input): SV_Target{
    float z = gDepth[input.position.xy];
    float4 vProjectedPos = float4(input.position.xy, z, 1.0f);
    // Transform by the inverse screen view projection matrix to world space
    float4 vPositionWS = mul(vProjectedPos, gInvPV);
    // Divide by w to get the view-space position
    vPositionWS = vPositionWS / vPositionWS.w;
    float3 albedo = gAlbedoTexture[input.position.xy].xyz;
    float3 normal = normalize(gNormalTexture[input.position.xy].xyz);
    float4 specGloss = gSpecularGlossTexture[input.position.xy].xyzw;
    float3 col = GGXBRDF(normalize(gLightPos.xyz- vPositionWS.xyz), gLightPos, albedo ,normal,	normalize(gCamPos - vPositionWS), specGloss.xyz, specGloss.w);
    float d = length(gLightPos.xyz - vPositionWS.xyz);
    col = col*(1.0f / (1.0f + 0.1f*d + 0.01f*d));
    return float4(col,1.0f);
}

