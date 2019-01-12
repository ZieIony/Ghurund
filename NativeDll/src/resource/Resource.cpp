#include "resource/Resource.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Status Resource_load(Resource *_this, ResourceManager *manager, ResourceContext *context, const tchar *fileName) {
    return _this->load(*manager, *context, fileName);
}

extern "C" __declspec(dllexport) Status Resource_save(Resource *_this, ResourceManager *manager, const tchar *fileName) {
    return _this->save(*manager, fileName);
}

extern "C" __declspec(dllexport) void Resource_setFileName(Resource *_this, const wchar_t *fileName) {
    _this->setFileName(fileName);
}

extern "C" __declspec(dllexport) wchar_t *Resource_getFileName(Resource *_this) {
    return copyStr(_this->getFileName());
}

extern "C" __declspec(dllexport) const tchar *ResourceFormat_getExtension(ResourceFormat *_this) {
    return copyStr(_this->getExtension());
}

extern "C" __declspec(dllexport) const ResourceFormat** ResourceFormat_getValues() {
    return ResourceFormat::getValues();
}

extern "C" __declspec(dllexport) size_t ResourceFormat_getValueCount() {
    return ResourceFormat::getValueCount();
}

extern "C" __declspec(dllexport) bool ResourceFormat_canSave(ResourceFormat *_this) {
    return _this->canSave();
}

extern "C" __declspec(dllexport) bool ResourceFormat_canLoad(ResourceFormat *_this) {
    return _this->canLoad();
}

extern "C" __declspec(dllexport) void Resource_setValid(Resource *_this, BOOL valid) {
    _this->setValid(valid);
}

extern "C" __declspec(dllexport) BOOL Resource_isValid(Resource *_this) {
    return _this->isValid();
}