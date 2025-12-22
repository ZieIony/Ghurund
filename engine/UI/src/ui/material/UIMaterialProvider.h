#pragma once

#include "ui/shader/IUIShaderProvider.h"

#include <engine/graphics/material/Material.h>

namespace Ghurund::UI {

    class UIMaterialProvider:public Noncopyable {
    private:
        IUIShaderProvider& shaderProvider;

        Material* makeWithShader(IShader* shader) const {
            Material* material = nullptr;
            if (shader)
                material = ghnew Material(shader);
            return material;
        }

    public:
		UIMaterialProvider(IUIShaderProvider& shaderProvider): shaderProvider(shaderProvider) {}

        inline Material* makeInvalid() const {
            IntrusivePointer<IShader> shader(shaderProvider.loadInvalid());
            return makeWithShader(shader.get());
        }

        inline Material* makeControl() const {
            IntrusivePointer<IShader> shader(shaderProvider.loadControl());
            return makeWithShader(shader.get());
        }

        inline Material* makeText() const {
            IntrusivePointer<IShader> shader(shaderProvider.loadText());
            return makeWithShader(shader.get());
        }

        inline Material* makeShadow() const {
            IntrusivePointer<IShader> shader(shaderProvider.loadShadow());
            return makeWithShader(shader.get());
        }
    };
}