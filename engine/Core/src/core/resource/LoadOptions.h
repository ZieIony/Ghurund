#pragma once

namespace Ghurund::Core {
	struct LoadOptions {
		// keep track of this resource and reload if necessary
		const bool watch = IS_DEBUG_BUILD && !IS_UNIT_TEST;

		// the state the resource should be in when loading completes
		const ResourceState targetState = ResourceState::INITIALIZED;

		// if the resource was already loaded, clone it and return the clone
		const bool clone = false;
	};
}
