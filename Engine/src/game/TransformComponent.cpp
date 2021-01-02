#include "TransformComponent.h"

#include "core/io/File.h"
#include "core/io/MemoryStream.h"

namespace Ghurund {
	Status TransformComponent::loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
		position = stream.read<XMFLOAT3>();
		rotation = stream.read<XMFLOAT3>();
		scale = stream.read<XMFLOAT3>();
		return Status::OK;
	}
	
	Status TransformComponent::saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
		stream.write<XMFLOAT3>(position);
		stream.write<XMFLOAT3>(rotation);
		stream.write<XMFLOAT3>(scale);
		return Status::OK;
	}
}