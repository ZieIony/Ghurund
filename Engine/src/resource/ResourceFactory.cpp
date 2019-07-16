#include "ResourceFactory.h"
#include "graphics/DrawableComponent.h"

namespace Ghurund {
	DefaultResourceFactory::DefaultResourceFactory() {
		addType(Type::CAMERA);
		addType(Type::LIGHT);
		addType(Type::MESH);
		addType(DrawableComponent::TYPE);
		addType(Type::TEXTURE);
		addType(Type::MATERIAL);
		addType(Type::IMAGE);
		addType(Type::SHADER);
		addType(Type::SCENE);
	}
}