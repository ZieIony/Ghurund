#include "ghe3dpch.h"
#include "TransformComponent3DLoader.h"

#include "TransformComponent3D.h"

#include "core/math/Vector.h"

namespace Ghurund::Engine::_3D {
	void TransformComponent3DLoader::loadComponent(NotNull<Scene> scene, NotNull<Entity> entity, const XMLElement& xml, const DirectoryPath& workingDir) {
		auto& component = entity->addComponent<TransformComponent3D>();
		auto positionAttr = xml.findAttribute(L"position");
		if (positionAttr)
			component.Position = parse<XMFLOAT3>(*positionAttr);
		auto rotationAttr = xml.findAttribute(L"rotation");
		if (rotationAttr)
			component.Rotation = parse<XMFLOAT3>(*rotationAttr);
		auto scaleAttr = xml.findAttribute(L"scale");
		if (scaleAttr)
			component.Scale = parse<XMFLOAT3>(*scaleAttr);
	}
}
