#pragma once

#include "graphics/mesh/Mesh.h"
#include "Material.h"
#include "graphics/mesh/CubeMesh.h"
#include "graphics/mesh/SphereMesh.h"
#include "resource/ResourceManager.h"
#include "game/Entity.h"

namespace Ghurund {
    class Model: public Entity {
    private:
        shared_ptr<Mesh> mesh;
        shared_ptr<Material> material;

    protected:
        List<Entity*> entities;

        virtual Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned long *bytesRead) override;
        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size) const override;

    public:

        Model(){}

        Model(shared_ptr<Mesh> mesh, shared_ptr<Material> material) {
            this->mesh = mesh;
            this->material = material;
        }

        virtual EntityType getType() const override {
            return EntityType::MODEL;
        }

        shared_ptr<Mesh> getMesh() {
            return mesh;
        }

        void setMesh(shared_ptr<Mesh> mesh) {
            this->mesh = mesh;
        }

        __declspec(property(get = getMesh, put = setMesh)) shared_ptr<Mesh> Mesh;

        shared_ptr<Material> getMaterial() {
            return material;
        }

        void setMaterial(shared_ptr<Material> material) {
            this->material = material;
        }

        __declspec(property(get = getMaterial, put = setMaterial)) shared_ptr<Material> Material;

        void draw(ID3D12GraphicsCommandList *commandList) {
            material->set(commandList);
            mesh->draw(commandList);
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