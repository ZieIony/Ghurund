#pragma once

#include "DxUIShaderProvider.h"

#include "engine/parameter/ParameterManager.h"
#include "ui/material/IUIMaterialProvider.h"

namespace Ghurund::UI::DirectX {
    using namespace Ghurund::UI;
    using namespace Ghurund::Engine::DirectX;

    class DxUMaterialProvider:public IUMaterialProvider {
    private:
        ParameterManager& parameterManager;
        DxUIShaderProvider& shaderProvider;

        Material* makeWithShader(DxShader* shader);

    public:
        DxUMaterialProvider(
            ParameterManager& parameterManager,
            DxUIShaderProvider& shaderProvider
        ):parameterManager(parameterManager), shaderProvider(shaderProvider) {
        }

        virtual Material* makeInvalid() override;

        virtual Material* makeControl() override;

        virtual Material* makeText() override;

        virtual Material* makeShadow() override;
    };
}