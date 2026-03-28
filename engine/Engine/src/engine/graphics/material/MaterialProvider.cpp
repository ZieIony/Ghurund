#include "ghepch.h"
#include "MaterialProvider.h"

#include "engine/parameter/TextureParameter.h"

namespace Ghurund::Engine {
	Material* MaterialProvider::makeWithShader(Shader* shader) const {
		Material* material = nullptr;
		if (shader) {
			material = ghnew Material();
			material->init(memoryManager);
			material->Shader = shader;
		}
		return material;
	}

	Material* MaterialProvider::makeBasic(ITexture* diffuseTexture) const {
		Material* material = nullptr;
		IntrusivePointer<Shader> shader(shaderProvider.loadBasic());
		if (shader != nullptr) {
			material = ghnew Material();
			material->init(memoryManager);
			material->Shader = shader.get();
			/*if (diffuseTexture) {
				TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
				diffuse->setValue(diffuseTexture);
			}*/
		}
		return material;
	}

	Material* MaterialProvider::makeBasicLight(ITexture* diffuseTexture, ITexture* specularTexture, ITexture* normalTexture) const {
		Material* material = nullptr;
		IntrusivePointer<Shader> shader(shaderProvider.loadBasicLight());
		if (shader != nullptr) {
			material = ghnew Material();
			material->init(memoryManager);
			material->Shader = shader.get();
			/*if (diffuseTexture) {
				TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
				diffuse->setValue(diffuseTexture);
			}
			if (specularTexture) {
				TextureParameter* specular = (TextureParameter*)material->Shader->getParameter(ParameterId::SPECULAR_TEXTURE.ConstantName);
				specular->setValue(specularTexture);
			}
			if (normalTexture) {
				TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::NORMAL_TEXTURE.ConstantName);
				diffuse->setValue(normalTexture);
			}*/
		}
		return material;
	}

	Material* MaterialProvider::makeChecker() const {
		Material* material = nullptr;
		IntrusivePointer<Shader> shader(shaderProvider.loadBasic());
		if (shader != nullptr) {
			material = ghnew Material();
			material->init(memoryManager);
			material->Shader = shader.get();
			ITexture* texture = textureProvider.makeChecker();
			//TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
			//diffuse->setValue(texture);
		}
		return material;
	}

	Material* MaterialProvider::makeWireframe() const {
		IntrusivePointer<Shader> shader(shaderProvider.loadWireframe());
		return makeWithShader(shader.get());
	}

	Material* MaterialProvider::makeOutline() const {
		IntrusivePointer<Shader> shader(shaderProvider.loadOutline());
		return makeWithShader(shader.get());
	}

	Material* MaterialProvider::makeNormals() const {
		IntrusivePointer<Shader> shader(shaderProvider.loadNormals());
		return makeWithShader(shader.get());
	}

	Material* MaterialProvider::makeInvalid() const {
		IntrusivePointer<Shader> shader(shaderProvider.loadInvalid());
		return makeWithShader(shader.get());
	}

	Material* MaterialProvider::makeLightPass() const {
		IntrusivePointer<Shader> shader(shaderProvider.loadLightPass());
		return makeWithShader(shader.get());
	}

	Material* MaterialProvider::makeBasicSky() const {
		IntrusivePointer<Shader> shader(shaderProvider.loadBasicSky());
		return makeWithShader(shader.get());
	}

	Material* MaterialProvider::makeAdvancedSky() const {
		IntrusivePointer<Shader> shader(shaderProvider.loadAdvancedSky());
		return makeWithShader(shader.get());
	}
}