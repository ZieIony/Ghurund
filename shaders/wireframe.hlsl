cbuffer perCamera : register(b0) {
    row_major float4x4 viewProjection;
}

cbuffer perObject : register(b1) {
    row_major float4x4 world;
    float2 viewportSize;
}

struct VsInput {
    float3 position : POSITION;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float2 texCoord : TEXCOORD0;
};

struct GsInput {
    float4 position : SV_POSITION;
};

struct PsInput {
    float4 position : SV_POSITION;
    noperspective float4 edgeA: TEXCOORD0;
    noperspective float4 edgeB: TEXCOORD1;
    uint posCase:TEXCOORD2;
};

GsInput vertexMain(VsInput input) {
    GsInput output;

    output.position = mul(mul(float4(input.position, 1), world), viewProjection);

    return output;
}

static const uint infoA[] = {0, 0, 0, 0, 1, 1, 2};
static const uint infoB[] = {1, 1, 2, 0, 2, 1, 2};
static const uint infoAd[] = {2, 2, 1, 1, 0, 0, 0};
static const uint infoBd[] = {2, 2, 1, 2, 0, 2, 1};
static const float lineWidth = 1.0;
static const float fadeDistance = 1000;
static const float4 wireColor = float4(1, 1, 1, 1);

float2 projToWindow(in float4 pos) {
    return float2(viewportSize.x*0.5*((pos.x/pos.w) + 1),
                  viewportSize.y*0.5*(1-(pos.y/pos.w)));
}

[maxvertexcount(3)]
void geometryMain(triangle GsInput input[3],
                  inout TriangleStream<PsInput> outStream) {
    PsInput output;

    // Compute the posCase from the positions of point in space.
    output.posCase = (input[0].position.z < 0)*4 + (input[1].position.z < 0)*2 + (input[2].position.z < 0);

    // If posCase is all vertices behind viewpoint (posCase = 7) then cull.
    if(output.posCase == 7) return;

    // Transform position to window space
    float2 points[3];
    points[0] = projToWindow(input[0].position);
    points[1] = projToWindow(input[1].position);
    points[2] = projToWindow(input[2].position);

    // If posCase is 0, all projected points are defined, do the
    // general posCase computation
    if(output.posCase == 0) {
        output.edgeA = float4(0, 0, 0, 0);
        output.edgeB = float4(0, 0, 0, 0);

        // Compute the edges vectors of the transformed triangle
        float2 edges[3];
        edges[0] = points[1] - points[0];
        edges[1] = points[2] - points[1];
        edges[2] = points[0] - points[2];

        // Store the length of the edges
        float lengths[3];
        lengths[0] = length(edges[0]);
        lengths[1] = length(edges[1]);
        lengths[2] = length(edges[2]);

        // Compute the cos angle of each vertices
        float cosAngles[3];
        cosAngles[0] = dot(-edges[2], edges[0]) / (lengths[2] * lengths[0]);
        cosAngles[1] = dot(-edges[0], edges[1]) / (lengths[0] * lengths[1]);
        cosAngles[2] = dot(-edges[1], edges[2]) / (lengths[1] * lengths[2]);

        // The height for each vertices of the triangle
        float heights[3];
        heights[1] = lengths[0]*sqrt(1 - cosAngles[0]*cosAngles[0]);
        heights[2] = lengths[1]*sqrt(1 - cosAngles[1]*cosAngles[1]);
        heights[0] = lengths[2]*sqrt(1 - cosAngles[2]*cosAngles[2]);

        float edgeSigns[3];
        edgeSigns[0] = (edges[0].x > 0 ? 1 : -1);
        edgeSigns[1] = (edges[1].x > 0 ? 1 : -1);
        edgeSigns[2] = (edges[2].x > 0 ? 1 : -1);

        float edgeOffsets[3];
        edgeOffsets[0] = lengths[0]*(0.5 - 0.5*edgeSigns[0]);
        edgeOffsets[1] = lengths[1]*(0.5 - 0.5*edgeSigns[1]);
        edgeOffsets[2] = lengths[2]*(0.5 - 0.5*edgeSigns[2]);

        output.position = (input[0].position);
        output.edgeA[0] = 0;
        output.edgeA[1] = heights[0];
        output.edgeA[2] = 0;
        output.edgeB[0] = edgeOffsets[0];
        output.edgeB[1] = edgeOffsets[1] + edgeSigns[1] * cosAngles[1]*lengths[0];
        output.edgeB[2] = edgeOffsets[2] + edgeSigns[2] * lengths[2];
        outStream.Append(output);

        output.position = (input[1].position);
        output.edgeA[0] = 0;
        output.edgeA[1] = 0;
        output.edgeA[2] = heights[1];
        output.edgeB[0] = edgeOffsets[0] + edgeSigns[0] * lengths[0];
        output.edgeB[1] = edgeOffsets[1];
        output.edgeB[2] = edgeOffsets[2] + edgeSigns[2] * cosAngles[2]*lengths[1];
        outStream.Append(output);

        output.position = (input[2].position);
        output.edgeA[0] = heights[2];
        output.edgeA[1] = 0;
        output.edgeA[2] = 0;
        output.edgeB[0] = edgeOffsets[0] + edgeSigns[0] * cosAngles[0]*lengths[2];
        output.edgeB[1] = edgeOffsets[1] + edgeSigns[1] * lengths[1];
        output.edgeB[2] = edgeOffsets[2];
        outStream.Append(output);

        outStream.RestartStrip();
    } else {
        // Then compute and pass the edge definitions from the posCase
        output.edgeA.xy = points[infoA[output.posCase]];
        output.edgeB.xy = points[infoB[output.posCase]];

        output.edgeA.zw = normalize(output.edgeA.xy - points[infoAd[output.posCase]]);
        output.edgeB.zw = normalize(output.edgeB.xy - points[infoBd[output.posCase]]);

        // Generate vertices
        output.position = (input[0].position);
        outStream.Append(output);

        output.position = (input[1].position);
        outStream.Append(output);

        output.position = (input[2].position);
        outStream.Append(output);

        outStream.RestartStrip();
    }
}

