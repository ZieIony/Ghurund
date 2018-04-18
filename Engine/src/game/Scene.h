#pragma once

#include "collection/List.h"
#include "graphics/Model.h"
#include "graphics/CommandList.h"
#include "graphics/Camera.h"

namespace Ghurund {
    class Scene:public Resource {
    private:
        List<shared_ptr<Model>> models;
        List<shared_ptr<Camera>> cameras;

    protected:
        virtual unsigned int getVersion()const {
            return 0;
        }

        Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned int flags = 0) {
            return Status::NOT_IMPLEMENTED;
        }

        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size, unsigned int flags = 0)const {
            return Status::NOT_IMPLEMENTED;
        }

        virtual void clean() {
            for(size_t i = 0; i<cameras.Size; i++)
                cameras[i].reset();
            models.clear();
            for(size_t i = 0; i<models.Size; i++)
                models[i].reset();
            cameras.clear();
        }

    public:

        void draw(shared_ptr<CommandList> commandList, ParameterManager &parameterManager) {
            for(size_t i = 0; i<cameras.Size; i++)
                cameras[i]->fillParameters();

            for(size_t i = 0; i<models.Size; i++)
                models[i]->draw(commandList->get());
        }

        void addModel(shared_ptr<Model> model) {
            models.add(model);
        }

        void addCamera(shared_ptr<Camera> camera) {
            cameras.add(camera);
        }
    };
}