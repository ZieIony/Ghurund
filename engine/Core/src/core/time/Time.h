#include <cstdint>

namespace Ghurund::Core {
	template<typename T>
    struct Time {
        T value = 0.0;
        uint32_t valueMs = 0;
        uint64_t valueNs = 0;

        /**
        * Scaled time takes max frame time into account,
        * so scaled time may not be equal to time even if time scale == 1.
        **/
        T scaledValue = 0.0;
	};
}
