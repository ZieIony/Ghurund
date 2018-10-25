#pragma once

#include "game/ParameterProvider.h"

#include <DirectXCollision.h>

namespace Ghurund {

    template <class Type> class GlobalEntity: public ParameterProvider {
    private:
        XMFLOAT4X4 world;
        BoundingOrientedBox boundingBox;
        bool visible = true;

        Type &entity;

    public:
        GlobalEntity(Type &entity, BoundingBox &boundingBox, XMFLOAT4X4 world):entity(entity) {
            BoundingOrientedBox::CreateFromBoundingBox(this->boundingBox, boundingBox);
            this->boundingBox.Transform(this->boundingBox, XMLoadFloat4x4(&world));
            this->world = world;
        }

        const XMFLOAT4X4 &getTransformation() const {
            return world;
        }

        __declspec(property(get = getTransformation)) XMFLOAT4X4 &Transformation;

        Type &getEntity() const {
            return entity;
        }

        __declspec(property(get = getEntity)) Type &Entity;

        BoundingOrientedBox &getBoundingBox() {
            return boundingBox;
        }

        __declspec(property(get = getBoundingBox)) BoundingOrientedBox &BoundingBox;

        bool isVisible() {
            return visible;
        }

        __declspec(property(get = isVisible)) bool Visible;

        void cull(BoundingFrustum &frustum) {
            visible = frustum.Contains(boundingBox)!=ContainmentType::DISJOINT;
        }

        bool checkIntersection(XMFLOAT3 &pos, XMFLOAT3 &dir) {
            float dist;
            bool picked = boundingBox.Intersects(XMLoadFloat3(&pos), XMLoadFloat3(&dir), dist);
            if(picked) {
                // TODO: test geometry
                //entity->
            }
            return picked;
        }
    };
}