#include "resource/ResourceManager.h"
#include "game/entity/Model.h"
#include "game/parameter/ParameterManager.h"
#include "graphics/texture/Image.h"
#include "graphics/texture/Texture.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) ResourceManager *ResourceManager_new() {
    ResourceManager *resourceManager = new ResourceManager();
    resourceManager->Libraries.add(L"main", DirectoryPath(L"\\"));
    return resourceManager;
}

template<class Type> void load(ResourceManager *_this, ResourceContext &context, const tchar *fileName, void(__stdcall *loadCallback)(Status status)) {
/*    _this->load<Type>(fileName, [loadCallback](std::shared_ptr<Type> &resource, Status status) {
        loadCallback(status);
    });*/
}

extern "C" __declspec(dllexport) void ResourceManager_loadImage(ResourceManager *_this, ResourceContext *context, const tchar *fileName, void(__stdcall *loadCallback)(Status status)) {
    load<Image>(_this, *context, fileName, loadCallback);
}

extern "C" __declspec(dllexport) void ResourceManager_loadTexture(ResourceManager *_this, ResourceContext *context, const tchar *fileName, void(__stdcall *loadCallback)(Status status)) {
    load<Texture>(_this, *context, fileName, loadCallback);
}

extern "C" __declspec(dllexport) void ResourceManager_loadModel(ResourceManager *_this, ResourceContext *context, const tchar *fileName, void(__stdcall *loadCallback)(Status status)) {
    load<Model>(_this, *context, fileName, loadCallback);
}
