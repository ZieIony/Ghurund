#pragma once

#include "core/image/Image.h"
#include "engine/graphics/mesh/Mesh.h"
#include "engine/graphics/mesh/MeshData.h"
#include "engine/graphics/texture/ITexture.h"
#include "engine/graphics/cubemap/ICubeMap.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class IGraphicsResourceFactory:public Noncopyable {
	public:
		[[nodiscard]]
		virtual Mesh* makeMesh(const MeshData& meshData) = 0;

		[[nodiscard]]
		virtual ITexture* makeTexture(Image& image, bool generateMips = false) = 0;

		[[nodiscard]]
		virtual ITexture* makeTexture(Array<IntrusivePointer<Image>>& image) = 0;

		[[nodiscard]]
		virtual ICubeMap* makeCubemap(
			Ghurund::Core::Image& imageTop,
			Ghurund::Core::Image& imageBottom,
			Ghurund::Core::Image& imageLeft,
			Ghurund::Core::Image& imageRight,
			Ghurund::Core::Image& imageFront,
			Ghurund::Core::Image& imageBack
		) = 0;
	};
}
