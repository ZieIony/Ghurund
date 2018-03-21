#include "resource/ResourceManager.h"
#include "game/ParameterManager.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) ResourceManager *ResourceManager_new(Graphics *graphics, ParameterManager *parameterManager) {
    return new ResourceManager(*graphics, *parameterManager);
}
