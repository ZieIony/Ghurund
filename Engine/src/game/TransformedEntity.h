#pragma once

#include "Entity.h"

namespace Ghurund {

    class TransformedEntity: public TransformedObject, public Entity {
    private:
        Entity *entity;
        Array<Parameter*> parameters;

        TransformedEntity():parameters(Array<Parameter*>(0)) {}

        friend class Type;

    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, ResourceContext &context, MemoryInputStream &stream, LoadOption options) override {
            memcpy(&position, stream.readBytes(sizeof(position)), sizeof(position));
            memcpy(&rotation, stream.readBytes(sizeof(rotation)), sizeof(rotation));
            memcpy(&scale, stream.readBytes(sizeof(scale)), sizeof(scale));

            memcpy(&world, stream.readBytes(sizeof(world)), sizeof(world));

            Status result;
            entity = (Entity*)resourceManager.load(context, stream, &result, options);

            return result;
        }

        virtual Status saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options) const override {
            stream.writeBytes(&position, sizeof(position));
            stream.writeBytes(&rotation, sizeof(rotation));
            stream.writeBytes(&scale, sizeof(scale));

            stream.writeBytes(&world, sizeof(world));

            return resourceManager.save(*entity, options);
        }

        virtual void clean() {}

    public:
        TransformedEntity(Entity &entity):TransformedEntity() {
            this->entity = &entity;
            entity.addReference();
        }

        ~TransformedEntity() {
            entity->release();
        }

        virtual void flatten(RenderingBatch &batch, XMFLOAT4X4 &transformation) override {
            XMFLOAT4X4 localTransformation = getTransformation();
            XMFLOAT4X4 dest;
            XMStoreFloat4x4(&dest, XMLoadFloat4x4(&transformation)*XMLoadFloat4x4(&localTransformation));
            entity->flatten(batch, dest);
        }

        virtual const Ghurund::Type &getType() const override {
            return Type::TRANSFORMED_ENTITY;
        }

        virtual const Array<ResourceFormat> &getFormats() const override {
            static const Array<ResourceFormat> formats = {ResourceFormat::AUTO, ResourceFormat::ENTITY};
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::ENTITY;
        }

        virtual Array<Parameter*>& getParameters() override {
            return parameters;
        }
    };
}