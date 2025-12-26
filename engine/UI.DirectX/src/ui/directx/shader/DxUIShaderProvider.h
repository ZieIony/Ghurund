#pragma once

#include "engine/directx/shader/DxShader.h"
#include "ui/shader/IUIShaderProvider.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::UI;
    using namespace Ghurund::Engine::DirectX;

    class DxUIShaderProvider:public IUIShaderProvider {
    private:
        ResourceManager& manager;

        inline DxShader* load(const WString& fileName) const {
			return manager.load<DxShader>(ResourceManager::ENGINE_LIB / FilePath(fileName));
        }

        DxUIShaderProvider& operator=(const DxUIShaderProvider& other) = delete;

    public:
        DxUIShaderProvider(ResourceManager& manager):manager(manager) {}

        virtual DxShader* loadInvalid() const override {
            return load(L"/shaders/DirectX/ui/invalid.hlsl");
        }

        virtual DxShader* loadControl() const override {
            return load(L"/shaders/DirectX/ui/control.hlsl");
        }

        virtual DxShader* loadText() const override {
            return load(L"/shaders/DirectX/ui/text.hlsl");
        }

        virtual DxShader* loadShadow() const override {
            return load(L"/shaders/DirectX/ui/shadow.hlsl");
        }
    };
}