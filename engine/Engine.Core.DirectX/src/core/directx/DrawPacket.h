#pragma once

#include "mesh/Mesh.h"

namespace Ghurund::Core::DirectX {
	class DrawPacket {
	private:
		Mesh* mesh;

	public:
		void draw(CommandList& commandList) {
			mesh->draw(commandList);
		}
	};
}