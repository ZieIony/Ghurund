#pragma once

#include "ShaderConstant.h"

namespace Ghurund::Engine::DirectX {
    class TextureConstant:public ShaderConstant {
    private:
        IntrusivePointer<TextureParameter> parameter;

    public:
        TextureConstant(const char *name, unsigned int bindPoint, D3D12_SHADER_VISIBILITY visibility):ShaderConstant(name, bindPoint, visibility) {
            parameter = makeIntrusive<TextureParameter>(name);
        }

        inline TextureParameter* getParameter() const {
            return parameter.get();
        }

        __declspec(property(get = getParameter)) TextureParameter* Parameter;
    };
}