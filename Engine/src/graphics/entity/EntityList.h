#pragma once

#include "collection/PointerList.h"
#include "graphics/entity/Entity.h"

namespace Ghurund {

    class EntityList:public PointerList<Entity*> {
    private:
        Entity& owner;

    public:
        EntityList(Entity& owner):owner(owner) {}

        ~EntityList() {
            for (size_t i = 0; i < size; i++)
                v[i]->parent = nullptr;
        }

        inline void add(Entity* const& item) {
            PointerList<Entity*>::add(item);
            item->parent = &owner;
        }

        inline void insert(size_t i, Entity* const& item) {
            PointerList<Entity*>::insert(i, item);
            item->parent = &owner;
        }

        inline void insertKeepOrder(size_t i, Entity* const& item) {
            PointerList<Entity*>::insertKeepOrder(i, item);
            item->parent = &owner;
        }

        inline void set(size_t i, Entity* const& item) {
            v[i]->parent = nullptr;
            PointerList<Entity*>::set(i, item);
            item->parent = &owner;
        }

        inline void removeAt(size_t i) {
            v[i]->parent = nullptr;
            PointerList<Entity*>::removeAt(i);
        }

        inline void removeAtKeepOrder(size_t i) {
            v[i]->parent = nullptr;
            PointerList<Entity*>::removeAtKeepOrder(i);
        }

        inline void remove(Entity* const& item) {
            item->parent = nullptr;
            PointerList<Entity*>::remove(item);
        }

        inline void removeKeepOrder(Entity* const& item) {
            item->parent = nullptr;
            PointerList<Entity*>::removeKeepOrder(item);
        }

        inline void clear() {
            for (size_t i = 0; i < size; i++)
                v[i]->parent = nullptr;
            PointerList<Entity*>::clear();
        }
    };
}