float evalMinDistanceToEdges(in PsInput input) {
    float dist;

    // The easy posCase, the 3 distances of the fragment to the 3 edges is already
    // computed, get the min.
    if(input.posCase == 0) {
        dist = min(min(input.edgeA.x, input.edgeA.y), input.edgeA.z);
    }
    // The tricky posCase, compute the distances and get the min from the 2D lines
    // given from the geometry shader.
    else {
        // Compute and compare the sqDist, do one sqrt in the end.

        float2 AF = input.position.xy - input.edgeA.xy;
        float sqAF = dot(AF, AF);
        float AFcosA = dot(AF, input.edgeA.zw);
        dist = abs(sqAF - AFcosA*AFcosA);

        float2 BF = input.position.xy - input.edgeB.xy;
        float sqBF = dot(BF, BF);
        float BFcosB = dot(BF, input.edgeB.zw);
        dist = min(dist, abs(sqBF - BFcosB*BFcosB));

        // Only need to care about the 3rd edge for some posCases.
        if(input.posCase == 1 || input.posCase == 2 || input.posCase == 4) {
            float AFcosA0 = dot(AF, normalize(input.edgeB.xy - input.edgeA.xy));
            dist = min(dist, abs(sqAF - AFcosA0*AFcosA0));
        }

        dist = sqrt(dist);
    }

    return dist;
}

// supportsTransparency
float4 pixelMain(PsInput input): SV_Target{
    // Compute the shortest distance between the fragment and the edges.
    float dist = evalMinDistanceToEdges(input);

    // Cull fragments too far from the edge.
    if(dist > 0.5*lineWidth+1) discard;

    // Map the computed distance to the [0,2] range on the border of the line.
    dist = clamp((dist - (0.5*lineWidth - 1)), 0, 2);

    // Alpha is computed from the function exp2(-2(x)^2).
    dist *= dist;
    float alpha = exp2(-2*dist);

    float fading = clamp(fadeDistance / input.position.w, 0, 1);

    float4 color = wireColor;
    color.a *= alpha*fading;

    return color;
}
