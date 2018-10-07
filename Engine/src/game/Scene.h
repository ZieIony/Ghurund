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
        List<Entity*> entities;

        virtual Status loadInternal(ResourceManager &resourceManager, ResourceContext &context, MemoryInputStream &stream, LoadOption options) override {
            size_t size = stream.read<size_t>();
            for(size_t i = 0; i<size; i++) {
                Status result;
                Resource *resource = resourceManager.load(context, stream, &result, options);
                if(resource==nullptr)
                    return result;
                entities.add((Entity*)resource);
            }
            return Status::OK;
        }

        virtual Status saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options) const override {
            stream.write<size_t>(entities.Size);
            for(size_t i = 0; i<entities.Size; i++) {
                Status result = resourceManager.save(*entities[i], stream, options);
                if(result!=Status::OK)
                    return result;
            }
            return Status::OK;
        }

    public:

        Scene() {
            Name = _T("scene");
        }

        ~Scene() {
            for(size_t i = 0; i<entities.Size; i++)
                entities[i]->release();
        }

        virtual const Ghurund::Type &getType() const override {
            return Type::SCENE;
        }

        List<Entity*> &getEntities() {
            return entities;
        }

        __declspec(property(get = getEntities)) List<Entity*> &Entities;

        virtual const Array<ResourceFormat> &getFormats() const override {
            static const Array<ResourceFormat> formats = {ResourceFormat::AUTO, ResourceFormat::ENTITY};
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::ENTITY;
        }

        virtual void flatten(RenderingBatch &batch, XMFLOAT4X4 &transformation) override {
            for(size_t i = 0; i<Entities.Size; i++) {
                Entity *entity = Entities[i];
                entity->flatten(batch, transformation);
            }
        }

    };
}