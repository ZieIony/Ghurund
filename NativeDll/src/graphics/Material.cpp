#include "graphics/Material.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Material *Material_new() {
    return new Material();
}

/*extern "C" __declspec(dllexport) void materialLoad(shared_ptr<Material> *material, ResourceManager &*resourceManager) {
    (*material)->load();
}*/
