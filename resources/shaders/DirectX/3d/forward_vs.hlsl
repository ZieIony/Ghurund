#include <common.hlsli>
#include <3d.hlsli>

cbuffer vertexConstants : register(b0) {
    matrix gh_world;
    matrix gh_viewProjection;
}

DefaultPixel3D vertexMain(in DefaultVertex3D input) {
    DefaultPixel3D output;

    float4 pos = mul(float4(input.position, 1), gh_world);
    output.screenPosition = mul(pos, gh_viewProjection);
    output.position = pos.xyz;
    output.normal = normalize(mul(input.normal, gh_world)).xyz;
    output.tangent = normalize(mul(input.tangent, gh_world)).xyz;
    output.texCoord = input.texCoord;
	
    return output;
}
