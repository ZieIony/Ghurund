#pragma once

#include "graphics/mesh/Mesh.h"
#include "Material.h"
#include "graphics/mesh/CubeMesh.h"
#include "graphics/mesh/SphereMesh.h"
#include "resource/ResourceManager.h"
#include "game/Entity.h"
#include "game/ParameterProvider.h"

namespace Ghurund {
    class Model: public Entity, public ParameterProvider {
    private:
        Mesh *mesh = nullptr;
        Material *material = nullptr;

    protected:
        List<Entity*> entities;

        virtual Status loadInternal(ResourceManager &resourceManager, MemoryInputStream &stream, LoadOption options) override;
        virtual Status saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options) const override;

    public:

        Model(){}

        Model(Mesh *mesh, Material *material) {
            setPointer(this->mesh, mesh);
            setPointer(this->material, material);
        }

        ~Model() {
            mesh->release();
            material->release();
        }

        Mesh *getMesh() {
            return mesh;
        }

        void setMesh(Mesh *mesh) {
            this->mesh = mesh;
        }

        __declspec(property(get = getMesh, put = setMesh)) Mesh *Mesh;

        Material *getMaterial() {
            return material;
        }

        void setMaterial(Material *material) {
            this->material = material;
        }

        __declspec(property(get = getMaterial, put = setMaterial)) Material *Material;

        void draw(CommandList &commandList, ParameterManager &parameterManager) {
            material->set(commandList, parameterManager);
            mesh->draw(commandList);
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

        virtual void flatten(RenderingBatch &batch, XMFLOAT4X4 &transformation) override;
    };
}