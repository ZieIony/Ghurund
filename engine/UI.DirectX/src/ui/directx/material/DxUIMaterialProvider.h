#pragma once

#include "DxUIShaderProvider.h"

#include "engine/directx/material/DxMaterial.h"
#include "engine/parameter/ParameterManager.h"
#include "ui/material/IUIMaterialProvider.h"

namespace Ghurund::UI::DirectX {
    using namespace Ghurund::UI;
    using namespace Ghurund::Engine::DirectX;

    class DxUIMaterialProvider:public IUIMaterialProvider {
    private:
        ParameterManager& parameterManager;
        DxUIShaderProvider& shaderProvider;

        DxMaterial* makeWithShader(DxShader* shader);

    public:
        DxUIMaterialProvider(
            ParameterManager& parameterManager,
            DxUIShaderProvider& shaderProvider
        ):parameterManager(parameterManager), shaderProvider(shaderProvider) {
        }

        virtual IMaterial* makeInvalid() override;

        virtual IMaterial* makeControl() override;

        virtual IMaterial* makeText() override;

        virtual IMaterial* makeShadow() override;
    };
}