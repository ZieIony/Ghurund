#include "ghe2dpch.h"
#include "SpriteComponent.h"

#include "engine/2d/Graphics2DFeature.h"

namespace Ghurund::Engine::_2D {
	void SpriteComponent::init(IGPUMemoryManager& memoryManager) {
		Mesh = Graphics2DFeature::MESH_SPRITE;
		auto spriteMaterial = IntrusivePointer((Ghurund::Engine::Material*)Graphics2DFeature::MATERIAL_SPRITE->clone());
		spriteMaterial->init(memoryManager);
		Material = spriteMaterial.get();
	}
}
