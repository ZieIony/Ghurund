#include "editor/CameraUtils.h"
#include "../Float3.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Float3 CameraUtils_screenVectorTo3D(Float2 screenVector, Camera* camera) {
    return convertFloat3(CameraUtils::screenVectorTo3D(convertFloat2(screenVector), *camera));
}