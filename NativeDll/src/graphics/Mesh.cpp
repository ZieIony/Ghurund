#include "graphics/mesh/Mesh.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Mesh *Mesh_new() {
    return new Mesh();
}

extern "C" __declspec(dllexport) const Array<ResourceFormat*> *Mesh_getFormats() {
    return &Mesh::getFormats();
}