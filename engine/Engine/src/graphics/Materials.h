#pragma once

#include "Material.h"
#include "shader/Shaders.h"
#include "texture/Textures.h"

namespace Ghurund {
    class Materials {
    private:
        Materials() = delete;

        static Material* makeWithShader(Shader *shader, ParameterManager& parameterManager);

    public:
        static Material* makeBasic(ResourceManager& manager, ParameterManager& parameterManager, Texture* texture = nullptr);

        static Material* makeBasicLight(ResourceManager& manager, ParameterManager& parameterManager, Texture* diffuseTexture = nullptr, Texture* specularTexture = nullptr, Texture* normalTexture = nullptr);

        static Material* makeToon(ResourceManager& manager, ParameterManager& parameterManager, Texture* texture = nullptr);

        static Material* makeChecker(ResourceManager& manager, Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager);

        static Material* makeWireframe(ResourceManager& manager, ParameterManager& parameterManager);

        static Material* makeOutline(ResourceManager& manager, ParameterManager& parameterManager);

        static Material* makeNormals(ResourceManager& manager, ParameterManager& parameterManager);

        static Material* makeInvalid(ResourceManager& manager, ParameterManager& parameterManager);

        static Material* makeLightPass(ResourceManager& manager, ParameterManager& parameterManager);

        static Material* makeUi(ResourceManager& manager, ParameterManager& parameterManager);

		static Material* makeBasicSky(ResourceManager& manager, ParameterManager& parameterManager);

		static Material* makeAdvancedSky(ResourceManager& manager, ParameterManager& parameterManager);
	};
}