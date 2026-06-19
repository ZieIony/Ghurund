#include <common.hlsli>
#include <3d.hlsli>

cbuffer vertexConstants: register(b0) {
    matrix gh_world;
    matrix gh_viewProjection;
}

Pixel3D vertexMain(Vertex3D input) {
    Pixel3D output;

    float4 inputPos = float4(input.position, 1);
    output.position = mul(mul(inputPos, gh_world), gh_viewProjection);
    output.normal = normalize(mul(input.normal, (float3x3)gh_world));
    //output.tangent = normalize(mul(input.tangent, world)).xyz;
    output.texCoord = input.texCoord;

    return output;
}
