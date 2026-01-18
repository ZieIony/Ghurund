#pragma once

#include "ui/material/UIMaterial.h"
#include "ui/shader/IUIShaderProvider.h"

namespace Ghurund::UI {

    class UIMaterialProvider:public Noncopyable {
    private:
        IUIShaderProvider& shaderProvider;
        IGPUMemoryManager& memoryManager;

        UIMaterial* makeWithShader(Shader* shader) const {
            UIMaterial* material = nullptr;
            if (shader) {
                material = ghnew UIMaterial(memoryManager);
                material->Shader = shader;
            }
            return material;
        }

    public:
		UIMaterialProvider(
            IUIShaderProvider& shaderProvider,
            IGPUMemoryManager& memoryManager
        ): shaderProvider(shaderProvider), memoryManager(memoryManager) {}

        inline UIMaterial* makeInvalid() const {
            IntrusivePointer<Shader> shader(shaderProvider.loadInvalid());
            return makeWithShader(shader.get());
        }

        inline UIMaterial* makeControl() const {
            IntrusivePointer<Shader> shader(shaderProvider.loadControl());
            return makeWithShader(shader.get());
        }

        inline UIMaterial* makeText() const {
            IntrusivePointer<Shader> shader(shaderProvider.loadText());
            return makeWithShader(shader.get());
        }

        inline UIMaterial* makeShadow() const {
            IntrusivePointer<Shader> shader(shaderProvider.loadShadow());
            return makeWithShader(shader.get());
        }
    };
}