#pragma once

#include "engine/directx/shader/DxShader.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Engine::DirectX;

    class DxUIShaderProvider {
    private:
        ResourceManager& manager;

        inline DxShader* load(const WString& fileName) {
            return manager.load<DxShader>(ResourcePath(ResourceManager::ENGINE_LIB_NAME, fileName), DirectoryPath());
        }

        DxUIShaderProvider& operator=(const DxUIShaderProvider& other) = delete;

    public:
        DxUIShaderProvider(ResourceManager& manager):manager(manager) {}

        DxShader* loadInvalid() {
            return load(L"/shaders/DirectX/ui/invalid.hlsl");
        }

        DxShader* loadControl() {
            return load(L"/shaders/DirectX/ui/control.hlsl");
        }

        DxShader* loadText() {
            return load(L"/shaders/DirectX/ui/text.hlsl");
        }

        DxShader* loadShadow() {
            return load(L"/shaders/DirectX/ui/shadow.hlsl");
        }
    };
}