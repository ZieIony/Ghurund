#pragma once

#include "collection/PointerList.h"
#include "game/entity/Entity.h"
#include "game/entity/Model.h"
#include "game/entity/Light.h"
#include "game/entity/Camera.h"
#include "graphics/CommandList.h"

namespace Ghurund {

    class Scene:public Entity {
    private:
        Array<Parameter*> parameters;

    protected:
        PointerList<Entity*> entities;

        virtual Status loadInternal(ResourceManager &resourceManager, ResourceContext &context, const DirectoryPath &workingDir, MemoryInputStream &stream, LoadOption options) override;
        virtual Status saveInternal(ResourceManager &resourceManager, const DirectoryPath &workingDir, MemoryOutputStream &stream, SaveOption options) const override;

    public:

        Scene():parameters(Array<Parameter*>(0)) {
            Name = _T("scene");
        }

        ~Scene() {}

        virtual void initParameters(ParameterManager &parameterManager) override {
            for(Entity *e:entities)
                e->initParameters(parameterManager);
        }

        virtual void updateParameters() override {
            for(Entity *e:entities)
                e->updateParameters();
        }

        virtual Array<Parameter*> &getParameters() {
            return parameters;
        }

        virtual const Ghurund::Type &getType() const override {
            return Type::SCENE;
        }

        PointerList<Entity*> &getEntities() {
            return entities;
        }

        __declspec(property(get = getEntities)) PointerList<Entity*> &Entities;

        Entity *findEntity(String &name) {
            for(Entity *entity:entities) {
                if(entity->Name==name)
                    return entity;
            }

            return nullptr;
        }

        List<Entity*> *findEntities(String &name) {
            List<Entity*> *list = ghnew List<Entity*>();
            for(Entity *entity:entities) {
                if(entity->Name==name)
                    list->add(entity);
            }

            return list;
        }

        Entity *findEntity(Ghurund::Type &type) {
            for(Entity *entity:entities) {
                if(entity->Type==type)
                    return entity;
            }

            return nullptr;
        }

        List<Entity*> *findEntities(Ghurund::Type &type) {
            List<Entity*> *list = ghnew List<Entity*>();
            for(Entity *entity:entities) {
                if(entity->Type==type)
                    list->add(entity);
            }

            return list;
        }

        static const Array<ResourceFormat*> &getFormats() {
            static const Array<ResourceFormat*> formats = {(ResourceFormat*)&ResourceFormat::SCENE};
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*> &Formats;

        virtual void flatten(RenderStep &step, XMFLOAT4X4 &transformation) override {
            for(size_t i = 0; i<Entities.Size; i++) {
                Entity *entity = Entities[i];
                entity->flatten(step, transformation);
            }
        }

    };
}