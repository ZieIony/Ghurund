#pragma once

#include "collection/String.h"
#include "ParameterProvider.h"
#include "ParameterManager.h"
#include "collection/TypeList.h"
#include "resource/Resource.h"
#include "core/NamedObject.h"
#include "graphics/BoundingBox.h"
#include "graphics/TransformedObject.h"

namespace Ghurund {

    template <class Type> class GlobalEntity: public ParameterProvider {
    private:
        XMFLOAT4X4 world;
        BoundingBox boundingBox;
        bool isVisible = true;

        Type &entity;

    public:
        GlobalEntity(Type &entity, XMFLOAT4X4 world):entity(entity) {
            this->world = world;
        }

        const XMFLOAT4X4 &getTransformation() const {
            return world;
        }

        Type &getEntity() const {
            return entity;
        }

        __declspec(property(get = getEntity)) Type &Entity;
    };

    class RenderingBatch;

    class Entity: public Resource, public NamedObject {
    protected:
        BoundingBox boundingBox;

    public:
        virtual void flatten(RenderingBatch &batch, XMFLOAT4X4 &transformation) = 0;
    };

    class TransformedEntity: public TransformedObject, public Entity {
    private:
        Entity &entity;

    public:
        TransformedEntity(Entity &entity):entity(entity) {}

        virtual void flatten(RenderingBatch &batch, XMFLOAT4X4 &transformation) override {
            XMFLOAT4X4 localTransformation = getTransformation();
            XMFLOAT4X4 dest;
            XMStoreFloat4x4(&dest, XMLoadFloat4x4(&transformation)*XMLoadFloat4x4(&localTransformation));
            entity.flatten(batch, dest);
        }

    };

}