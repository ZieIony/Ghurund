#include "ghedxpch.h"
#include "DxTexture.h"

#include "core/reflection/TypeBuilder.h"
#include "engine/directx/memory/DxGPUMemoryManager.h"
#include "engine/directx/DxGraphics.h"

namespace Ghurund::Engine::DirectX {
	const Ghurund::Core::Type& DxTexture::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<DxTexture>();
		static const Ghurund::Core::Type TYPE = TypeBuilder<DxTexture>()
			.withSupertype(__super::GET_TYPE())
			.withConstructor(CONSTRUCTOR);

		return TYPE;
	}

	void DxTexture::init(DxGPUMemoryManager& memoryManager, DxGraphics& graphics) {
		memoryManager.resetUpload();

		textureResource = memoryManager.makeTexture(images);
		descHandle = memoryManager.makeTextureRV(textureResource, images[0]->Format, images.Size);

		memoryManager.executeUploads();

		auto desc = textureResource->GetDesc();
		auto allocationInfo = graphics.Device->GetResourceAllocationInfo(0, 1, &desc);
		dataSize.graphical = allocationInfo.SizeInBytes;
		State = ResourceState::INITIALIZED;
	}
	
	void DxTexture::setImages(List<IntrusivePointer<Ghurund::Core::Image>>& images) {
		if (State != ResourceState::EMPTY) {
			deinit_internal();
			unload_internal();
		}

		this->images = images;
		size = images[0]->Size;
		format = images[0]->Format;

		dataSize.system = sizeof(*this);
		State = ResourceState::LOADED;
	}
}
