#include "graphics/Material.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) shared_ptr<Material> *Material_new() {
    return new shared_ptr<Material>(new Material());
}

/*extern "C" __declspec(dllexport) void materialLoad(shared_ptr<Material> *material, ResourceManager &*resourceManager) {
    (*material)->load();
}*/
