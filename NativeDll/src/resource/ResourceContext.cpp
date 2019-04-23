#include "resource/ResourceContext.h"
#include "game/entity/Model.h"
#include "game/parameter/ParameterManager.h"
#include "graphics/texture/Image.h"
#include "graphics/texture/Texture.h"
#include "script/ScriptEngine.h"
#include "physics/Physics.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) ResourceContext* ResourceContext_new(Graphics* graphics, Audio* audio, ParameterManager* parameterManager, ScriptEngine* scriptEngine, Physics* physics) {
    return new ResourceContext(*graphics, *audio, *parameterManager, *scriptEngine, *physics);
}
