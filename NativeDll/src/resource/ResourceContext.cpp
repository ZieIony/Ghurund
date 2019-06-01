#include "resource/ResourceContext.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) ResourceContext* ResourceContext_new(
    Graphics* graphics, Audio* audio, ParameterManager* parameterManager, ScriptEngine* scriptEngine, Physics* physics, ResourceManager *resourceManager) {
    return new ResourceContext(*graphics, *audio, *parameterManager, *scriptEngine, *physics, *resourceManager);
}

extern "C" __declspec(dllexport) Status ResourceContext_init(ResourceContext* _this) {
    return _this->init();
}
