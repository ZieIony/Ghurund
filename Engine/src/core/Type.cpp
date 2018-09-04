#include "Type.h"
#include "graphics/Light.h"
#include "graphics/Camera.h"
#include "game/Scene.h"
#include "audio/Sound.h"

namespace Ghurund {
    const Type &Type::LIGHT = Type([]() {return ghnew Light(); }, _T("light"), 0);
    const Type &Type::CAMERA = Type([]() {return ghnew Camera(); }, _T("camera"), 1);
    const Type &Type::SCENE = Type([]() {return ghnew Scene(); }, _T("scene"), 2);
    const Type &Type::SHADER = Type([]() {return ghnew Shader(); }, _T("shader"), 3);
    const Type &Type::TEXTURE = Type([]() {return ghnew Texture(); }, _T("texture"), 4);
    const Type &Type::MATERIAL = Type([]() {return ghnew Material(); }, _T("material"), 5);
    const Type &Type::IMAGE = Type([]() {return ghnew Image(); }, _T("image"), 6);
    const Type &Type::MODEL = Type([]() {return ghnew Model(); }, _T("model"), 7);
    const Type &Type::MESH = Type([]() {return ghnew Mesh(); }, _T("mesh"), 8);
    const Type &Type::SOUND = Type([]() {return ghnew Sound(); }, _T("sound"), 9);

    const Type* Type::values[10] = {
        &Type::LIGHT,
        &Type::CAMERA,
        &Type::SCENE,
        &Type::SHADER,
        &Type::TEXTURE,
        &Type::MATERIAL,
        &Type::IMAGE,
        &Type::MODEL,
        &Type::MESH,
        &Type::SOUND
    };
}