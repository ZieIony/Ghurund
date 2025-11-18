#pragma once

#include "DrawPacket.h"
#include <core/collection/List.h>

#include <cstdint>

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class RenderGroup {
    private:
        uint32_t order;
        int8_t drawOrder;

    public:
        List<DrawPacket> objects;

        // TODO: is this draw order correct?
        RenderGroup(uint32_t order, bool frontToBack = true):order(order), drawOrder(frontToBack ? 1 : -1) {}

        // TODO: get sorted objects from here
        inline int8_t getDrawOrder() const {
            return drawOrder;
        }

        __declspec(property(get = getDrawOrder)) int8_t DrawOrder;

        inline auto operator<=>(const RenderGroup& other) const {
            return order <=> other.order;
        }
    };
}