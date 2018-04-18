#pragma once

#include "game\Entity.h"

namespace Ghurund {
    class Light: public Entity {
    private:
        Entity target;

    public:
        Light() {
            target.Name = _T("target");
            subentities.add(&target);
        }
    };
}