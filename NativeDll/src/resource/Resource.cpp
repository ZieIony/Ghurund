#include "resource/Resource.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Status Resource_load(Resource *_this, ResourceManager *manager, const tchar *fileName) {
    return _this->load(*manager, fileName);
}

extern "C" __declspec(dllexport) Status Resource_save(Resource *_this, ResourceManager *manager, const tchar *fileName) {
    return _this->save(*manager, fileName);
}

extern "C" __declspec(dllexport) const ResourceFormat *Resource_getDefaultFormat(Resource *_this) {
    return &_this->getDefaultFormat();
}