#pragma once

#include "engine/graphics/mesh/Mesh.h"
#include "engine/graphics/mesh/MeshData.h"

namespace Ghurund::Engine {
	class IGraphicsResourceFactory:public Noncopyable {
	public:
		[[nodiscard]]
		virtual Mesh* makeMesh(const MeshData& meshData) = 0;
	};
}
