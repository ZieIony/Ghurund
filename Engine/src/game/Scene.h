#pragma once

#include "collection/List.h"
#include "graphics/Model.h"
#include "graphics/CommandList.h"
#include "graphics/Camera.h"
#include "graphics/Light.h"
#include "Entity.h"

namespace Ghurund {
    class Scene:public Entity {
    protected:
        virtual unsigned int getVersion()const {
            return 0;
        }

        Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size) {
            return Status::NOT_IMPLEMENTED;
        }

        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size, unsigned int flags = 0)const {
            return Status::NOT_IMPLEMENTED;
        }

    public:

        Scene() {
            Name = _T("scene");
        }

        void draw(shared_ptr<CommandList> commandList) {
            List<Model*> models;
            List<Camera*> cameras;
            List<Light*> lights;

            for(size_t i = 0; i<Entities.Size; i++) {
                Entity *entity = Entities[i];
                if(entity->Type==EntityType::MODEL) {
                    models.add((Model*)entity);
                } else if(entity->Type==EntityType::CAMERA) {
                    cameras.add((Camera*)entity);
                }
            }

            cameras.get(0)->fillParameters();
            for(size_t i = 0; i<models.Size; i++) {
                models[i]->fillParameters();
                models[i]->draw(commandList->get());
            }
        }

        virtual const Array<ResourceFormat> &getFormats() const override {
            static const Array<ResourceFormat> formats = {ResourceFormat::AUTO, ResourceFormat::ENTITY};
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::ENTITY;
        }
    };
}