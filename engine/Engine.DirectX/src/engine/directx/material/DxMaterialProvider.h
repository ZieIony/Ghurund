#pragma once

#include "engine/directx/texture/DxTexture.h"
#include "engine/graphics/material/MaterialProvider.h"
#include "engine/directx/shader/ShaderProvider.h"
#include "engine/directx/texture/TextureProvider.h"

namespace Ghurund::Engine::DirectX {

    class DxMaterialProvider: public MaterialProvider {
    private:
        ParameterManager& parameterManager;
        ShaderProvider& shaderProvider;
        TextureProvider& textureProvider;

        Material* makeWithShader(DxShader *shader);

    public:
        DxMaterialProvider(
            ParameterManager& parameterManager,
            ShaderProvider& shaderProvider,
            TextureProvider& textureProvider
		):parameterManager(parameterManager), shaderProvider(shaderProvider), textureProvider(textureProvider) {
		}

        virtual Material* makeBasic(ITexture* texture = nullptr) override;

        virtual Material* makeBasicLight(
            ITexture* diffuseTexture = nullptr,
            ITexture* specularTexture = nullptr,
            ITexture* normalTexture = nullptr
        ) override;

        virtual Material* makeToon(ITexture* texture = nullptr) override;

        virtual Material* makeChecker() override;

        virtual Material* makeWireframe() override;

        virtual Material* makeOutline() override;

        virtual Material* makeNormals() override;

        virtual Material* makeInvalid() override;

        virtual Material* makeLightPass() override;

        virtual Material* makeBasicSky() override;

        virtual Material* makeAdvancedSky() override;
	};
}