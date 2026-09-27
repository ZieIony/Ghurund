#include "ghe3dpch.h"
#include "FullscreenQuadComponent.h"

#include "engine/3d/scene/Entity3D.h"
#include "engine/3d/World3D.h"
#include "engine/graphics/GraphicsFeature.h"
#include "engine/graphics/mesh/QuadMeshData.h"

namespace Ghurund::Engine::_3D {
	CoroutineTask<void> FullscreenQuadComponent::onInit() {
		if (!Mesh) {
			auto graphicsFeature = Owner.World.app.Features.get<GraphicsFeature>();
			auto quadMeshData = makeIntrusive<QuadMeshData>();
			quadMeshData->init();
			auto quadMesh = IntrusivePointer<Ghurund::Engine::Mesh>(graphicsFeature->ResourceFactory.makeMesh(quadMeshData.ref()));
			Mesh = quadMesh.get();
		}
		co_return;
	}

	void FullscreenQuadComponent::queueDraw(RenderGroup& group) {
		if (!mesh || !material)
			return;

		group.objects.add(DrawPacket(mesh, material, drawOrder));
	}
}
