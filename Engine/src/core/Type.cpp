#include "audio/Sound.h"
#include "core/Type.h"
#include "graphics/entity/Light.h"
#include "graphics/entity/Camera.h"
#include "graphics/entity/Scene.h"
#include "script/Script.h"

namespace Ghurund {
    const Type &Type::LIGHT = Type([]() {return ghnew Light(); }, "Light");
    const Type &Type::CAMERA = Type([]() {return ghnew Camera(); }, "Camera");
    const Type &Type::SCENE = Type([]() {return ghnew Scene(); }, "Scene");
    const Type &Type::SHADER = Type([]() {return ghnew Shader(); }, "Shader");
    const Type &Type::TEXTURE = Type([]() {return ghnew Texture(); }, "Texture");
    const Type &Type::MATERIAL = Type([]() {return ghnew Material(); }, "Material");
    const Type &Type::IMAGE = Type([]() {return ghnew Image(); }, "Image");
    const Type &Type::MESH = Type([]() {return ghnew Mesh(); }, "Mesh");
    const Type &Type::SOUND = Type([]() {return ghnew Sound(); }, "Sound");
    const Type &Type::COMMAND_LIST = Type([]() {return ghnew CommandList(); }, "CommandList");
    const Type &Type::SCRIPT = Type([]() {return ghnew Script(); }, "Script");
}