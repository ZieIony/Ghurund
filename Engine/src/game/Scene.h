#pragma once

#include "collection/List.h"
#include "graphics/Model.h"
#include "graphics/CommandList.h"
#include "graphics/Camera.h"
#include "graphics/Light.h"
#include "Entity.h"

namespace Ghurund {
    class Scene:public Entity {
    private:
        List<shared_ptr<Model>> models;
        List<shared_ptr<Camera>> cameras;
        List<shared_ptr<Light>> lights;

        static const Array<ResourceFormat> formats;

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

        virtual void clean() {
            for(size_t i = 0; i<cameras.Size; i++)
                cameras[i].reset();
            models.clear();
            for(size_t i = 0; i<models.Size; i++)
                models[i].reset();
            cameras.clear();
        }

    public:

        Scene() {
            Name = _T("scene");
        }

        void draw(shared_ptr<CommandList> commandList) {
            for(size_t i = 0; i<cameras.Size; i++)
                cameras[i]->fillParameters();

            for(size_t i = 0; i<models.Size; i++) {
                models[i]->fillParameters();
                models[i]->draw(commandList->get());
            }
        }

        List<shared_ptr<Model>> &getModels() {
            return models;
        }

        __declspec(property(get = getModels)) List<shared_ptr<Model>> &Models;

        List<shared_ptr<Camera>> &getCameras() {
            return cameras;
        }

        __declspec(property(get = getCameras)) List<shared_ptr<Camera>> &Cameras;

        List<shared_ptr<Light>> &getLights() {
            return lights;
        }

        __declspec(property(get = getLights)) List<shared_ptr<Light>> &Lights;

        virtual const Array<ResourceFormat> &getFormats() const override {
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::ENTITY;
        }
    };
}