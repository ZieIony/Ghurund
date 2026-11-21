#include <globalParameters.hlsli>
#include <objectParameters.hlsli>
#include <common.hlsli>
#include <3d.hlsli>

DefaultPixel3D vertexMain(in DefaultVertex3D input, ObjectParameters objectParameters) {
    DefaultPixel3D output;

    float4 pos = mul(float4(input.position, 1), objectParameters.world);
    output.screenPosition = mul(pos, gh_viewProjection);
    output.position = pos.xyz;
    output.normal = normalize(mul(input.normal, objectParameters.world)).xyz;
    output.tangent = normalize(mul(input.tangent, objectParameters.world)).xyz;
    output.texCoord = input.texCoord;
	
    return output;
}
