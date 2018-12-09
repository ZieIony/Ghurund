#include "graphics/Material.h"
#include "graphics/Materials.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Material *Material_new() {
    return new Material();
}

extern "C" __declspec(dllexport) Material *Materials_makeChecker(ResourceManager *resourceManager, ResourceContext *context) {
    return Materials::makeChecker(*resourceManager, *context);
}

extern "C" __declspec(dllexport) Material *Materials_makeWireframe(ResourceManager *resourceManager, ResourceContext *context) {
    return Materials::makeWireframe(*resourceManager, *context);
}

extern "C" __declspec(dllexport) Material *Materials_makeNormals(ResourceManager *resourceManager, ResourceContext *context) {
    return Materials::makeNormals(*resourceManager, *context);
}
