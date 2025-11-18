#pragma once

#include "engine/directx/texture/Texture.h"
#include "engine/graphics/IMaterialProvider.h"
#include "DxMaterial.h"
#include "engine/directx/shader/ShaderProvider.h"
#include "engine/directx/texture/TextureProvider.h"

namespace Ghurund::Engine::DirectX {

    class MaterialProvider: public IMaterialProvider {
    private:
        ParameterManager& parameterManager;
        ShaderProvider& shaderProvider;
        TextureProvider& textureProvider;

        DxMaterial* makeWithShader(DxShader *shader);

    public:
        MaterialProvider(
            ParameterManager& parameterManager,
            ShaderProvider& shaderProvider,
            TextureProvider& textureProvider
		):parameterManager(parameterManager), shaderProvider(shaderProvider), textureProvider(textureProvider) {
		}

        virtual DxMaterial* makeBasic(ITexture* texture = nullptr) override;

        virtual DxMaterial* makeBasicLight(
            ITexture* diffuseTexture = nullptr,
            ITexture* specularTexture = nullptr,
            ITexture* normalTexture = nullptr
        ) override;

        virtual DxMaterial* makeToon(ITexture* texture = nullptr) override;

        virtual DxMaterial* makeChecker() override;

        virtual DxMaterial* makeWireframe() override;

        virtual DxMaterial* makeOutline() override;

        virtual DxMaterial* makeNormals() override;

        virtual DxMaterial* makeInvalid() override;

        virtual DxMaterial* makeLightPass() override;

        virtual DxMaterial* makeUi() override;

        virtual DxMaterial* makeText() override;

        virtual DxMaterial* makeBasicSky() override;

        virtual DxMaterial* makeAdvancedSky() override;
	};
}