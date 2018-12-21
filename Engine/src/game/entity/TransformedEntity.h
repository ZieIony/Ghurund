#pragma once

#include "Entity.h"

namespace Ghurund {

    class TransformedEntity: public Entity, public TransformedObject {
    private:
        Entity *entity = nullptr;
        Array<Parameter*> parameters;

        TransformedEntity():parameters(Array<Parameter*>(0)) {}

        friend class Type;

    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, ResourceContext &context, MemoryInputStream &stream, LoadOption options) override {
            memcpy(&position, &stream.read<XMFLOAT3>(), sizeof(position));
            memcpy(&rotation, &stream.read<XMFLOAT3>(), sizeof(rotation));
            memcpy(&scale, &stream.read<XMFLOAT3>(), sizeof(scale));

            memcpy(&world, &stream.read<XMFLOAT4X4>(), sizeof(world));

            Status result;
            entity = (Entity*)resourceManager.load(context, stream, &result, options);

            return result;
        }

        virtual Status saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options) const override {
            stream.write(position);
            stream.write(rotation);
            stream.write(scale);

            stream.write(world);

            return resourceManager.save(*entity, stream, options);
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

        static const Array<ResourceFormat*> &getFormats() {
            static const Array<ResourceFormat*> formats = {(ResourceFormat*)&ResourceFormat::ENTITY};
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*> &Formats;

        virtual Array<Parameter*>& getParameters() override {
            return parameters;
        }
    };
}