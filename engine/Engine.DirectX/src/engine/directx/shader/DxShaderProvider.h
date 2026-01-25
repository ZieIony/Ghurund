#pragma once

#include "engine/directx/shader/DxShader.h"
#include "engine/graphics/shader/IShaderProvider.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Engine::DirectX;

	class DxShaderProvider:public IShaderProvider {
	private:
		ResourceManager& manager;

		inline DxShader* load(const WString& fileName) {
			return manager.load<DxShader>(ResourceManager::ENGINE_LIB / FilePath(fileName), DirectoryPath());
		}

		DxShaderProvider& operator=(const DxShaderProvider& other) = delete;

	public:
		DxShaderProvider(ResourceManager& manager):manager(manager) {}

		virtual DxShader* loadBasic() override {
			return load(L"/shaders/DirectX/basic.hlsl");
		}

		virtual DxShader* loadBasicLight() override {
			return load(L"/shaders/DirectX/basicLight.hlsl");
		}

		virtual DxShader* loadWireframe() override {
			return load(L"/shaders/DirectX/wireframe.hlsl");
		}

		virtual DxShader* loadOutline() override {
			return load(L"/shaders/DirectX/outline.hlsl");
		}

		virtual DxShader* loadNormals() override {
			return load(L"/shaders/DirectX/normals.hlsl");
		}

		virtual DxShader* loadInvalid() override {
			return load(L"/shaders/DirectX/invalid.hlsl");
		}

		virtual DxShader* loadLightPass() override {
			return load(L"/shaders/DirectX/lightPass.hlsl");
		}

		virtual DxShader* loadBasicSky() override {
			return load(L"/shaders/DirectX/basicSky.hlsl");
		}

		virtual DxShader* loadAdvancedSky() override {
			return load(L"/shaders/DirectX/advancedSky.hlsl");
		}
	};
}