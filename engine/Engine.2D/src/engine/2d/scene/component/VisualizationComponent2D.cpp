#include "ghe2dpch.h"
#include "VisualizationComponent2D.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& VisualizationComponent2D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<VisualizationComponent2D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
		
	VisualizationComponent2D::~VisualizationComponent2D() {
		if (mesh)
			mesh->release();
		if (material)
			material->release();
	}
	
	void VisualizationComponent2D::draw(RenderGroup& group) {
		auto w = XMLoadFloat4x4(&worldTransformation);
		XMFLOAT4X4 world;
		XMStoreFloat4x4(&world, XMMatrixTranspose(w));

		inputs.Transformation = world;
		inputs.Extents = { extents.x * 100, extents.y * 100 };

		group.objects.add(DrawPacket(mesh, material, drawOrder));
	}
}
