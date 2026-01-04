#pragma once

#include "Material.h"

#include "engine/graphics/shader/IShaderProvider.h"
#include "engine/graphics/texture/TextureProvider.h"

namespace Ghurund::Engine {

    class MaterialProvider: public Noncopyable {
    private:
        ParameterManager& parameterManager;
        IShaderProvider& shaderProvider;
        TextureProvider& textureProvider;
        IGPUMemoryManager& memoryManager;

        Material* makeWithShader(Shader *shader) const;

    public:
        MaterialProvider(
            ParameterManager& parameterManager,
            IShaderProvider& shaderProvider,
            TextureProvider& textureProvider,
            IGPUMemoryManager& memoryManager
		):parameterManager(parameterManager), shaderProvider(shaderProvider), textureProvider(textureProvider), memoryManager(memoryManager) {
		}

        Material* makeBasic(ITexture* texture = nullptr) const;

        Material* makeBasicLight(
            ITexture* diffuseTexture = nullptr,
            ITexture* specularTexture = nullptr,
            ITexture* normalTexture = nullptr
        ) const;

        Material* makeChecker() const;

        Material* makeWireframe() const;

        Material* makeOutline() const;

        Material* makeNormals() const;

        Material* makeInvalid() const;

        Material* makeLightPass() const;

        Material* makeBasicSky() const;

        Material* makeAdvancedSky() const;
	};
}