#pragma once

#include <cstdint>

namespace Ghurund::Core {
	struct FontMetrics {
        uint16_t height;
        uint16_t ascent;
        uint16_t descent;
        uint16_t weight;
        bool italic;
	};
}