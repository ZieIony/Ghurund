#pragma once

namespace Ghurund::Core {
    struct LoadOptions {
		bool watch =
#ifdef _DEBUG
			true;
#else
			false;
#endif
        bool cache = true;
    };
}
