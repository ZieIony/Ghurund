#pragma once

#include "core/Pointer.h"

#include <entt.hpp>

namespace Ghurund {
    class Entity:public Pointer {
    public:
        class ComponentCollection {
        private:
            Entity& owner;

        public:
            ComponentCollection(Entity& owner):owner(owner) {}

            template<typename Type, typename... Args>
            Type& add(Args&&... args) {
                return owner.registry.emplace<Type>(owner.id, std::forward<Args>(args)...);
            }

            template<typename Type>
            bool contains() {
                return owner.registry.any_of<Type>(owner.id);
            }

            template<typename Type>
            Type& get() {
                return owner.registry.get<Type>(owner.id);
            }

            template<typename Type>
            void remove() {
                owner.registry.remove<Type>(owner.id);
            }
        };

    private:
        entt::entity id;
        entt::registry& registry;
        ComponentCollection components;
        WString name;

    public:
        Entity(entt::registry& registry):id(registry.create()), registry(registry), components(*this) {}

        ~Entity() {
            registry.destroy(id);
        }

        inline ComponentCollection& getComponents() {
            return components;
        }

        __declspec(property(get = getComponents)) ComponentCollection& Components;

        inline WString& getName() {
            return name;
        }

        inline void setName(const WString& name) {
            this->name = name;
        }

        __declspec(property(get = getName, put = setName)) WString& Name;
    };
}