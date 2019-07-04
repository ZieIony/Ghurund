#include "Entity.h"

namespace Ghurund {

    PointerList<Entity*> Entity::entities;
    atomic<id_t> Entity::currentId = {0};

}