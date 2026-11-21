#include "ghepch.h"
#include "StaticDrawable.h"

namespace Ghurund::Engine {
	const Ghurund::Core::Type& StaticDrawable::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<StaticDrawable>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void StaticDrawable::queueDraw(RenderGroup& group) {
		if (mesh && material) {
			auto w = XMMatrixTranslation(offset.x, offset.y, 0) * XMMatrixScaling(size.Width, size.Height, 1);
			XMFLOAT4X4 world;
			XMStoreFloat4x4(&world, XMMatrixTranspose(w));

			if(worldInput)
				worldInput->Value = world;
			BatchId batchId = { mesh->id, material->id };
			if (!group.objects.contains(batchId))
				group.objects.put(batchId, { mesh, material });
			//renderingContext.setParameters(visualization.WorldId, objParameters);
			//group.objects.get(batchId).instances.add(visualization.WorldId);
		}
	}
}
