#include "ghuidxpch.h"
#include "DxUIMaterialProvider.h"

#include "engine/parameter/TextureParameter.h"
#include "engine/directx/shader/ShaderProvider.h"

namespace Ghurund::UI::DirectX {
    Material* DxUMaterialProvider::makeWithShader(DxShader* shader) {
        Material* material = nullptr;
        if (shader) {
            material = ghnew Material(shader);
        }
        return material;
    }

    Material* DxUMaterialProvider::makeInvalid() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadInvalid());
        return makeWithShader(shader.get());
    }

    Material* DxUMaterialProvider::makeControl() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadControl());
        return makeWithShader(shader.get());
    }

    Material* DxUMaterialProvider::makeText() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadText());
        return makeWithShader(shader.get());
    }

    Material* DxUMaterialProvider::makeShadow() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadShadow());
        return makeWithShader(shader.get());
    }
}