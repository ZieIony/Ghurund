#pragma once

#include <engine/graphics/mesh/Mesh.h>
#include <engine/graphics/material/Material.h>

namespace Ghurund::Engine {
	struct RenderableComponent {
		Mesh* mesh;
		Material* material;
		float order;
	};
}
