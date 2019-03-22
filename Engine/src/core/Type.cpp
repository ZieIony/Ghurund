#include "core/Type.h"
#include "game/entity/Light.h"
#include "game/entity/Camera.h"
#include "game/entity/Scene.h"
#include "game/entity/Model.h"
#include "audio/Sound.h"
#include "script/Script.h"

namespace Ghurund {
    const Type &Type::LIGHT = Type([]() {return ghnew Light(); }, "Light");
    const Type &Type::CAMERA = Type([]() {return ghnew Camera(); }, "Camera");
    const Type &Type::SCENE = Type([]() {return ghnew Scene(); }, "Scene");
    const Type &Type::SHADER = Type([]() {return ghnew Shader(); }, "Shader");
    const Type &Type::TEXTURE = Type([]() {return ghnew Texture(); }, "Texture");
    const Type &Type::MATERIAL = Type([]() {return ghnew Material(); }, "Material");
    const Type &Type::IMAGE = Type([]() {return ghnew Image(); }, "Image");
    const Type &Type::MODEL = Type([]() {return ghnew Model(); }, "Model");
    const Type &Type::MESH = Type([]() {return ghnew Mesh(); }, "Mesh");
    const Type &Type::SOUND = Type([]() {return ghnew Sound(); }, "Sound");
    const Type &Type::COMMAND_LIST = Type([]() {return ghnew CommandList(); }, "CommandList");
    const Type &Type::SCRIPT = Type([]() {return ghnew Script(); }, "Script");
}