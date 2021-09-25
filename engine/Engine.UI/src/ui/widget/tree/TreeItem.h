#pragma once

#include "core/collection/List.h"

namespace Ghurund::UI {
    class TreeItem {
    public:
        TreeItem* parent = nullptr;
        Ghurund::Core::List<TreeItem*> children;

        inline uint32_t getDepth() {
            uint32_t depth = 0;
            TreeItem* p = parent;
            while (p) {
                depth++;
                p = parent->parent;
            }
            return depth;
        }
    };
}