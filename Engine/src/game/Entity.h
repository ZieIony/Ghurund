#pragma once

#include "collection/String.h"
#include "ParameterProvider.h"
#include "ParameterManager.h"
#include "collection/TypeList.h"
#include "resource/Resource.h"
#include "core/NamedObject.h"
#include "graphics/TransformedObject.h"

#include <DirectXCollision.h>

namespace Ghurund {

    class RenderingBatch;

    class Entity: public Resource, public NamedObject {
    public:
        virtual void flatten(RenderingBatch &batch, XMFLOAT4X4 &transformation) = 0;

        virtual bool intersects(XMFLOAT3 &pos, XMFLOAT3 &dir) {
            return false;
        }
    };

    class TransformedEntity: public TransformedObject, public Entity {
    private:
        Entity &entity;

    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, ResourceContext &context, MemoryInputStream &stream, LoadOption options) override {
            memcpy(&position, stream.readBytes(sizeof(position)), sizeof(position));
            memcpy(&rotation, stream.readBytes(sizeof(rotation)), sizeof(rotation));
            memcpy(&scale, stream.readBytes(sizeof(scale)), sizeof(scale));

            memcpy(&world, stream.readBytes(sizeof(world)), sizeof(world));

            return Status::OK;
        }

        virtual Status saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options) const override {
            stream.writeBytes(&position, sizeof(position));
            stream.writeBytes(&rotation, sizeof(rotation));
            stream.writeBytes(&scale, sizeof(scale));

            stream.writeBytes(&world, sizeof(world));

            return Status::OK;
        }

        virtual void clean() {}

    public:
        TransformedEntity(Entity &entity):entity(entity) {}

        virtual void flatten(RenderingBatch &batch, XMFLOAT4X4 &transformation) override {
            XMFLOAT4X4 localTransformation = getTransformation();
            XMFLOAT4X4 dest;
            XMStoreFloat4x4(&dest, XMLoadFloat4x4(&transformation)*XMLoadFloat4x4(&localTransformation));
            entity.flatten(batch, dest);
        }

        virtual const Ghurund::Type &getType() const override {
            return Type::MODEL;
        }

        virtual const Array<ResourceFormat> &getFormats() const override {
            static const Array<ResourceFormat> formats = {ResourceFormat::AUTO, ResourceFormat::MODEL};
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::MODEL;
        }

    };

}