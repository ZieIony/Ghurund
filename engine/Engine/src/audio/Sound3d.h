#pragma once

#include "Common.h"

#include <xaudio2.h>
#include <x3daudio.h>

#include <mfapi.h>
#include <mfidl.h>

#include "Sound.h"

namespace Ghurund::Audio {
    using namespace ::DirectX;
 
    class Sound3D:public Sound {
    private:
        X3DAUDIO_EMITTER emitter = { 0 };	// sound source's position

    public:
        Sound3D() {
            emitter.ChannelCount = 1;
            emitter.CurveDistanceScaler = FLT_MIN;

            /*X3DAUDIO_DSP_SETTINGS DSPSettings = { 0 };
            FLOAT32* matrix = new FLOAT32[deviceDetails.OutputFormat.Format.nChannels];
            DSPSettings.SrcChannelCount = 1;
            DSPSettings.DstChannelCount = deviceDetails.OutputFormat.Format.nChannels;
            DSPSettings.pMatrixCoefficients = matrix;*/
        }
    };
}