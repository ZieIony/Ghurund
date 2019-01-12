cbuffer perCamera : register(b0) {
    row_major float4x4 viewProjection;
    row_major float4x4 world;

    float4 lightPos;
    float4 camPos;

    float3 v3LightDir;      // Direction vector to the light source
    float3 v3InvWavelength; // 1 / pow(wavelength, 4) for RGB

    float fCameraHeight;    // The camera's current height
    float fCameraHeight2;   // fCameraHeight^2
    float fOuterRadius;     // The outer (atmosphere) radius
    float fOuterRadius2;    // fOuterRadius^2

    float fInnerRadius;     // The inner (planetary) radius
    float fInnerRadius2;    // fInnerRadius^2
    float fKrESun;          // Kr * ESun
    float fKmESun;          // Km * ESun

    float fKr4PI;           // Kr * 4 * PI
    float fKm4PI;           // Km * 4 * PI
    float fScale;           // 1 / (fOuterRadius - fInnerRadius)
    float fScaleDepth;

    float fInvScaleDepth;
    float fScaleOverScaleDepth; // fScale / fScaleDepth
    float fSamples;

    float3 v3LightDirection;

    float g;
    float g2;
}

struct VsInput {
    float3 position : POSITION;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float2 texCoord : TEXCOORD0;
};

struct PsInput {
    float4 position	: sv_position;
    float3 c0	: texCoord0;
    float3 c1	: texCoord1;
    float3 t0	: texCoord2;
};

// The scale equation calculated by Vernier's Graphical Analysis
float scale(float fCos) {
    float x = 1.0 - fCos;
    return fScaleDepth * exp(-0.00287 + x*(0.459 + x*(3.83 + x*(-6.80 + x*5.25))));
}

// Calculates the Mie phase function
float getMiePhase(float fCos, float fCos2, float g, float g2) {
    return 1.5 * ((1.0 - g2) / (2.0 + g2)) * (1.0 + fCos2) / pow(1.0 + g2 - 2.0*g*fCos, 1.5);
}

// Calculates the Rayleigh phase function
float getRayleighPhase(float fCos2) {
    //return 1.0;
    return 0.75 + 0.75*fCos2;
}

// Returns the near intersection point of a line and a sphere
float getNearIntersection(float3 v3Pos, float3 v3Ray, float fDistance2, float fRadius2) {
    float B = 2.0 * dot(v3Pos, v3Ray);
    float C = fDistance2 - fRadius2;
    float fDet = max(0.0, B*B - 4.0 * C);
    return 0.5 * (-B - sqrt(fDet));
}

// Returns the far intersection point of a line and a sphere
float getFarIntersection(float3 v3Pos, float3 v3Ray, float fDistance2, float fRadius2) {
    float B = 2.0 * dot(v3Pos, v3Ray);
    float C = fDistance2 - fRadius2;
    float fDet = max(0.0, B*B - 4.0 * C);
    return 0.5 * (-B + sqrt(fDet));
}

Vertex2Geometry vertexMain(App2Vertex vsIn) {
    Vertex2Geometry vsOut;

    float3 v3Pos = mul(float4(vsIn.position.xyz, 1), world).xyz;
    float3 v3Ray = v3Pos - camPos;
    float fFar = length(v3Ray);
    v3Ray /= fFar;

    // Calculate the ray's starting position, then calculate its scattering offset
    float3 v3Start = float3(0, fCameraHeight, 0);//camPos;
    float fHeight = length(v3Start);
    float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fCameraHeight));
    float fStartAngle = dot(v3Ray, v3Start) / fHeight;
    float fStartOffset = fDepth*scale(fStartAngle);

    // Initialize the scattering loop variables
    //gl_FrontColor = vec4(0.0, 0.0, 0.0, 0.0);
    float fSampleLength = fFar / fSamples;
    float fScaledLength = fSampleLength * fScale;
    float3 v3SampleRay = v3Ray * fSampleLength;
    float3 v3SamplePoint = v3Start + v3SampleRay * 0.5;

    // Now loop through the sample rays
    float3 v3FrontColor = float3(0.0, 0.0, 0.0);
    for(int i = 0; i<fSamples; i++) {
        float fHeight = length(v3SamplePoint);
        float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fHeight));
        float fLightAngle = dot(normalize(-v3LightDir), v3SamplePoint) / fHeight;
        float fCameraAngle = dot(v3Ray, v3SamplePoint) / fHeight;
        float fScatter = (fStartOffset + fDepth*(scale(fLightAngle) - scale(fCameraAngle)));
        float3 v3Attenuate = exp(-fScatter * (v3InvWavelength * fKr4PI + fKm4PI));
        v3FrontColor += v3Attenuate * (fDepth * fScaledLength);
        v3SamplePoint += v3SampleRay;
    }

    // Finally, scale the Mie and Rayleigh colors and set up the varying variables for the pixel shader
    vsOut.c1.rgb = v3FrontColor * fKmESun;
    vsOut.c0.rgb = v3FrontColor * (v3InvWavelength * fKrESun);
    vsOut.position = mul(mul(float4(vsIn.position.xyz, 1), world), viewProj);
    vsOut.t0 = camPos - v3Pos;

    return vsOut;
}

float4 pixelMain(PsInput psIn):sv_target{
    float fCos = dot(-v3LightDirection, psIn.t0) / length(psIn.t0);
    float fCos2 = fCos * fCos;
    float fExposure = 2.0f;
    float3 color2 = getRayleighPhase(fCos2) * psIn.c0 +
                    getMiePhase(fCos, fCos2, g, g2) * psIn.c1;
    float4 color = float4(1.0 - exp(-fExposure *color2),1);
    return color;
}
