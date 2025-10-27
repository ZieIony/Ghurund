#pragma once

#include "engine/directx/texture/Texture.h"
#include "engine/graphics/IMaterialProvider.h"
#include "Material.h"
#include "engine/directx/shader/ShaderProvider.h"
#include "engine/directx/texture/TextureProvider.h"

namespace Ghurund::Engine::DirectX {

    class MaterialProvider: public IMaterialProvider {
    private:
        ParameterManager* parameterManager;
        ShaderProvider* shaderProvider;
        TextureProvider* textureProvider;

        Material* makeWithShader(DxShader *shader);

    public:
        MaterialProvider(
            NotNull<ParameterManager> parameterManager,
            NotNull<ShaderProvider> shaderProvider,
            NotNull<TextureProvider> textureProvider
		):parameterManager(&parameterManager), shaderProvider(&shaderProvider), textureProvider(&textureProvider) {
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

        virtual Material* makeUi() override;

        virtual Material* makeBasicSky() override;

        virtual Material* makeAdvancedSky() override;
	};
}