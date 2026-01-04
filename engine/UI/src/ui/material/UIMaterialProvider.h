#pragma once

#include "ui/shader/IUIShaderProvider.h"

#include <engine/graphics/material/Material.h>

namespace Ghurund::UI {

    class UIMaterialProvider:public Noncopyable {
    private:
        IUIShaderProvider& shaderProvider;
        IGPUMemoryManager& memoryManager;

        Material* makeWithShader(Shader* shader) const {
            Material* material = nullptr;
            if (shader)
                material = ghnew Material(memoryManager, shader);
            return material;
        }

    public:
		UIMaterialProvider(
            IUIShaderProvider& shaderProvider,
            IGPUMemoryManager& memoryManager
        ): shaderProvider(shaderProvider), memoryManager(memoryManager) {}

        inline Material* makeInvalid() const {
            IntrusivePointer<Shader> shader(shaderProvider.loadInvalid());
            return makeWithShader(shader.get());
        }

        inline Material* makeControl() const {
            IntrusivePointer<Shader> shader(shaderProvider.loadControl());
            return makeWithShader(shader.get());
        }

        inline Material* makeText() const {
            IntrusivePointer<Shader> shader(shaderProvider.loadText());
            return makeWithShader(shader.get());
        }

        inline Material* makeShadow() const {
            IntrusivePointer<Shader> shader(shaderProvider.loadShadow());
            return makeWithShader(shader.get());
        }
    };
}