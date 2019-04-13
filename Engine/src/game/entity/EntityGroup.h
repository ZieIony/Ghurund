#pragma once

#include "game/entity/EntityList.h"

namespace Ghurund {

    class EntityGroup:public Entity {
    protected:
        EntityList entities;

        virtual Status loadInternal(ResourceManager& resourceManager, ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) override;
        virtual Status saveInternal(ResourceManager& resourceManager, ResourceContext &context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const override;

    public:

        EntityGroup():entities(*this) {
        }

        virtual void initParameters(ParameterManager& parameterManager) override {
            for (Entity* e : entities)
                e->initParameters(parameterManager);
        }

        virtual void updateParameters() override {
            for (Entity* e : entities)
                e->updateParameters();
        }

        virtual const Ghurund::Type& getType() const override {
            return Type::SCENE;
        }

        EntityList& getEntities() {
            return entities;
        }

        __declspec(property(get = getEntities)) EntityList & Entities;

        Entity * findEntity(String & name) {
            for (Entity* entity : entities) {
                if (entity->Name == name)
                    return entity;
            }

            return nullptr;
        }

        List<Entity*>* findEntities(String & name) {
            List<Entity*>* list = ghnew List<Entity*>();
            for (Entity* entity : entities) {
                if (entity->Name == name)
                    list->add(entity);
            }

            return list;
        }

        Entity* findEntity(Ghurund::Type & type) {
            for (Entity* entity : entities) {
                if (entity->Type == type)
                    return entity;
            }

            return nullptr;
        }

        List<Entity*>* findEntities(Ghurund::Type & type) {
            List<Entity*>* list = ghnew List<Entity*>();
            for (Entity* entity : entities) {
                if (entity->Type == type)
                    list->add(entity);
            }

            return list;
        }

        virtual void flatten(RenderStep & step, XMFLOAT4X4 & transformation) override {
            for (size_t i = 0; i < Entities.Size; i++) {
                Entity* entity = Entities[i];
                entity->flatten(step, transformation);
            }
        }

    };
}