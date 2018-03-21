#pragma once

#include "collection/List.h"
#include "graphics/Model.h"
#include "graphics/CommandList.h"

namespace Ghurund {
    class Scene:public Resource {
    private:
        List<shared_ptr<Model>> models;

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

    public:
        void draw(shared_ptr<CommandList> commandList) {
            for(size_t i = 0; i<models.Size; i++)
                models[i]->draw(commandList->get());
        }

        void addModel(shared_ptr<Model> model) {
            models.add(model);
        }
    };
}