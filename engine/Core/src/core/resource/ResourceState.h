#pragma once

namespace Ghurund::Core {
	enum class ResourceState {
		// a path may be set, but the rest is missing
		EMPTY,
		// the resource was loaded, but can't be used yet, for example because it still needs to be uploaded to VRAM
		LOADED,
		// the resource is ready to use
		INITIALIZED
	};
}
