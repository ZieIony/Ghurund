#include "resource/ResourceContext.h"
#include "game/ParameterManager.h"
#include "graphics/Image.h"
#include "graphics/Texture.h"
#include "graphics/Model.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) ResourceContext *ResourceContext_new(Graphics *graphics, Audio *audio, ParameterManager *parameterManager) {
    return new ResourceContext(*graphics, *audio, *parameterManager);
}