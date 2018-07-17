#include "resource/ResourceManager.h"
#include "game/ParameterManager.h"
#include "graphics/Image.h"
#include "graphics/Texture.h"
#include "graphics/Model.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) ResourceManager *ResourceManager_new(Graphics *graphics, ParameterManager *parameterManager) {
    return new ResourceManager(*graphics, *parameterManager);
}

template<class Type> void load(ResourceManager *_this, const tchar *fileName, void(__stdcall *loadCallback)(Status status)) {
    _this->load<Type>(fileName, [loadCallback](std::shared_ptr<Type> &resource, Status status) {
        loadCallback(status);
    });
}

extern "C" __declspec(dllexport) void ResourceManager_loadImage(ResourceManager *_this, const tchar *fileName, void(__stdcall *loadCallback)(Status status)) {
    load<Image>(_this, fileName, loadCallback);
}

extern "C" __declspec(dllexport) void ResourceManager_loadTexture(ResourceManager *_this, const tchar *fileName, void(__stdcall *loadCallback)(Status status)) {
    load<Texture>(_this, fileName, loadCallback);
}

extern "C" __declspec(dllexport) void ResourceManager_loadModel(ResourceManager *_this, const tchar *fileName, void(__stdcall *loadCallback)(Status status)) {
    load<Model>(_this, fileName, loadCallback);
}
