#pragma once

#include "DxMaterial.h"
#include "engine/graphics/material/IMaterialFactory.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class DxMaterialFactory:public IMaterialFactory {
    public:
        virtual IMaterial* makeMaterial(IShader* shader) override {
            auto material = ghnew DxMaterial();
            material->Shader = (DxShader*)shader;
            return material;
        }
    };
}