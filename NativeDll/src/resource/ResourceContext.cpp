#include "resource/ResourceContext.h"
#include "game/entity/Model.h"
#include "game/parameter/ParameterManager.h"
#include "graphics/texture/Image.h"
#include "graphics/texture/Texture.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) ResourceContext *ResourceContext_new(Graphics *graphics, Audio *audio, ParameterManager *parameterManager) {
    return new ResourceContext(*graphics, *audio, *parameterManager);
}

extern "C" __declspec(dllexport) void ResourceContext_delete(ResourceContext *_this) {
    delete _this;
}
