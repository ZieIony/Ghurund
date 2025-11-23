#include "ghuidxpch.h"
#include "DxUIMaterialProvider.h"

#include "engine/parameter/TextureParameter.h"
#include "engine/directx/shader/ShaderProvider.h"

namespace Ghurund::UI::DirectX {
    DxMaterial* DxUIMaterialProvider::makeWithShader(DxShader* shader) {
        DxMaterial* material = nullptr;
        if (shader) {
            material = ghnew DxMaterial(shader);
        }
        return material;
    }

    IMaterial* DxUIMaterialProvider::makeInvalid() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadInvalid());
        return makeWithShader(shader.get());
    }

    IMaterial* DxUIMaterialProvider::makeControl() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadControl());
        return makeWithShader(shader.get());
    }

    IMaterial* DxUIMaterialProvider::makeText() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadText());
        return makeWithShader(shader.get());
    }

    IMaterial* DxUIMaterialProvider::makeShadow() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadShadow());
        return makeWithShader(shader.get());
    }
}