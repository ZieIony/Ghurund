#ifndef COLORS_HLSLI
#define COLORS_HLSLI

#include <common.hlsli>

const float4 WHITE = float4(1, 1, 1, 1);
const float4 BLACK = float4(1, 1, 1, 1);

matrix makeSaturationMatrix(float sat) {
    matrix m = MATRIX_IDENTITY;
    
    /*
    Where rwgt is 0.3086, gwgt is 0.6094, and bwgt is 0.0820.This is the luminance vector. Notice
    here that we do not usethe standard NTSC weights of 0.299, 0.587, and 0.114.The NTSC weights
    are only applicable to RGB colorsin a gamma 2.2 color space. For linear RGB colors the values
    above are better.
    */
    
    float invSat = 1 - sat;
    float R = 0.213f * invSat;
    float G = 0.715f * invSat;
    float B = 0.072f * invSat;

    m[0][0] = R + sat;
    m[1][0] = G;
    m[2][0] = B;
    m[0][1] = R;
    m[1][1] = G + sat;
    m[2][1] = B;
    m[0][2] = R;
    m[1][2] = G;
    m[2][2] = B + sat;
    
    return m;
}

matrix makeBrightnessMatrix(float b) {
    matrix m = MATRIX_IDENTITY;
    
    m[0][0] = b;
    m[1][1] = b;
    m[2][2] = b;
    
    return m;
}

#endif